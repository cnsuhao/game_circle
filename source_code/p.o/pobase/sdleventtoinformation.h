#ifndef SDLEVENTTOINFORMATION_H
#define SDLEVENTTOINFORMATION_H
#include <SDL2/SDL.h>
#include "../information.h"
#include "../handle.h"
Handle<Information> Translate(SDL_Event& Event)
{
    Handle<Information> Temporary=new Information;
    switch(Event.type)
    {
    case SDL_QUIT:
        Temporary->Category=INFEXIT;
        break;
    case SDL_KEYDOWN:
        Temporary->Category=INFKEYDOWN;
        Temporary->Data1.uc=Event.key.keysym.sym;
        break;
    case SDL_KEYUP:
        Temporary->Category=INFKEYUP;
        Temporary->Data1.uc=Event.key.keysym.sym;
        break;
    case SDL_MOUSEMOTION:
        Temporary->Category=MOUSEMOTION;
        Temporary->Data1.i=Event.button.x;
        Temporary->Data2.i=Event.button.y;
        Temporary->Data3.i=Event.motion.xrel;
        Temporary->Data4.i=Event.motion.yrel;
        break;
    case SDL_MOUSEBUTTONDOWN:
        Temporary->Category=MOUSEBUTTONDOWN;
        Temporary->Data1.i=Event.button.x;
        Temporary->Data2.i=Event.button.y;
        Temporary->Data3.i=Event.button.button;
        break;
    case SDL_MOUSEBUTTONUP:
        Temporary->Category=MOUSEBUTTONUP;
        Temporary->Data1.i=Event.button.x;
        Temporary->Data2.i=Event.button.y;
        Temporary->Data3.i=Event.button.button;
        break;
    /*case SDL_ACTIVEEVENT:
        if(Event.active.state==2)
            Temporary->Category=INFWINDOWDISACTIVE;
        else if(Event.active.state==6)
            Temporary->Category=INFWINDOWACTIVE;*/
    default :
        break;
    }
    return Temporary;
}

#endif // SDLEVENTTOINFORMATION_H
