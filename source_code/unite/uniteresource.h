#ifndef UNITERESOURCE_H
#define UNITERESOURCE_H
#include <map>
#include "../p.o/po.h"
#include "../p.o/scription/scriptionseparate.h"
#include "../p.o/scription/scriptionblock.h"
#include "../p.o/pobase/gllist.h"
#include "unitelist.h"
#include "listdata.h"
#include <fstream>

class UniteResource
{
    std::map<std::string,int> UniteCount;
    std::map<std::string,std::map<std::string,Handle<GLList> > > RicturePool;
    std::map<std::string,UniteList> ULM;
    std::map<std::string,std::string> UniteDefine;
    std::map<std::string,std::string> CustomUniteDefine;
    template<class T> void Translate(const std::string& S,T& D){static std::stringstream SStream;SStream.clear();SStream<<S;SStream>>D;}
public:
    void LoadDefine(std::string P);
    void Clear(){UniteCount.clear();CustomUniteDefine.clear();ULM.clear();UniteDefine.clear();}
    void LoadUnite(std::string P);
    void CheckDetail(std::fstream& P,std::string Pre="   ");
};

void UniteResource::LoadDefine(std::string P)
{
    Clear();
    FileFactor Tem;
    Tem.Separate(P);
    ScriptionBlock SB(Tem.Begin(),Tem.End());
    for(CommentPoint CP=SB.Begin();CP!=SB.End();++CP)
    {
        if(CP->Begin()==CP->End())
            UniteDefine[CP->Detail()]=CP->Scription();
        else{
            bool Custom=false;
            for(OperatorPoint OP=CP->Begin();OP!=CP->End();++OP)
            {
                if(OP->Is("Custom"))
                    Custom=true;
            }
            if(Custom)
                CustomUniteDefine[CP->Detail()]=CP->Scription();
            else
                UniteDefine[CP->Detail()]=CP->Scription();
        }
    }
}

void UniteResource::LoadUnite(std::string P)
{
    bool Find=false;
    bool Custom=false;
    std::string Adress;
    if(UniteDefine.count(P)>0)
    {
        Find=true;
        Adress=UniteDefine[P];
    }else if(CustomUniteDefine.count(P)>0)
    {
        Custom=true;
        Find=true;
        Adress=UniteDefine[P];
    }
    if(Find)
    {
        if(UniteCount.count(P)>0)
        {
            UniteCount[P]+=1;
        }else{
            UniteCount[P]=1;
            if(ULM.count(P)==0)
            {
                FileFactor Tem;
                Tem.Separate(Adress);
                ScriptionBlock SB(Tem.Begin(),Tem.End());
                UniteList& TemList=ULM[P];
                bool Relative=false;
                for(CommentPoint CP=SB.Begin();CP!=SB.End();++CP)
                {
                    if(CP->Is("_Relay"))
                    {
                        LoadUnite(CP->Scription());
                        TemList.Unite(CP->Scription());
                    }else if(CP->Is("_Relative"))
                    {
                        Relative=true;
                        Adress=AdressCount(Adress,"");
                    }else if(CP->Is("_Call"))
                    {
                        int i=0;std::string D;std::string A;FileFactorPoint FFp=CP->ScriptionBegin;
                        while(FFp!=CP->ScriptionEnd)
                        {
                            if(i==0)
                                D=FFp->Detail();
                            else if(i==1)
                                A=FFp->Detail();
                            ++i;++FFp;
                        }
                        if(i!=2)
                            GetError("Parameter is not cerrect.",i);
                        else
                            if(TemList.IsRelay(D))
                            {
                                UniteList& ULT=ULM[D];
                                if(ULT.IsHave(A))
                                    TemList.Define(A,ULT.Find(A));
                            }
                    }else{
                        URStyle URS;
                        OperatorPoint OP=CP->Begin();
                        URS.SetPicture(CP->Scription());
                        if(OP!=CP->End())
                        {
                            if(OP->Is("D"))
                                URS.SetList(CP->Scription());
                        }
                        TemList.Define(CP->Detail(),URS);
                    }
                }
            }
        }
    }
}

void UniteResource::CheckDetail(std::fstream &P, std::string Pre)
{
    for(std::map<std::string,int>::iterator Po=UniteCount.begin();Po!=UniteCount.end();++Po)
        P<<"Unite <"<<Po->first<<"> was used by <"<<Po->second<<"> times"<<std::endl;
    /*for(std::map<std::string,int>::iterator Po=PictureCount.begin();Po!=PictureCount.end();++Po)
        P<<"Picture <"<<Po->first<<"> was used by <"<<Po->second<<"> times"<<std::endl;
    for(std::map<std::string,int>::iterator Po=ListCount.begin();Po!=ListCount.end();++Po)
        P<<"List <"<<Po->first<<"> was used by <"<<Po->second<<"> times"<<std::endl;*/
    for(std::map<std::string,UniteList>::iterator Po=ULM.begin();Po!=ULM.end();++Po)
    {
        P<<"In Unite <"<<Po->first<<"> :"<<std::endl;
        Po->second.CheckDetail(P,Pre);
    }
    for(std::map<std::string,std::string>::iterator Po=UniteDefine.begin();Po!=UniteDefine.end();++Po)
        P<<"Unite <"<<Po->first<<"> at adress <"<<Po->second<<">"<<std::endl;
    for(std::map<std::string,std::string>::iterator Po=CustomUniteDefine.begin();Po!=CustomUniteDefine.end();++Po)
        P<<"CustomUnite <"<<Po->first<<"> at adress <"<<Po->second<<">"<<std::endl;
}


#endif // UNITERESOURCE_H
