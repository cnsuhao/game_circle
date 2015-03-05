#ifndef SCENERESOURCE_H
#define SCENERESOURCE_H
#include "../p.o/scription/scriptionblock.h"
#include "../p.o/pobase/pomain.h"
class SceneResource:public HandleSeed
{
public:
    std::map<std::string,std::string> Define;
    std::map<std::string,Handle<GLTexture> > Resource;
    std::string Adress;
    void RelesePicture(POMain*){Define.clear();Resource.clear();}
    void LoadScription(std::string);
    void LoadResource(POMain*);
    void CheckDetail(std::fstream& Tem,std::string Pre="");
    Handle<GLTexture> GetResource(std::string P){Handle<GLTexture> Tem;if(Resource.count(P)>0){Tem=Resource[P];}return Tem;}
    SceneResource(){}
    SceneResource(SceneResource& SR):Define(SR.Define),Resource(SR.Resource),Adress(SR.Adress){}
    SceneResource(const SceneResource& SR):Define(SR.Define),Resource(SR.Resource),Adress(SR.Adress){}
    //void operator=(SceneResource SR){Define=SR.Define;Resource=SR.Resource;Adress=SR.Adress;PM=SR.PM;}
    void operator=(SceneResource& SR){Define=SR.Define;Resource=SR.Resource;Adress=SR.Adress;}
};

void SceneResource::LoadResource(POMain * P)
{
    //Error<<"Try Loading"<<endl;
    Resource.clear();
    for(std::map<std::string,std::string>::iterator Po=Define.begin();Po!=Define.end();++Po)
    {
        //Error<<"Creat "<<Po->second<<endl;
        Resource[Po->first]=P->CreatPicture(Po->second);
    }
    //Error<<"Loading Finish"<<endl;
}



void SceneResource::LoadScription(std::string K)
{
    Adress=K;
    FileFactor Tem;
    Tem.Separate(K);
    ScriptionBlock Oh(Tem.Begin(),Tem.End());
    std::string PreFile;
    std::string MainDefine;
    std::list<std::string> FileStack;
    for(CommentPoint PO=Oh.Begin();PO!=Oh.End();++PO)
    {
        if(PO->Is("FS"))//set the primer adress for all the follow rresource, it can be changed by run this again
            PreFile=PO->Scription();
        else if(PO->Is("AF"))// select next level adress of resource
            FileStack.push_back(PO->Scription());
        else if(PO->Is("PF"))// pop the newest level adress
        {
            if(!FileStack.empty())
                FileStack.pop_back();
        }else if(PO->Is("CF"))//clean all the adress , but do not clean primer adress
            FileStack.clear();
        else if(PO->Is("T"))//set the main define of the resource
            MainDefine=PO->Scription();
        else if(PO->Is("P")||PO->Is("SP")||PO->Is("B"))//realty
        {
            std::string O;
            for(OperatorPoint Po2=PO->Begin();Po2!=PO->End();++Po2)
            {
                O+=Po2->Detail();
            }
            std::string File=PreFile;
            for(std::list<std::string>::iterator Te=FileStack.begin();Te!=FileStack.end();++Te)
            {
                File+=*Te;
            }
            File+=PO->Scription();
            if(PO->Is("P"))
                Define[MainDefine+"_P_"+O]=File;
            else if(PO->Is("SP"))
                Define[MainDefine+"_SP_"+O]=File;
            else if(PO->Is("B"))
                Define[MainDefine+"_B_"+O]=File;
        }
    }
}

void SceneResource::CheckDetail(std::fstream &Tem, std::string Pre)
{
    Tem<<"Resource Scription At File <"<<Adress<<"> :"<<std::endl;
    for(std::map<std::string,std::string>::iterator Po=Define.begin();Po!=Define.end();++Po)
    {
        Tem<<"    <"<<Po->first<<">  Define To <"<<Po->second<<"> . "<<std::endl;
    }
}

#endif // SCENERESOURCE_H
