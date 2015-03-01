#ifndef DIY_SDL_IMAGE_INIT_H
#define DIY_SDL_IMAGE_INIT_H
#include "controlcenter.h"
#include <SDL/SDL_image.h>
class SDL_IMAGE_FIRST_INIT
{
    public:
    SDL_IMAGE_FIRST_INIT()
    {
        std::fstream Error("allerror.txt",std::ios::out|std::ios::app);
        if(IMG_Init(IMG_INIT_JPG||IMG_INIT_PNG||IMG_INIT_TIF)<0)
        {
            Error<<"The SDL_image can not Init as your wish. Please Check your Developmental Environment ^.^"<<std::endl;
            Error<<"Or may be you can get something from here:"<<endl<<SDL_GetError()<<endl;
            Error.close();
            exit(0);
        }
        Error.close();
        atexit(IMG_Quit);
    }
}Just_For_SDL_Image_Init_And_Do_Not_Use_This;
#endif
