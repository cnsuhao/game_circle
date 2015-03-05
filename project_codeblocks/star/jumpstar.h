#ifndef JUMPSTAR_H
#define JUMPSTAR_H
#include "doublestarbase.h"
class JumpStar:public DoubleStarBase
{
    float Speed;
    XYF SB1T;
    XYF SB2T;
    XYF Center;
    float Time;
public:
    static POTTF P;
    void Display()
    {
    if(P)
    {
        P.DisplayMiddle(XYF(SB1.Location.X,SB1.Location.Y+SB1.Range),XYF(SB1.Range/2.0,0.0),SB1.Range*2.0,1.0,0.0,0.0);
        P.DisplayMiddle(XYF(SB2.Location.X,SB2.Location.Y+SB1.Range),XYF(SB2.Range/2.0,0.0),SB2.Range*2.0,1.0,0.0,0.0);
    }
        DoubleStarBase::Display();
    }

    JumpStar(XYF Tem,float Ran,XYF T2,float Ran2,float Sp,float St):DoubleStarBase(Tem,Ran,T2,Ran2,1.0,1.0,0.0)
    {
        XYF L1;
        XYF L2;
        L1=Tem;
        L2=T2;
        XYF T;
        T=(L2-L1);
        float L=T.Long();
        float R2=SB1.Range*SB1.Range;
        L=R2/(R2+SB2.Range*SB2.Range)*L;
        Center=T.Uint(L)+L1;
        SB1T=Center-L2;
        SB2T=Center-L1;
        Speed=Sp;
        Time=St;
    }
    void Accessorial(long T)
    {
        SB1.Location=Center+cos(Speed*3.141592653*Time)*SB1T;
        SB2.Location=Center+cos(Speed*3.141592653*Time)*SB2T;
        Time+=T/1000.0;
    }
};
POTTF JumpStar::P;
#endif // JUMPSTAR_H
