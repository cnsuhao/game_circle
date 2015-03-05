#ifndef MOVESTAR_H
#define MOVESTAR_H
#include "starbase.h"
#include "starmove.h"
#include "../p.o/pottf.h"
class MoveStar:public StarBase
{
public:
    static POTTF P;
    bool Ready;
    StarMove SM;
    XYF Loc(){return Location;}
    void GetSpeed(const XYF& Tem){SM.GetSpeed(Tem);}
    void Launch(const XYF& Tem){Ready=true;GetSpeed(Tem);}
    MoveStar(XYF Tem,float Ran):StarBase(Tem,Ran,0.0,0.858,0.0){Ready=false;}
    void CleanAll(){SM.CleanAll();Ready=false;}
    void GetForce(const XYF& T){SM.GetForce(T);}
    float Range(){return StarBase::Range;}
    void Display()
    {
        if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range()),XYF(Range()/2.0,0.0),Range()*2.0,1.0,0.0,0.0);
        glBegin(GL_LINES);
        glColor4f(1.0,1.0,0.5,0.5);
        glVertex(Location);
        glVertex(SM.Force.Uint(0.1)+Location);
        glColor4f(0.0,1.0,0.5,0.5);
        glVertex(Location);
        glVertex(SM.Target+Location);
        glEnd();
        StarBase::Display();
    }

    void Assorial(const long& Ti)
    {
        if(Ready)
        {
            SM.Move(Ti,this);
            SM.CleanForce();
        }
    }
};
POTTF MoveStar::P;
#endif // MOVESTAR_H
