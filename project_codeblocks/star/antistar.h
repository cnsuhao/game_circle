#ifndef ANTISTAR_H
#define ANTISTAR_H
#include "starbase.h"
#include "regularstar.h"
#include "../p.o/publicvalue.h"
class AntiStar:public StarBase
{
public:
    static POTTF P;
    AntiStar(XYF Tem,float Ran):StarBase(Tem,Ran,0.44,0.7,1.0){}
    AntiStar(){}
    float Range(){return StarBase::Range;}
    void Display()
    {
        if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range()),XYF(Range()/2.0,0.0),Range()*2.0,1.0,0.0,0.0);
        StarBase::Display();
    }
};
POTTF AntiStar::P;
#endif // ANTISTAR_H
