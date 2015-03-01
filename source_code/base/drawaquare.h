#ifndef DIY_DRAWAQUARE_H
#define DIY_DRAWAQUARE_H
#include "../p.o/baseclass.h"
#include "../p.o/glsimplify.h"
inline void DrawAquare(XYZF L,float X,float Y,float Z)
{
    glBegin(GL_QUADS);
    glVertex(L+XYZF(-X,Y,Z));
    glVertex(L+XYZF(-X,-Y,Z));
    glVertex(L+XYZF(X,-Y,Z));
    glVertex(L+XYZF(X,Y,Z));


    glVertex(L+XYZF(X,-Y,-Z));
    glVertex(L+XYZF(-X,-Y,-Z));
    glVertex(L+XYZF(-X,Y,-Z));
    glVertex(L+XYZF(X,Y,-Z));


    glVertex(L+XYZF(X,Y,Z));
    glVertex(L+XYZF(X,-Y,Z));
    glVertex(L+XYZF(X,-Y,-Z));
    glVertex(L+XYZF(X,Y,-Z));



    glVertex(L+XYZF(-X,Y,-Z));
    glVertex(L+XYZF(-X,Y,Z));
    glVertex(L+XYZF(X,Y,Z));
    glVertex(L+XYZF(X,Y,-Z));



    glVertex(L+XYZF(-X,-Y,-Z));
    glVertex(L+XYZF(-X,-Y,Z));
    glVertex(L+XYZF(-X,Y,Z));
    glVertex(L+XYZF(-X,Y,-Z));





    glVertex(L+XYZF(X,-Y,Z));
    glVertex(L+XYZF(-X,-Y,Z));
    glVertex(L+XYZF(-X,-Y,-Z));
    glVertex(L+XYZF(X,-Y,-Z));




    
    glEnd();
}
inline void BulletDrawAquare(XYZF L,float X,float Y,float Z)
{
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    glVertex(L+XYZF(-X,Y,Z));
    glVertex(L+XYZF(-X,-Y,Z));
    glVertex(L+XYZF(X,-Y,Z));
    glVertex(L+XYZF(X,Y,Z));

    glColor3f(0.5,0.5,0.5);
    glVertex(L+XYZF(X,-Y,-Z));
    glVertex(L+XYZF(-X,-Y,-Z));
    glVertex(L+XYZF(-X,Y,-Z));
    glVertex(L+XYZF(X,Y,-Z));

    glColor3f(1.0,0.0,1.0);
    glVertex(L+XYZF(X,Y,Z));
    glVertex(L+XYZF(X,-Y,Z));
    glVertex(L+XYZF(X,-Y,-Z));
    glVertex(L+XYZF(X,Y,-Z));


    glColor3f(1.0,0.0,1.0);
    glVertex(L+XYZF(-X,Y,-Z));
    glVertex(L+XYZF(-X,Y,Z));
    glVertex(L+XYZF(X,Y,Z));
    glVertex(L+XYZF(X,Y,-Z));


    glColor3f(1.0,0.0,1.0);
    glVertex(L+XYZF(-X,-Y,-Z));
    glVertex(L+XYZF(-X,-Y,Z));
    glVertex(L+XYZF(-X,Y,Z));
    glVertex(L+XYZF(-X,Y,-Z));




    glColor3f(1.0,0.0,1.0);
    glVertex(L+XYZF(X,-Y,Z));
    glVertex(L+XYZF(-X,-Y,Z));
    glVertex(L+XYZF(-X,-Y,-Z));
    glVertex(L+XYZF(X,-Y,-Z));




    
    glEnd();
}
#endif
