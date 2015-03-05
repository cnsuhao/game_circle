#ifndef DOUBLESTARBASE_H
#define DOUBLESTARBASE_H
#include "starbase.h"
class DoubleStarBase:public HandleSeed
{
public:
    StarBase SB1;
    StarBase SB2;
    int Crash(StarBase*);
    DoubleStarBase(XYF Tem,float Ran,XYF T2,float Ran2,float R=1.0,float G=1.0,float B=1.0):SB1(Tem,Ran,R,G,B),SB2(T2,Ran2,R,G,B){}
    void Display();
};

void DoubleStarBase::Display()
{
    SB1.Display();
    SB2.Display();
    if(SB1.Location.Distance(SB2.Location)>SB1.Range+SB2.Range)
    {
        XYF T=SB1.Location-SB2.Location;
        float F=T.Long();
        XYF T1=T.Uint(SB1.Range)+SB2.Location;
        XYF T2=T.Uint(F-SB2.Range)+SB2.Location;
        glColor3f(SB1.R,SB1.G,SB1.B);
        glBegin(GL_LINES);
        glVertex(T1);
        glVertex(T2);
        glEnd();
    }
}

int DoubleStarBase::Crash(StarBase* SB)
{
    int R=0;
    if(SB->Location.Distance(SB1.Location)<SB->Range+SB1.Range)
        R=1;
    if(SB->Location.Distance(SB2.Location)<SB->Range+SB2.Range)
    {
        if(R==0) return 2;
        else if(R==1)
            return 3;
    }
    return R;
}

#endif // DOUBLESTARBASE_H
