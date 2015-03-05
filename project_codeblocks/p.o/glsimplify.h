#ifndef DIY_GLSIMPLIFY_H
#define DIY_GLSIMPLIFY_H
#include "baseclass.h"
//部分GL函数简化，与XYZF 和XYF 兼容 
inline float Abs(float r)
{
    if(r>=0)
    return r;
    else
    return -r;
}
inline void glVertex(const float* tte,int Tem=1)
{
    glVertex3f(*(tte+(Tem-1)*3),*(tte+(Tem-1)*3+1),*(tte+(Tem-1)*3+2));
}
inline void glVertex(const XYZF& Tem)
{
    glVertex3f(Tem.X,Tem.Y,Tem.Z);
}
inline void glVertex(const XYF& Tem)
{
    glVertex2f(Tem.X,Tem.Y);
}
inline void glVertex(const float& X,const float& Y)
{
    glVertex2f(X,Y);
}
inline void PT(XYZF Tem)
{
    float Temm=Abs(Tem.X)+Abs(Tem.Y)+Abs(Tem.Z);
    glColor3f(Abs(Tem.X/Temm)*2,Abs(Tem.Y/Temm)*2,Abs(Tem.Z/Temm)*2);
    glVertex3f(Tem.X,Tem.Y,Tem.Z);
}
inline void glNormal(XYZF Tem)
{
    glNormal3f(Tem.X,Tem.Y,Tem.Z);
}
inline void glColor(XYZF Tem)
{
    glColor3f(Tem.X,Tem.Y,Tem.Z);
}
inline void gluLookAt(XYZF V1,XYZF V2,XYZF V3)
{
    gluLookAt(V1.X,V1.Y,V1.Z,V2.X,V2.Y,V2.Z,V3.X,V3.Y,V3.Z);
}
void ToGlMatrix(Coordinate* C,float* F,float X=1.0,float Y=1.0,float Z=1.0)
{
    F[0]=C->Left.X*X;
    F[1]=C->Left.Y*X;
    F[2]=C->Left.Z*X;
    F[3]=0.0;
    F[4]=C->Up.X*Y;
    F[5]=C->Up.Y*Y;
    F[6]=C->Up.Z*Y;
    F[7]=0.0;
    F[8]=C->Front.X*Z;
    F[9]=C->Front.Y*Z;
    F[10]=C->Front.Z*Z;
    F[11]=0.0;
    F[12]=C->Location.X;
    F[13]=C->Location.Y;
    F[14]=C->Location.Z;
    F[15]=1.0;
}
void AddMatrix(Coordinate* C,float X=1.0,float Y=1.0,float Z=1.0)
{
    float M[16];
    ToGlMatrix(C,M,X,Y,Z);
    glMultMatrixf(M);
}
#endif
