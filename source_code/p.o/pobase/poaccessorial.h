#ifndef POACCESSORIAL_H
#define POACCESSORIAL_H
#define DEFLUTINTERVAL 6
#include "../baseclass.h"
#include "../information.h"
class POAccessorial
{
    long RunTime;
    long IntervalTime;
public:
    int WindowW;
    int WindowH;
    long Time(){return IntervalTime;}
    void AccessorialStart();
    void AccessorialFinish();
    virtual void Exit(){}
    void SetAccessorialStart(){RunTime=SDL_GetTicks();IntervalTime=DEFLUTINTERVAL;}
};
void POAccessorial::AccessorialStart()
{
}

void POAccessorial::AccessorialFinish()
{
    IntervalTime=SDL_GetTicks()-RunTime;
    if(IntervalTime<DEFLUTINTERVAL)
    {
        SDL_Delay(DEFLUTINTERVAL-IntervalTime);
        IntervalTime=DEFLUTINTERVAL;
    }
    RunTime=SDL_GetTicks();
}
#undef DEFLUTINTERVAL
#endif // POACCESSORIAL_H
