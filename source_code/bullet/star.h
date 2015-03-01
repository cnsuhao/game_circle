#ifndef DIY_STAR_H
#define DIY_STAR_H
#include "bullet.h"
class Star:public Bullet
{
    float Distance;
    XYZF Center;
    public:
        void Analyze(void *, long);
        Star(Handle<Personage> Tc,Coordinate& C,float Dis):Bullet(Tc,C,2.0),Center(C.Location),Distance(Dis){}
};
void Star::Analyze(void * C, long T)
{
    Realm* RB=static_cast<Realm*>(C);
    float Time=T/1000.0;
    if(IsLive(T))
    {
        TargetReflesh(RB,T);
        Location=Distance*sin(0.001*Live.Time)*Up+Front*(~Live)+Center;
        Center+=Front*Time*Speed;
        Judge();
    }
}

#endif // TAIJI_H
