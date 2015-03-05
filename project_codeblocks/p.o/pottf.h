#ifndef POTTF_H
#define POTTF_H
#include "pobase/gltexture.h"
#include "baseclass.h"
class POTTF
{
    void SetPoint(float* C,XYF T){C[0]=T.X;C[1]=T.Y;}
    void SetPoint(float* C,XYZF T){C[0]=T.X;C[1]=T.Y;C[2]=T.Z;}
public:
    Handle<GLTexture> Data;
    POTTF(Handle<GLTexture> P):Data(P){}
    POTTF(POTTF& C):Data(C.Data){}
    POTTF(const POTTF& P):Data(P.Data){}
    POTTF operator= (Handle<GLTexture> P){Data=P;return *this;}
    POTTF (){}
    operator bool(){return Data;}
    void Display(XYF P,XYF T,float,float R=1.0,float G=1.0,float B=1.0);
    void DisplayMiddle(XYF P,XYF T,float,float R=1.0,float G=1.0,float B=1.0);
};
void POTTF::Display(XYF P, XYF T,float S, float R, float G, float B)
{
    bool Shendu=glIsEnabled(GL_BLEND);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    static float Tx[]={0.0,0.0,0.0,1.0,1.0,1.0,1.0,0.0};
    static float Lx[8];
    XYF Tem=T.Uint(S*0.4*Data->Size);
    XYF Tem2(Tem.Y,-Tem.X);
    Tem2=Tem2.Uint(S);
    SetPoint(&Lx[0],P);
    SetPoint(&Lx[2],P+Tem2);
    SetPoint(&Lx[4],P+Tem+Tem2);
    SetPoint(&Lx[6],P+Tem);
    float Cx[12];
    for(int i=0;i<4;++i)
    {
        Cx[i*3]=R;
        Cx[i*3+1]=B;
        Cx[i*3+2]=G;
    }
    unsigned int K[]={0,1,2,3};
    Data->Display(PO_QUADS,Tx,2,Lx,2,Cx,3,K,4);
    if(!Shendu)
        glDisable(GL_BLEND);
}
void POTTF::DisplayMiddle(XYF P, XYF T, float S, float R, float G, float B)
{
    XYF Tem=P-T.Uint(Data->Size/2.0*S*0.4);
    Display(Tem,T,S,R,G,B);
}
#endif // POTTF_H
