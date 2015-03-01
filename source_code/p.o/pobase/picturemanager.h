#ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H
#include "pomain.h"
class PictureManager
{
    std::map<std::string,Handle<GLTexture> > DefinePicture;
    //std::map<std::string,handle<GLList> > DefineList;
public:
     Handle<GLTexture> CreatPicture(std::string,POMain* K);
    void RelasePicture(POMain*);
    PictureManager(){}
    PictureManager(PictureManager& PM):DefinePicture(PM.DefinePicture){}
    PictureManager(const PictureManager& PM):DefinePicture(PM.DefinePicture){}
    void operator=(PictureManager& PM){DefinePicture=PM.DefinePicture;}
};

Handle<GLTexture>  PictureManager::CreatPicture(std::string S, POMain *K)
{
    if(DefinePicture.count(S)>0)
    {
        return DefinePicture[S];
    }else{
        Handle<GLTexture> Tem=K->CreatPicture(S);
        DefinePicture.insert(std::make_pair(S,Tem));
        return Tem;
    }
}

void PictureManager::RelasePicture(POMain * P)
{
    if(!DefinePicture.empty())
    {
        std::string Tem;
        for(std::map<std::string,Handle<GLTexture> >::iterator Po=DefinePicture.begin();Po!=DefinePicture.end();++Po)
        {
            Tem=Po->first;
            Po->second.Unused();
            P->DeletePicture(Tem);
        }
        DefinePicture.clear();
    }
}

#endif // PICTUREMANAGER_H
