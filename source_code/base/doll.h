#ifndef DOLL_H
#define DOLL_H
#include "../p.o/ControlCenter.h"
#include "../p.o/baseclass.h"
inline void SetPoint(GLfloat* T,float K,float P,float C)
{
    T[0]=K;T[1]=P;T[2]=C;
}

void DrawQuad(XYZF Center,XYZF F,XYZF L,XYZF Up)
{
    glBegin(GL_QUADS);
    glVertex(Center+F+Up+L);
    glVertex(Center+F-Up+L);
    glVertex(Center+F-Up-L);
    glVertex(Center+F+Up-L);

    glVertex(Center-F+Up+L);
    glVertex(Center-F-Up+L);
    glVertex(Center-F-Up-L);
    glVertex(Center-F+Up-L);

    glVertex(Center-F+Up+L);
    glVertex(Center-F-Up+L);
    glVertex(Center+F-Up+L);
    glVertex(Center+F+Up+L);

    glVertex(Center-F+Up-L);
    glVertex(Center-F-Up-L);
    glVertex(Center+F-Up-L);
    glVertex(Center+F+Up-L);

    glVertex(Center-F+Up+L);
    glVertex(Center-F+Up-L);
    glVertex(Center+F+Up-L);
    glVertex(Center+F+Up+L);

    glVertex(Center-F-Up+L);
    glVertex(Center-F-Up-L);
    glVertex(Center+F-Up-L);
    glVertex(Center+F-Up+L);

    glEnd();
}

class Doll
{
    Coordinate Lo;
public:
    void Show();
};
void Doll::Show()
{
    XYZF Center=Lo.Location+XYZF(0.0,0.5,0.15);
    XYZF F(0.0,0.0,0.7*0.8);
    XYZF L(0.7,0.0,0.0);
    XYZF UpV(0.0,0.5,0.0);
    glColor3f(1.0,1.0,0.9);
    DrawQuad(Center,F,L,UpV);
    glColor3f(0.2,0.1,0.3);
    Center=Lo.Location+XYZF(0.0,-0.35,0.0);
    F.Set(0.0,0.0,0.4*0.8);
    L.Set(0.5,0.0,0.0);
    UpV.Set(0.0,0.35,0.0);
    DrawQuad(Center,F,L,UpV);
    glColor3f(1.0,0.5,0.1);
    XYZF Cen(0.0,-1.1,0.0);
    GLfloat Up=0.4;
    GLfloat Left=0.5;
    GLfloat Front=0.4*0.8;
    GLfloat FD=0.56;
    GLfloat LD=0.7;
    GLfloat Sp[36];
    SetPoint(&Sp[0],Cen.X-Left,Cen.Y+Up,Cen.Z+Front);
    SetPoint(&Sp[3],Cen.X+Left,Cen.Y+Up,Cen.Z+Front);
    SetPoint(&Sp[6],Cen.X+Left,Cen.Y+Up,Cen.Z-Front);
    SetPoint(&Sp[9],Cen.X-Left,Cen.Y+Up,Cen.Z-Front);
    SetPoint(&Sp[12],Cen.X-Left,Cen.Y-Up,Cen.Z+FD);
    SetPoint(&Sp[15],Cen.X+Left,Cen.Y-Up,Cen.Z+FD);
    SetPoint(&Sp[18],Cen.X+LD,Cen.Y-Up,Cen.Z+Front);
    SetPoint(&Sp[21],Cen.X+LD,Cen.Y-Up,Cen.Z-Front);
    SetPoint(&Sp[24],Cen.X+Left,Cen.Y-Up,Cen.Z-FD);
    SetPoint(&Sp[27],Cen.X-Left,Cen.Y-Up,Cen.Z-FD);
    SetPoint(&Sp[30],Cen.X-LD,Cen.Y-Up,Cen.Z-Front);
    SetPoint(&Sp[33],Cen.X-LD,Cen.Y-Up,Cen.Z+Front);
    GLint K[][4]={{0,1,2,3},
                  {1,2,7,6},
                  {5,4,0,1},
                  {0,3,10,11},
                  {9,8,2,3},
                  {1,1,5,6},
                  {8,2,2,7},
                  {3,3,9,10},
                  {4,11,0,0}};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0,Sp);
    glDrawElements(GL_QUADS, 36, GL_UNSIGNED_INT,K);




    /*Center=Lo.Location+XYZF(0.0,-1.1,0.0);
    F.Set(0.0,0.0,0.8*0.65);
    L.Set(0.8,0.0,0.0);
    Up.Set(0.0,0.4,0.0);
    DrawQuad(Center,F,L,Up);
    Center=Lo.Location+XYZF(0.0,1.5,0.0);
    F.Set(0.0,0.0,0.9*0.65);
    L.Set(0.9,0.0,0.0);
    Up.Set(0.0,0.5,0.0);
    DrawQuad(Center,F,L,Up);
    glColor3f(1.0,0.0,0.0);
    Center=Lo.Location+XYZF(-0.3,-1.8,-0.15);
    F.Set(0.0,0.0,0.24*0.65);
    L.Set(0.24,0.0,0.0);
    Up.Set(0.0,0.18,0.0);
    DrawQuad(Center,F,L,Up);
    Center=Lo.Location+XYZF(0.3,-1.8,-0.15);
    F.Set(0.0,0.0,0.24*0.65);
    L.Set(0.24,0.0,0.0);
    Up.Set(0.0,0.18,0.0);
    DrawQuad(Center,F,L,Up);
    glColor3f(1.0,1.0,0.7);
    Center=Lo.Location+XYZF(0.7,-0.4,-0.15);
    F.Set(0.0,0.0,0.4);
    L.Set(0.1,0.0,0.0);
    Up.Set(0.0,0.2,0.0);
    DrawQuad(Center,F,L,Up);
    Center=Lo.Location+XYZF(-0.7,-0.4,-0.15);
    F.Set(0.0,0.0,0.4);
    L.Set(0.1,0.0,0.0);
    Up.Set(0.0,0.2,0.0);
    DrawQuad(Center,F,L,Up);*/
}

#endif // DOLL_H
