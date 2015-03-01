#ifndef DIY_TAIJI_H
#define DIY_TAIJI_H
#include "../p.o/baseclass.h"
#include "bullet.h"
class Personage;
class TaiJi:public Bullet
{
    Handle<Personage> ThisTarget;
    float Angle;
    bool FreeFly;
    public:
        XYZF Center;
        //void Move(Realm *, float);
        void Analyze(void *, long);
        //void Show(void *, long);
        TaiJi(Handle<Personage> Tc,Coordinate& C,Handle<Personage> Tz):Bullet(Tc,C,2.0,10000),Center(C.Location),ThisTarget(Tz),Angle(0.0),FreeFly(false){}
};
void TaiJi::Analyze(void * C, long T)
{
    Realm* RB=static_cast<Realm*>(C);
    float Time=T/1000.0;
    if(IsLive(T))
    {
        TargetReflesh(RB,T);
        if(Live>=2000)
        {
            if(!FreeFly)
            {
                Front=(cos(Angle)*Left-sin(Angle)*Front).Uint();
                FreeFly=true;
            }
            if(ThisTarget)
                FollowMove(1.0,Time,ThisTarget.Data);
            else
                NormalMove(Time);
        }else{
            Location=Center+((~Live)*2.0+1.0)*(sin(Angle)*Left+cos(Angle)*Front).Uint();
        }
        Judge();
        Angle+=2.0*Time;
    }
}

#endif // TAIJI_H
