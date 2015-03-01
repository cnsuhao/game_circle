#ifndef POGISDL_H
#define POGISDL_H
#include "pogi.h"
#include "../po.h"
class SDLData:public POGIData
{
public:
    XYF Display(XYF,XYF,XYF,float,float,float);
    void Delete(){SDL_FreeSurface(static_cast<SDL_Surface*>(Data.Data3.v));}
    SDLData(){Data.Data3.ui=0;}
};

XYF SDLData::Display(XYF SP, XYF T,XYF L, float R, float B, float G)
{
    SDL_Rect Tem;
    Tem.x=static_cast<int>((SP.X+1.0)*(PO::GetGI()->WindowW/2));
    Tem.y=static_cast<int>((1.0-SP.Y)*(PO::GetGI()->WindowH/2));
    Tem.w=static_cast<unsigned int>(((T+L).X+1.0)*(PO::GetGI()->WindowW/2));
    Tem.h=static_cast<unsigned int>((1.0-(T+L).Y)*(PO::GetGI()->WindowH/2));
    SDL_BlitSurface(static_cast<SDL_Surface*>(Data.Data3.v), NULL, PO::GetGI()->MainSurface, &Tem);
    return SP+T;
}

/*XYZF SDLData::Display(XYZF SP, XYZF T,XYZF L, float R, float B, float G)
{

    return SP+T;
}*/

class POGISDL:protected POGI
{
    POGISDL(){}
public:
    static Handle<POGI> Agent(){return new POGISDL();}
    void Clear();
    void CreatWindow(PO*);
    void UpData();
    void DisplayManage(PO*);
    virtual Handle<POGIData> CreatPicture(std::string);
    virtual Handle<POGIData> CreatTTF(std::string){}
};

Handle<POGIData> POGISDL::CreatPicture(std::string K)
{
    Handle<POGIData> Tem=new SDLData();
    SDL_Surface* Picture=(*POGI::CreatPictureFunction)(K);
    Tem->Data.Data1.ui = Picture->w;
    Tem->Data.Data2.ui = Picture->h;
    Tem->Data.Data3.v=static_cast<void*>(Picture);
    return Tem;
}


void POGISDL::DisplayManage(PO* p)
{
    UpData();
    Clear();
    for(Tank<Handle<Plugin> >::Ladle Po=p->Library.Begin();!p->Library.IsEnd(Po);++Po)
    {
        if(*Po)
        {
            (*Po)->Layer2D(p);
        }
    }
}
void POGISDL::Clear()
{
        SDL_FillRect(MainSurface, NULL, SDL_MapRGB(MainSurface->format, 0, 0, 0));
}
void POGISDL::CreatWindow(PO*)
{
    //Creat();
    MainSurface = SDL_SetVideoMode( WindowW, WindowH, 0, SDL_Flag);
}
void POGISDL::UpData()
{
        SDL_Flip (MainSurface);
}

#endif // POGISDL_H
