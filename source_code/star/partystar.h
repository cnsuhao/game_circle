#ifndef PARTYSTAR_H
#define PARTYSTAR_H
#include "starbase.h"
class PartyStar:public StarBase
{
public:
    static float* PD;
    static unsigned int* O;
    static bool Init;
    PartyStar(XYF Tem,float Ran):StarBase(Tem,Ran,0.0,0.8,0.0)
    {
        if(!Init)
        {
            PD=new float[(POINT_NUMBER+1)*2];
            O=new unsigned int[POINT_NUMBER+2];
            for(int i=0;i<POINT_NUMBER;++i)
            {
                PD[i*2]=cos(PI2/(POINT_NUMBER)*i);
                PD[i*2+1]=sin(PI2/(POINT_NUMBER)*i);
            }
            PD[POINT_NUMBER*2]=0.0;
            PD[POINT_NUMBER*2+1]=0.0;
            O[0]=POINT_NUMBER;
            O[POINT_NUMBER+1]=0;
            for(int i=1;i<=POINT_NUMBER;++i)
            {
                O[i]=i-1;
            }
            Init=true;
        }
    }
    PartyStar(){}
    float Range(){return StarBase::Range;}
    void Display()
    {
        glColor4f(0.0,0.8,0.0,0.8);
        glPushMatrix();
        glTranslatef(Location.X,Location.Y,0.0);
        glScalef(Range(),Range(),1.0);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2,GL_FLOAT,0,PD);

            glDrawElements(GL_TRIANGLE_FAN,(POINT_NUMBER+2), GL_UNSIGNED_INT,O);

        glDisableClientState(GL_VERTEX_ARRAY);

        glPopMatrix();
        StarBase::Display();
    }
};
float* PartyStar::PD;
unsigned int* PartyStar::O;
bool PartyStar::Init=false;
#endif // PARTYSTAR_H
