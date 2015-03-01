#ifndef POOPENGL_H
#define POOPENGL_H
#include "pogi.h"
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include "../po.h"
#include "pogidata.h"
#include "../glsimplify.h"
class GLData:public POGIData
{
    
public:
    void Display(unsigned int ES, float *TxP, int TSize, float *LoP, int LSize, float *Cop, int CSize,unsigned int* Order,unsigned int All);
    void Delete(){if(Data.Data3.ui!=0)glDeleteTextures(1,&Data.Data3.ui);std::cout <<"Delete FInish !"<<std::endl;}
    //GLData(std::string K):Adress(K){Data.Data3.ui=0;}
};

void GLData::Display(unsigned int ES, float *TxP, int TSize, float *LoP, int LSize, float *Cop, int CSize,unsigned int* Order,unsigned int All)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(LSize,GL_FLOAT,0,LoP);
    glColorPointer(CSize,GL_FLOAT,0,Cop);
    glTexCoordPointer(TSize,GL_FLOAT,0,TxP);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Data.Data3.ui);
    switch(ES)
    {
    case PO_QUADS:
        glDrawElements(GL_QUADS,All, GL_UNSIGNED_INT,Order);
        break;
    }
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

class POGIGL:protected POGI
{
protected:
    SDL_GLContext GLContext;
    float Angle;
    float NearSize,FarSize;
    POGIGL():Angle(100),NearSize(0.0005),FarSize(1000.0){}
public:
    static Handle<POGI> Agent(){return new POGIGL();}
    void Clear();
    void CreatWindow(PO*);
    void UpData();
    void DisplayManage(PO*);
    virtual Handle<POGIData> CreatPictureDetail(std::string);
    virtual Handle<POGIData> CreatTTF(std::string);
};

Handle<POGIData> POGIGL::CreatTTF(std::string P)
{
    Handle<POGIData> Tem=new GLData();
    Tem->Data.Data4.i=POMain::CalculateSize(P);
    Error<<"Creating POGIGL"<<(int)CreatPictureFunction<<endl;
    SDL_Surface* Picture=(*POGI::CreatTTFFunction)(P);
    Error<<(int)CreatPictureFunction<<endl;
    Tem->Data.Data1.ui = Picture->w;
    Tem->Data.Data2.ui = Picture->h;
    glGenTextures(1,&Tem->Data.Data3.ui);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Tem->Data.Data3.ui);
    gluBuild2DMipmaps(GL_TEXTURE_2D,4,Picture->w,Picture->h,GL_BGRA,GL_UNSIGNED_BYTE,Picture->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glDisable(GL_TEXTURE_2D);
    SDL_FreeSurface(Picture);
    return Tem;
}

Handle<POGIData> POGIGL::CreatPictureDetail(std::string K)
{
    Error<<"Using POGIGL CPD"<<endl;
    Handle<POGIData> Tem=new GLData();
    Error<<"Finish 4"<<endl;
        Error<<"Creating POGIGL"<<(int)CreatPictureFunction<<endl;
    SDL_Texture* Picture=(*POGI::CreatPictureFunction)(K);
        Error<<"Creating POGIGL"<<(int)CreatPictureFunction<<endl;
    Error<<"Finish 1"<<endl;
    Tem->Data.Data1.ui = Picture->w;
    Tem->Data.Data2.ui = Picture->h;
    glGenTextures(1,&Tem->Data.Data3.ui);
    glEnable(GL_TEXTURE_2D);
    Error<<"Finish 2"<<endl;
    glBindTexture(GL_TEXTURE_2D,Tem->Data.Data3.ui);
    gluBuild2DMipmaps(GL_TEXTURE_2D,4,Picture->w,Picture->h,GL_BGRA,GL_UNSIGNED_BYTE,Picture->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glDisable(GL_TEXTURE_2D);
    Error<<"Finish  3"<<endl;
    SDL_FreeSurface(Picture);
    Error<<"Finish"<<endl;
    return Tem;
}

void POGIGL::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
void POGIGL::CreatWindow(PO *)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

        /* Create our window centered at 512x512 resolution */
        MainSurface= SDL_CreateWindow("PO Framework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            512, 512, SDL_WINDOW_OPENGL );
         Renderer=SDL_CreateRenderer(MainSurface, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        GLContext = SDL_GL_CreateContext(MainSurface);
        SDL_GL_SetSwapInterval(1);

}
void POGIGL::UpData()
{
    SDL_GL_SwapWindow(MainSurface);
}
void POGIGL::DisplayManage(PO* p)
{
    UpData();
    Clear();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Angle,static_cast<float>(WindowW)/WindowH,NearSize,FarSize);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for(Tank<Handle<Plugin> >::Ladle Po=p->Library.Begin();!p->Library.IsEnd(Po);++Po)
    {
        if(*Po)
        {
            (*Po)->Layer3D(p);
        }
    }
    for(Tank<Handle<Plugin> >::Ladle Po=p->Library.Begin();!p->Library.IsEnd(Po);++Po)
    {
        if(*Po)
        {
            (*Po)->LayerBland(p);
        }
    }
    for(Tank<Handle<Plugin> >::Ladle Po=p->Library.Begin();!p->Library.IsEnd(Po);++Po)
    {
        if(*Po)
        {
            (*Po)->LayerSpecial(p);
        }
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for(Tank<Handle<Plugin> >::Ladle Po=p->Library.Begin();!p->Library.IsEnd(Po);++Po)
    {
        if(*Po)
        {
            (*Po)->Layer2D(p);
        }
    }
}
#endif // POOPENGL_H
