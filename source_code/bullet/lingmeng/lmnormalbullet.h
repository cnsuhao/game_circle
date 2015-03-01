#ifndef DIY_LINGMENGNORMALBULLET_H
#define DIY_LINGMENGNORMALBULLET_H
#include "../bullet.h"
#include "../../personage/bolilingmeng.h"
#include "../../p.o/picture.h"
#include "../../p.o/initer.h"
class LingMengNormalBullet:public Bullet
{
    public:
        static Picture3D Tex1;
        static Picture3D Tex2;
        static int ListMode;
        static void InitFunction(void);
        float Angle;
        void Main(Realm*,long T);
        LingMengNormalBullet(Handle<Personage> Tc,Coordinate& C):Bullet(Tc,C,10.0),Angle(0.0)
                                            {}
};

int LingMengNormalBullet::ListMode=0;
Picture3D LingMengNormalBullet::Tex1;
Picture3D LingMengNormalBullet::Tex2;

void LingMengNormalBullet::Main(Realm * RB, long T)
{
    glPushMatrix();
    AddMatrix(this);
    glRotatef(Angle,0.0,0.0,1.0);
    glColor3f(0.5,0.1,0.9);
    DrawAquare(XYZF(0.0,0.0,0.0),0.05,0.05,0.05);
    //glCallList(ListMode);
    glPopMatrix();
    Angle+=0.1*T;
    //Bullet::Show(C,T);
}

void LingMengNormalBullet::InitFunction()
{
    Tex1.Load("texture/lingmeng/bullet/normalshootrmb.jpg");
    //error<<"开始读取"<<endl;
    Tex2.Load("texture/lingmeng/bullet/normalshootrmbb.jpg");
    //error<<"完成读取"<<endl;
    ListMode=glGenLists(1);
    glNewList(ListMode,GL_COMPILE);
    Tex1.Show(XYZF(0.1,0.0,0.2),XYZF(0.0,0.0,-0.2),XYZF(-0.2,0.0,0.0));
    Tex2.Show(XYZF(-0.1,0.0,0.2),XYZF(0.0,0.0,-0.2),XYZF(0.2,0.0,0.0));
    glEndList();
}

InitNote LMNB(Ini_Sho,"LMNormalBullet",&LingMengNormalBullet::InitFunction);
#endif // BIGTAIJI_H
