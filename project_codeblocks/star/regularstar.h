#ifndef REGULARSTAR_H
#define REGULARSTAR_H
#include "starbase.h"
class RegularStar:public StarBase
{
public:
    static POTTF P;
    RegularStar(XYF Tem,float Ran):StarBase(Tem,Ran,0.6,0.6,0.0){}
    RegularStar(){}
    float Range(){return StarBase::Range;}
    void Display()
    {
        if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range()),XYF(Range()/2.0,0.0),Range()*2.0,1.0,0.0,0.0);
        StarBase::Display();
    }
};
POTTF RegularStar::P;
#endif // REGULARSTAR_H
