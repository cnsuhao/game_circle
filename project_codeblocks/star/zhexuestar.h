#ifndef ZHEXUESTAR_H
#define ZHEXUESTAR_H
#include "starbase.h"
class ZhexueStar:public StarBase
{
public:
    static POTTF P;
    ZhexueStar(XYF Tem,float Ran):StarBase(Tem,Ran,1.0,0.0,0.0){}
    ZhexueStar(){}
    float Range(){return StarBase::Range;}
    void Display()
    {
        if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range()),XYF(Range()/2.0,0.0),Range()*2.0,1.0,0.0,0.0);
        StarBase::Display();
    }
};
POTTF ZhexueStar::P;
#endif // ZHEXUESTAR_H
