#ifndef POGIGLES_H
#define POGIGLES_H
#include "pogidata.h"
#include "pogi.h"
class GLESData:public POGIData
{
public:
    XYF Display(XYF,XYF,XYF,float,float,float);
    XYZF Display(XYZF,XYZF,XYZF, float, float, float);
    void Delete(){if(Data.Data3.ui!=0)glDeleteTextures(1,&Data.Data3.ui);}
    GLESData(){Data.Data3.ui=0;}
};

XYF GLESData::Display(XYF SP, XYF T,XYF L, float R, float B, float G)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Data.Data3.ui);
    glColor3f(R,B,G);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);     glVertex(SP);
        glTexCoord2f(0.0,1.0);       glVertex(SP+L);
        glTexCoord2f(1.0,1.0);         glVertex(SP+L+T);
        glTexCoord2f(1.0,0.0);       glVertex(SP+T);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    return SP+T;
}

XYZF GLESData::Display(XYZF SP, XYZF T,XYZF L, float R, float B, float G)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Data.Data3.ui);
    glColor3f(R,B,G);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);     glVertex(SP);
        glTexCoord2f(0.0,1.0);       glVertex(SP+L);
        glTexCoord2f(1.0,1.0);         glVertex(SP+L+T);
        glTexCoord2f(1.0,0.0);       glVertex(SP+T);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    return SP+T;
}

class POGIGLES:protected POGI
{
protected:
    float Angle;
    float NearSize,FarSize;
    POGIGLES():Angle(100),NearSize(0.0005),FarSize(1000.0){}
public:
    static Handle<POGI> Agent(){return new POGIGLES();}
    void Clear();
    void CreatWindow(PO*);
    void UpData();
    void DisplayManage(PO*);
    virtual Handle<POGIESData> CreatPicture(std::string);
    virtual Handle<POGIESData> CreatTTF(std::string){}
};

Handle<POGIData> POGIGLES::CreatPicture(std::string K)
{
    Handle<POGIData> Tem=new GLData();
    SDL_Surface* Picture=(*POGI::CreatPictureFunction)(K);
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

void POGIGLES::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
void POGIGLES::CreatWindow(PO *)
{
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );//设定GL的初始属性，想使用GL的话必须用这个，其中参数自己百度
    MainSurface = SDL_SetVideoMode( WindowW, WindowH, 32, SDL_OPENGL|SDL_Flag); // 同上，设定属性的另一函数，必要。其参数自己百度
}
void POGIGLES::UpData()
{
    SDL_GL_SwapBuffers();//强制输出，刷屏。
}
void POGIGLES::DisplayManage(PO* p)
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
#endif // POGIGLES_H
