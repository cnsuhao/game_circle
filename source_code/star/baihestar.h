#ifndef BAIHESTAR_H
#define BAIHESTAR_H
#include "starbase.h"
class BaiheStar:public StarBase
{
public:
    static POTTF P;
    BaiheStar(XYF Tem,float Ran):StarBase(Tem,Ran,1.0,0.8,0.8){}
    BaiheStar(){}
    float Range(){return StarBase::Range;}
    void Display()
    {
        if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range()),XYF(Range()/2.0,0.0),Range()*2.0,1.0,0.0,0.0);
        StarBase::Display();
    }
};
POTTF BaiheStar::P;
#endif // BAIHESTAR_H
