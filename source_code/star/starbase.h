#ifndef STARBASE_H
#define STARBASE_H
#include <math.h>
#include "../p.o/baseclass.h"
#include "../p.o/handle.h"
#include "../p.o/glsimplify.h"
#include "../p.o/pottf.h"
#define POINT_NUMBER 40
#define PI2 6.283184
class StarBase:public HandleSeed
{
public:
    XYF Location;
    float Range;
    float R,B,G;
    static bool Init;
    static float* Point;
    static unsigned int* Order;
    XYF& Loc(){return Location;}
    void Set(const XYF& L,const float& Ra,const float &RC=1.0,const float & GC=1.0,const float & BC=1.0){Location=L;Range=Ra;R=RC;G=GC;B=BC;}
    bool Crash(StarBase* SB){return Location.Distance(SB->Location)<Range+SB->Range;}
    StarBase(const XYF& Tem,const float& S,float RC=1.0,float GC=1.0,float BC=1.0):Location(Tem),Range(S),R(RC),G(GC),B(BC)
    {
        if(!Init)
        {
            Point=new float[POINT_NUMBER*2];
            Order=new unsigned int[POINT_NUMBER];
            for(int i=0;i<POINT_NUMBER;++i)
            {
                Point[i*2]=cos(PI2/(POINT_NUMBER)*i);
                Point[i*2+1]=sin(PI2/(POINT_NUMBER)*i);
                Order[i]=i;
            }
            Init=true;
        }
    }
    StarBase()
    {
        if(!Init)
        {
            Point=new float[POINT_NUMBER*2];
            Order=new unsigned int[POINT_NUMBER];
            for(int i=0;i<POINT_NUMBER;++i)
            {
                Point[i*2]=cos(PI2/(POINT_NUMBER)*i);
                Point[i*2+1]=sin(PI2/(POINT_NUMBER)*i);
                Order[i]=i;
            }
            Init=true;
        }
    }
    float Distance(StarBase* SB){return SB->Location.Distance(Location);}
    float Distance(StarBase& SB){return SB.Location.Distance(Location);}
    void Display();
};

bool StarBase::Init=false;
float* StarBase::Point;
unsigned int* StarBase::Order;

void StarBase::Display()
{
    glColor3f(R,G,B);
    glPushMatrix();
    glTranslatef(Location.X,Location.Y,0.0);
    glScalef(Range,Range,1.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2,GL_FLOAT,0,Point);

        glDrawElements(GL_LINE_LOOP,POINT_NUMBER, GL_UNSIGNED_INT,Order);

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

#endif // STARBASE_H
