#ifndef PLAYERSTAR_H
#define PLAYERSTAR_H
#include "starbase.h"
#include "starmove.h"
#include "../p.o/pottf.h"
#define LIVE_TIME 3000
class SmallPS :public StarBase
{
    XYF Target;
    long Time;
public:
    void Move(long T){Location+=T/1000.0*Target;Time+=T;if(Time>LIVE_TIME)Destory();}
    SmallPS(XYF L,XYF T):Time(0),StarBase(L,0.01,0.6,0.2,0.7),Target(T){}
    SmallPS(const SmallPS& P):Time(0),StarBase(P.Location,P.Range,P.R,P.G,P.B),Target(P.Target){}
};

class PlayerStar:public StarBase
{
public:
    static POTTF P;
    bool Genarl;
    bool Ready;
    bool Special;
    StarMove SM;
    long Time;
    XYF Loc(){return Location;}
    std::list<Handle<SmallPS> > TSP;
    void GetSpeed(const XYF& Tem){SM.GetSpeed(Tem);}
    void Launch(const XYF& Tem){Ready=true;GetSpeed(Tem);}
    PlayerStar(XYF Tem,float Ran):StarBase(Tem,Ran,0.0,0.0,1.0),Time(0){Ready=false;}
    void Set(const XYF &L, const float &Ra){StarBase::Set(L,Ra);Reset();}
    void Reset(){Genarl=false;Ready=false;Special=false;ChangeColor();TSP.clear();Time=0;}
    void ChangeColor(){if(!Genarl){R=0.0;G=0.0;B=1.0;}else{R=1.0;G=0.8;B=0.8;}}
    void CleanAll(){SM.CleanAll();Reset();}
    void GetForce(const XYF& T){SM.GetForce(T);}
    float Range(){return StarBase::Range;}
    void ChangeGenal(){if(Ready){Genarl=!Genarl;}ChangeColor();}
    void ChangeSpecial(){}
    bool IsSpecial(){return Special;}
    void CreatSmall(XYF Tem)
    {
        if(Time<=0)
        {
            SM.Target+=Tem.Uint(-0.1);
            Handle<SmallPS> Temx=new SmallPS(Location,Tem.Uint(0.6)+SM.Target);
            TSP.push_back(Temx);
            Time=100;
        }
    }

    void Display()
    {
        for(std::list<Handle<SmallPS> >::iterator Po=TSP.begin();Po!=TSP.end();++Po)
        {
            if(*Po) (*Po)->Display();
            else TSP.erase(Po--);
        }
        if(Special){if(P) P.DisplayMiddle(XYF(Location.X,Location.Y+Range()),XYF(Range()/2.0,0.0),Range()*2.0,0.0,0.5,0.0);}
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
            for(std::list<Handle<SmallPS> >::iterator Po=TSP.begin();Po!=TSP.end();++Po)
            {
                if(*Po) (*Po)->Move(Ti);
            }
            SM.Move(Ti,this);
            SM.CleanForce();
            if(Time>0)
                Time-=Ti;
        }
    }
};
POTTF PlayerStar::P;
#endif // PLAYERSTAR_H
