#ifndef POMAIN_H
#define POMAIN_H
#include <string>
#include "../handle.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#ifdef POGL_GLES2
#include <SDL2/SDL_opengles2.h>
#include <GLES2/gl2.h>
#define GLESSTYLE
#else
#ifdef POGL_GLES
#include <SDL2/SDL_opengles.h>
#include <GLES/gl.h>
#define GLESSTYLE
#else
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#endif
#include "../poerror.h"
#include "gltexture.h"
#include "language.h"
#define DEFLUTINTERVAL 10

class POMain
{
    friend class PO;
    long RunTime;
    long IntervalTime;
    void MainFinish();
    void MainStart();
    SDL_Window* MainSurface;
    SDL_Renderer *MainRenderer;
    SDL_GLContext GLContext;
    std::string Title;
    int WindowW;
    int WindowH;
    TTF_Font *SDL_TTF_FONT;
    std::map<std::string,Handle<GLTexture> > AdressToHandle;
    std::map<std::string,int > AdressCalculate;
    void CreatWindow();
    Handle<GLTexture> CreatPictureDetail(std::string K);
public:
    long Time(){return IntervalTime;}
    SDL_Window* Window(){return MainSurface;}
    SDL_Renderer* Renderer(){return MainRenderer;}
    Handle<GLTexture> CreatPicture(std::string K);
    Handle<GLTexture> CreatTTF(std::string K){return CreatTTF(K,SDL_TTF_FONT);}
    Handle<GLTexture> CreatTTF(std::string K,TTF_Font* P){return CreatTTFUTF8(Translate(K),P);}
    Handle<GLTexture> CreatTTFUTF8(std::string S,TTF_Font* P);
    Handle<GLTexture> CreatTTFUTF8(std::string P){return CreatTTFUTF8(P,SDL_TTF_FONT);}
    XYF GetFloatMouse(int K,int Y){XYF Tem2(K*2.0/WindowW-1.0,1.0-Y*2.0/WindowH); return Tem2;}
    XYF GetFloatMouse(Information* I){return GetFloatMouse(I->Data1.i,I->Data2.i);}
    XYF GetFloatMouseMove(Information* I){return XYF(I->Data3.i*2.0/WindowW,-I->Data4.i*2.0/WindowH);}
    void SetMainStart(){RunTime=SDL_GetTicks();}
    POMain():RunTime(0),IntervalTime(DEFLUTINTERVAL),Title("PO FrameWord"),WindowW(640),WindowH(480){}
    static int CalculateSize(std::string);
    virtual void Exit(){TTF_CloseFont(SDL_TTF_FONT);}
};
Handle<GLTexture> POMain::CreatTTFUTF8(std::string S, TTF_Font *P)
{
    std::map<std::string,Handle<GLTexture> >::iterator Po=GLTexture::TextureMap.find(S);
    if(Po!=GLTexture::TextureMap.end())
        return Po->second;
    else{
        Handle<GLTexture> Tem;
        SDL_Surface* Picture = TTF_RenderUTF8_Blended(P,S.c_str(),(SDL_Color){255,255,255} );
        if(Picture)
        {
            SDL_Surface* Picturenew=SDL_ConvertSurfaceFormat(Picture,SDL_PIXELFORMAT_ABGR8888,0);
            if(Picturenew)
            {
                unsigned int T;
                glGenTextures(1,&T);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,T);
                gluBuild2DMipmaps(GL_TEXTURE_2D,4,Picturenew->w,Picturenew->h,GL_RGBA,GL_UNSIGNED_BYTE,Picturenew->pixels);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                glDisable(GL_TEXTURE_2D);
                Tem=new GLTexture(S,T);
                Tem->W=Picturenew->w;
                Tem->H=Picturenew->h;
                Tem->Size=CalculateSize(S);
            }
            SDL_FreeSurface(Picturenew);
        }else
            POError::GetError("TTF Font Is Not Available",3);
        SDL_FreeSurface(Picture);
        return Tem;
    }

}


void POMain::CreatWindow()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    MainSurface= SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WindowW,WindowH,SDL_WINDOW_OPENGL );
    MainRenderer=SDL_CreateRenderer(MainSurface, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    GLContext = SDL_GL_CreateContext(MainSurface);
    SDL_GL_SetSwapInterval(1);
}

int POMain::CalculateSize(std::string K)
{
    bool Dou=false;
    int Cal=0;
    int CalChar=0;
    for(std::string::iterator Po=K.begin();Po!=K.end();++Po)
    {
        unsigned int KK=*Po;
        if(CalChar==0)
        {
            if(*Po>0)
                CalChar=1;
            else
            {
                if(*Po>(int)0xfffffffc)
                    CalChar=6;
                else if(*Po>(int)0xfffffff8)
                    CalChar=5;
                else if(*Po>(int)0xfffffff0)
                    CalChar=4;
                else if(*Po>(int)0xffffffe0)
                    CalChar=3;
                else if(*Po>(int)0xffffffc0)
                    CalChar=2;
                Dou=true;
            }
        }
        if(CalChar==1)
        {
            if(Dou)
            Cal+=2;
            else Cal+=1;
            Dou=false;
        }
        --CalChar;
    }
    return Cal;
}

void POMain::MainStart()
{
    IntervalTime=SDL_GetTicks()-RunTime;
    RunTime=SDL_GetTicks();
    SDL_GL_SwapWindow(MainSurface);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void POMain::MainFinish()
{
    IntervalTime=SDL_GetTicks()-RunTime;
    if(IntervalTime<DEFLUTINTERVAL)
    {
        SDL_Delay(DEFLUTINTERVAL-IntervalTime);
        IntervalTime=DEFLUTINTERVAL;
    }
}

Handle<GLTexture> POMain::CreatPicture(std::string P)
{
    std::map<std::string,Handle<GLTexture> >::iterator Po=GLTexture::TextureMap.find(P);
    if(Po!=GLTexture::TextureMap.end())
        return Po->second;
    else{
        Handle<GLTexture> Tem=CreatPictureDetail(P);
        return Tem;
    }
}


Handle<GLTexture> POMain::CreatPictureDetail(std::string K)
{
    Handle<GLTexture> Tem;
    SDL_Surface* Picture = IMG_Load(K.c_str());
    if(Picture)
    {
        SDL_Surface* Picturenew=SDL_ConvertSurfaceFormat(Picture,SDL_PIXELFORMAT_ABGR8888,0);
        if(Picturenew)
        {
            //Error<<"Creat Picture "<<K<<endl;
            unsigned int T;
            glGenTextures(1,&T);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,T);
            gluBuild2DMipmaps(GL_TEXTURE_2D,4,Picturenew->w,Picturenew->h,GL_RGBA,GL_UNSIGNED_BYTE,Picturenew->pixels);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glDisable(GL_TEXTURE_2D);
            Tem=new GLTexture(K,T);
            Tem->W=Picturenew->w;
            Tem->H=Picturenew->h;
        }
        SDL_FreeSurface(Picturenew);
    }else
        POError::GetError("Picture File<"+K+"> Can not Find!",3);
    SDL_FreeSurface(Picture);
    return Tem;
}

void SetColorPoint(float *F,float R,float G,float B,float A,int Size)
{
    for(int i=0;i<Size;++i)
    {
        F[i*4]=R;F[i*4+1]=G;F[i*4+2]=B;F[i*4+3]=A;
    }
}
#undef DEFLUTINTERVAL
#endif // POMAIN_H
