#ifndef BLACKSTAR_H
#define BLACKSTAR_H
#include "doublestarbase.h"
class BlackStar:public DoubleStarBase
{
public:
    static POTTF P;
    BlackStar(XYF Tem,float Ran,XYF T2,float Ran2):DoubleStarBase(Tem,Ran,T2,Ran2,0.533,0.4,0.69){}
    void Change(int T,StarBase* SB);
    void Display();
};
void BlackStar::Display()
{
    if(P)
    {
        P.DisplayMiddle(XYF(SB1.Location.X,SB1.Location.Y+SB1.Range),XYF(SB1.Range/2.0,0.0),SB1.Range*2.0,0.0,1.0,0.0);
        P.DisplayMiddle(XYF(SB2.Location.X,SB2.Location.Y+SB1.Range),XYF(SB2.Range/2.0,0.0),SB2.Range*2.0,0.0,1.0,0.0);
    }
    DoubleStarBase::Display();
}


void BlackStar::Change(int T,StarBase* SB)
{
    if(T==1)
    {
        XYF Te=SB1.Location-SB->Location;
        SB->Location=SB2.Location+Te.Uint(SB2.Range+SB->Range+0.02);
    }else if(T==2)
    {
        XYF Te=SB2.Location-SB->Location;
        SB->Location=SB1.Location+Te.Uint(SB1.Range+SB->Range+0.02);
    }
}
POTTF BlackStar::P;
#endif // BLACKSTAR_H
