#ifndef POPLUGINTTF_H
#define POPLUGINTTF_H
#include <SDL2/SDL_ttf.h>
#include "../poerror.h"
#include "poplugin.h"
#include "pogi.h"
#include "language.h"
class POPluginTTF:public POPlugin
{
    std::string FontAdress;
    static TTF_Font *SDL_TTF_FONT;
public:
    virtual void Set(std::string K){FontAdress=K;}
    void Init(POGI*);
    static SDL_Surface* CP(std::string);
    ~POPluginTTF(){if(SDL_TTF_FONT!=NULL){TTF_CloseFont(SDL_TTF_FONT);SDL_TTF_FONT=NULL;}}
};
TTF_Font* POPluginTTF::SDL_TTF_FONT;
void POPluginTTF::Init(POGI* K)
{
    if(TTF_Init()<0)
    {
        POError::GetError(std::string("The SDL_TTF can not Init as your wish, Or may be you can get something from here:/n")+SDL_GetError(),-1);
    }
    K->CreatTTFFunction=&POPluginTTF::CP;
    PO::ExitFunction( TTF_Quit );
    SDL_TTF_FONT=TTF_OpenFont(FontAdress.c_str(),60);
}

SDL_Surface* POPluginTTF::CP(std::string P)
{
    SDL_Surface* Picture = TTF_RenderUTF8_Blended(POPluginTTF::SDL_TTF_FONT,Translate(P).c_str(),(SDL_Color){255,255,255} );
    //SDL_Surface* TT=SDL_DisplayFormatAlpha(Picture);
    //SDL_FreeSurface(Picture);
    return Picture;
}
#endif // POPLUGINTTF_H
