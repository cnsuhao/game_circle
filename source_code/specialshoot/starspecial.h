#ifndef DIY_STARSPECIAL_H
#define DIY_STARSPECIAL_H
#include "specialshoot.h"
#include "../bullet/star.h"
class StarSpecial:public SpecialShoot
{
    int Num;
    public:
        void Analyze(Personage*,Realm*,long,bool& B);
        StarSpecial():SpecialShoot(1000),Num(5){}
        
};
void StarSpecial::Analyze(Personage* P,Realm* RB,long T,bool& B)
{
    Base(P,RB,T,B);
    if(SS==SS_USING)
    {
        Coordinate Tc;
        Tc.Front=P->Front;
        Tc.Location=P->Location+P->Front;
        for(int i=0;i<Num;++i)
        {
            XYZF Tar=2.0*(sin(i*6.2831/Num)*P->Left+cos(i*6.2831/Num)*P->Up);
            XYZF Tk=(P->Front&Tar).Uint();
            for(int k=-4;k<=4;++k)
            {
                XYZF Ter=Tar+(k/4.5*2.0*tan(6.2831/Num))*Tk;
                float Di=Ter.Long();
                Tc.Up=(Ter).Uint();
                Tc.Left=(Tc.Up&Tc.Front).Uint();
                Handle<Object> Yu=new Star(P,Tc,Di);
                RB->GetObject(Yu);
            }
        }
        Num+=1;
        if(Num>9)
        {
            Num=5;
        }
        Finish(P,RB,B);
    }
}
#endif
