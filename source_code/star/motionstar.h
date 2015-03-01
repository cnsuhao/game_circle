#ifndef REPULSIONSTAR_H
#define REPULSIONSTAR_H
#include "starbase.h"
#include "regularstar.h"
class MotionStar:public StarBase
{
    
public:
    static POTTF P;
    float MA;
    MotionStar(XYF Tem,float Ran,float A):StarBase(Tem,Ran,1.0,0.4,0.0),MA(A){}
    void Set(XYF Tem,float Ran,float A){StarBase::Set(Tem,Ran,1.0,0.4,0.0);MA=A;}
    void Display()
    {
        if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range),XYF(Range/2.0,0.0),Range*2.0,0.0,1.0,0.0);
        StarBase::Display();
    }
};
POTTF MotionStar::P;
#endif // REPULSIONSTAR_H
