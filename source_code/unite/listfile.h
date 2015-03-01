#ifndef LISTFILE_H
#define LISTFILE_H
#include "../p.o/scription/scriptionblock.h"
#include "listdata.h"
class POListData:public GLList
{
public:
    std::list<Handle<GLTexture> > Storage;
    void StoreTexture(Handle<GLTexture>& U){Storage.push_back(U);}
};


class ListFile
{
public:
    std::map<std::string,Handle<ListData> >  PD;
    void LoadScription(const std::string& Now);
    Handle<GLList> CreatList();
    template<class T> void Translate(const std::string& S,T& D){static std::stringstream SStream;SStream.clear();SStream<<S;SStream>>D;}
    void CheckDetail(std::fstream& I);
    void Init(POMain*);
    void CleanUnuse();
};

void ListFile::CleanUnuse()
{
    for(std::map<std::string,Handle<ListData> >::iterator Po=PD.begin();Po!=PD.end();++Po)
    {
        Po->second->CleanUnused();
    }
}

void ListFile::Init(POMain * P)
{
    if(!PD.empty())
        for(std::map<std::string,Handle<ListData> >::iterator Po=PD.begin();Po!=PD.end();++Po)
            Po->second->Init(P);
}

void ListFile::CheckDetail(std::fstream &I)
{
    for(std::map<std::string,Handle<ListData> >::iterator Po=PD.begin();Po!=PD.end();++Po)
    {
        I<<"Model Name <"<<Po->first<<"> :"<<endl;
        Po->second->CheckDetail(I);
    }
}


Handle<GLList> ListFile::CreatList()
{
    Handle<GLList> Tem;
    if(!PD.empty())
    {
        Tem =new GLList;
        Tem->Compile();
        for(std::map<std::string,Handle<ListData> >::iterator Po=PD.begin();Po!=PD.end();++Po)
            Po->second->Draw();
        Tem->Finish();
    }
    return Tem;
}


void ListFile::LoadScription(const std::string &Now)
{
    FileFactor FF;
    FF.Separate(Now);
    ScriptionBlock SB(FF.Begin(),FF.End());
    int C=0;
    float Temfloat;
    int Temint;
    std::map<std::string,Handle<ListData> >::iterator PL=PD.find("");
    if(PL==PD.end())
    {
        Error<<"Creat New"<<endl;
        PD.insert(std::make_pair("",new ListData));
        PL=PD.find("");
        Error<<"Creat New Finish"<<endl;
        for(CommentPoint CP=SB.Begin();CP!=SB.End();++CP)
        {
            if(CP->Is("P"))
            {
                bool Correct=true;
                C=0;
                float* TemA=new float[PL->second->DataNumber()];
                for(FileFactorPoint FFP=CP->ScriptionBegin;FFP!=CP->ScriptionEnd;++FFP)
                {
                    if(C<PL->second->DataNumber())
                    {
                        if(FFP->IsNumber())
                        {
                            Translate(*FFP,Temfloat);
                            TemA[C]=Temfloat;
                            ++C;
                        }else if(FFP->Is(";")||FFP->Is(",")||FFP->Is("-"))
                        {
                            if(FFP->Is("-"))
                            {
                                ++FFP;
                                if(FFP!=CP->ScriptionEnd)
                                {
                                    if(FFP->IsNumber())
                                    {
                                        Translate(*FFP,Temfloat);
                                        TemA[C]=-Temfloat;
                                        ++C;
                                    }else {Correct=false;break;}
                                }else { Correct=false;break;}
                            }
                        }
                    }else{
                        ++C;
                    }
                }
                if(C!=PL->second->DataNumber())Correct=false;
                if(Correct)PL->second->AddPoint(TemA,C);
                else GetError("Comment P parameter is not correct.",CP->Line());
                delete [] TemA;
            }else if(CP->Is("D"))
            {
                for(FileFactorPoint FFP=CP->ScriptionBegin;FFP!=CP->ScriptionEnd;++FFP)
                {
                    if(FFP->IsNumber())
                    {
                        Translate(*FFP,Temint);
                        PL->second->AddPoint(Temint);
                    }else if(FFP->Is(";")||FFP->Is(","))
                    {}else{GetError("Wrong Parameter in Comment D",CP->Line());}
                }
            }else if(CP->Is("MN"))
            {
                bool Correct=true;
                int i=0;
                for(FileFactorPoint FFP=CP->ScriptionBegin;FFP!=CP->ScriptionEnd;++FFP,++i)
                {
                    if(i==0)
                    {
                        std::map<std::string,Handle<ListData> >::iterator Po=PD.find(FFP->Detail());
                        if(Po!=PD.end()){++i;break;}
                        PD.insert(std::make_pair(FFP->Detail(),new ListData));
                        PL=PD.find(FFP->Detail());
                    }else if(i==1)
                    {
                        if(FFP->Is("V"))PL->second->SetOrder(POINT_V);else if(FFP->Is("VT"))PL->second->SetOrder(POINT_VT);else if(FFP->Is("VTN"))PL->second->SetOrder(POINT_VTN);
                        else if(FFP->Is("VC"))PL->second->SetOrder(POINT_VC);else if(FFP->Is("VCN"))PL->second->SetOrder(POINT_VCN);
                    }else{
                        if(PL->second->HaveT())
                        {
                            if(i==2)
                            {
                                if((!FFP->IsNumber())&&(!FFP->IsSymple())) PL->second->Picture(AdressCount(Now,*FFP));
                                else{Correct=false;break;}
                            }else if(i==3)
                            {
                                if(FFP->IsNumber())
                                {int T;Translate(FFP->Detail(),T);PL->second->SetVector(T);}
                                else{Correct=false;break;}
                            }else{Correct=false;break;}
                        }else{
                            if(i==2)
                            {
                                if(FFP->IsNumber())
                                {int T;Translate(FFP->Detail(),T);PL->second->SetVector(T);}
                                else{Correct=false;break;}
                            }else if(i==3)
                            {
                                if(!PL->second->HaveC()){Correct=false;break;}
                                if(FFP->IsNumber())
                                {int T;Translate(FFP->Detail(),T);PL->second->SetColor(T);}
                                else{Correct=false;break;}
                            }else{Correct=false;break;}
                        }
                    }
                }
                if((!Correct)||i==0)
                    GetError("Comment MN Need More Parameter",CP->Line());
            }
        }
    }
    CheckDetail(Error);
}


#endif // LISTFILE_H
