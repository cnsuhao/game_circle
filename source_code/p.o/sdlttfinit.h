#ifndef DIY_SDL_TTF_INIT_H
#define DIY_SDL_TTF_INIT_H
#include "controlcenter.h"
#include <SDL/SDL_ttf.h>
#include <string>
namespace PO_FONT
{
    bool FontReady=false;
    static TTF_Font *SDL_TTF_FONT;
    void SetFont(std::string File,int Size)
    {
        if(FontReady)
        {
            TTF_CloseFont(SDL_TTF_FONT);
            FontReady=true;
        }
        SDL_TTF_FONT=TTF_OpenFont(File.c_str(),Size);
        if(SDL_TTF_FONT==NULL)
            throw RunInitError("Your Font:  "+File+"  isn't exist!\n"+"Or may be you can get something from here: "+SDL_GetError());
        FontReady=true;
    }
}

class SDL_TTF_FIRST_INIT
{
    public:
        SDL_TTF_FIRST_INIT()
        {
            std::fstream Error("allerror.txt",std::ios::out|std::ios::app);
            if(TTF_Init()<0)
            {
                Error<<"This is something wrong!! The SDL_ttf can not Init as your wish. Please Check your Developmental Environment ^.^"<<std::endl;
                Error<<"Or may be you can get something from here: "<<std::endl<<SDL_GetError()<<std::endl;
                Error.close();
                exit(0);
            }
            Error.close();
            atexit( TTF_Quit );
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
            try{
                PO_FONT::SetFont("simhei.ttf",50);
            }catch(...)
            {}

        }
}Just_For_First_Init_SDL_TTF_And_Do_Not_Use_This;
#endif
