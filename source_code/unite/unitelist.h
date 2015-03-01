#ifndef UNITELIST_H
#define UNITELIST_H
#include <string>
#include "../p.o/handle.h"
#include <map>
#include <list>
#include "unitestyle.h"
#include "listfile.h"
#include "../p.o/pobase/pomain.h"
class UniteList:public HandleSeed
{
public:
    std::set<std::string> UniteRelay;

    std::map<std::string,URStyle> DefineMap;

    std::map<std::string,ListFile> LFM;

    std::map<std::string,Handle<GLTexture> > PictureMap;
    std::map<std::string,Handle<GLList> > ListMap;

    void Unite(const std::string& K){UniteRelay.insert(K);}
    void Define(const std::string& P,const URStyle& T){DefineMap[P]=T;}
    bool IsRelay(const std::string& P){return UniteRelay.count(P)!=0;}
    bool IsHave(const std::string& K){return DefineMap.count(K)>0;}
    URStyle Find(const std::string&);
    void operator=(const UniteList& UL){UniteRelay=UL.UniteRelay;DefineMap=UL.DefineMap;}
    void CheckDetail(std::fstream& P,std::string Pre1="  ",std::string Pre2="       ");
    void CleanResource(){ListMap.clear();PictureMap.clear();}
    void Init(POMain *);
    void Picture(const std::string&,Handle<GLTexture>&);
    void List(const std::string&,Handle<GLList>&);
    Handle<GLTexture> Picture(const std::string&);
    Handle<GLList> List(const std::string&);
    void CleanUnuse();
};

void UniteList::CleanUnuse()
{
    for(std::map<std::string,ListFile>::iterator Po=LFM.begin();Po!=LFM.end();++Po)
    {
        Po->second.CleanUnuse();
    }
}


void UniteList::Picture(const std::string& S,Handle<GLTexture>& H)
{
    std::map<std::string,Handle<GLTexture> >::iterator Po=PictureMap.find(S);
    if(Po==PictureMap.end())
        PictureMap.insert(std::make_pair(S,H));
}

void UniteList::List(const std::string& S, Handle<GLList>& H)
{
    std::map<std::string,Handle<GLList> >::iterator Po=ListMap.find(S);
    if(Po==ListMap.end())
        ListMap.insert(std::make_pair(S,H));
}

Handle<GLTexture> UniteList::Picture(const std::string& S)
{
    std::map<std::string,Handle<GLTexture> >::iterator Po=PictureMap.find(S);
    if(Po==PictureMap.end())
    {
        Handle<GLTexture> Tem;
        return Tem;
    }else
        return Po->second;
}
Handle<GLList> UniteList::List(const std::string& S)
{
    std::map<std::string,Handle<GLList> >::iterator Po=ListMap.find(S);
    if(Po==ListMap.end())
    {
        Handle<GLList> Tem;
        return Tem;
    }else
        return Po->second;
}

void UniteList::Init(POMain * P)
{
    if(!DefineMap.empty())
    {
        for(std::map<std::string,URStyle>::iterator Po=DefineMap.begin();Po!=DefineMap.end();++Po)
        {
            if(Po->second.IsPicture())
            {
                Handle<GLTexture> Tem=P->CreatPicture(Po->second.Detail());
                PictureMap.insert(std::make_pair(Po->first,Tem));
            }else if(Po->second.IsList())
            {
                ListFile& TC=LFM[Po->first];
                TC.LoadScription(Po->second.Detail());
                TC.Init(P);
                Handle<GLList> Tc=TC.CreatList();
                ListMap.insert(std::make_pair(Po->first,Tc));
            }
        }
    }
}


URStyle UniteList::Find(const std::string& SS)
{
    std::map<std::string,URStyle >::iterator Po=DefineMap.find(SS);
    if(Po!=DefineMap.end())
    {
        return Po->second;
    }else{
        URStyle US;
       return US;
    }
}

void UniteList::CheckDetail(std::fstream &P, std::string Pre1, std::string Pre2)
{
    for(std::set<std::string>::iterator Po=UniteRelay.begin();Po!=UniteRelay.end();++Po)
        P<<Pre1<<"Relay To <"<<*Po<<">"<<std::endl;
    for(std::map<std::string,URStyle>::iterator Po=DefineMap.begin();Po!=DefineMap.end();++Po)
    {
        P<<Pre1<<"<"<<Po->first<<"> Define To"<<std::endl;
        Po->second.CheckDetail(P,"  "+Pre2);
    }
    for(std::map<std::string,ListFile>::iterator Po=LFM.begin();Po!=LFM.end();++Po)
    {
        Po->second.CheckDetail(P);
    }
}
#endif // UNITELIST_H
