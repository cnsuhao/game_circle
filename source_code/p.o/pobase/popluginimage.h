#ifndef POPLUGINIMAGE_H
#define POPLUGINIMAGE_H
#include <SDL2/SDL_image.h>
#include "poplugin.h"
#include "pogi.h"
#include "../po.h"
class POPluginImage:public POPlugin
{
public:
    void Init(POGI*);
    static SDL_Texture* CP(std::string);
};

void POPluginImage::Init(POGI* K)
{
    if(IMG_Init(~0)<0)
    {
        POError::GetError(std::string("The SDL_image can not Init as your wish, Or may be you can get something from here:/n")+SDL_GetError(),-1);
    }
    POGI::CreatPictureFunction=&POPluginImage::CP;
    PO::ExitFunction(IMG_Quit);
}

SDL_Texture* POPluginImage::CP(std::string P)
{
    SDL_Texture* Picture = IMG_LoadTexture(PO::POPoint->GI()->MainSurface,P.c_str());
    //SDL_Surface* TT=SDL_DisplayFormatAlpha(Picture);
    //SDL_FreeSurface(Picture);
    return Picture;
}

#endif // POPLUGINIMAGE_H
