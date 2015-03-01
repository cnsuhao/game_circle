#ifndef NORMALSTAR_H
#define NORMALSTAR_H
class NormalStar:public StarBase
{
public:
    static POTTF P;
    NormalStar(XYF Tem,float Ran):StarBase(Tem,Ran,1.0,1.0,1.0){}
    NormalStar(){}
    float Range(){return StarBase::Range;}
    void Display()
    {
        if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range()),XYF(Range()/2.0,0.0),Range()*2.0,1.0,0.0,0.0);
        StarBase::Display();
    }
};
POTTF NormalStar::P;
#endif // NORMALSTAR_H
