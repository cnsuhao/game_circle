#ifndef POPICTURE_H
#define POPICTURE_H
#include "pobase/gltexture.h"
float DefultPOPictureTextureCoor[8]={0.0,0.0,0.0,1.0,1.0,1.0,1.0,0.0};
float DefultPOPictureTextureLocation[16];
float DefultPOPictureTextureColor[16];
class POPicture
{
public:
    Handle<GLTexture> Data;
    POPicture(Handle<GLTexture> P):Data(P){}
    POPicture(POPicture& C):Data(C.Data){}
    POPicture(const POPicture& C):Data(C.Data){}
    void operator= (Handle<GLTexture> P){Data=P;}
    void operator= (POPicture K){Data=K.Data;}
    POPicture (){}
    operator bool(){return Data;}
    void Display(XYF P,XYF T,XYF U,float R=1.0,float G=1.0,float B=1.0,float A=1.0);
    void Unused(){Data.Unused();}
    void SetPoint(float* C,XYF T){C[0]=T.X;C[1]=T.Y;}
    void SetPoint(float* C,XYZF T){C[0]=T.X;C[1]=T.Y;C[2]=T.Z;}
};
void POPicture::Display(XYF P, XYF T, XYF U, float R, float G, float B,float A)
{
    SetPoint(&DefultPOPictureTextureLocation[0],P);
    SetPoint(&DefultPOPictureTextureLocation[2],P+U);
    SetPoint(&DefultPOPictureTextureLocation[4],P+T+U);
    SetPoint(&DefultPOPictureTextureLocation[6],P+T);
    SetColorPoint(DefultPOPictureTextureColor,R,G,B,A,4);
    bool Tem=glIsEnabled(GL_BLEND);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    unsigned int K[]={0,1,2,3};
    Data->Display(PO_QUADS,DefultPOPictureTextureCoor,2,DefultPOPictureTextureLocation,2,DefultPOPictureTextureColor,4,K,4);
    if(!Tem)
        glDisable(GL_BLEND);
}
/*void POPicture::Display(XYZF P, XYZF T, XYZF U, float R, float G, float B)
{
    Data->Display(P,T,U,R,G,B);
}*/
#endif // POPICTURE_H
