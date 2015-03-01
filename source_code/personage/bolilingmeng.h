#ifndef DIY_BOLILINGMENG_H
#define DIY_BOLILINGMENG_H
#include <list>
#include "../personage/personage.h"
#include "../bullet/lingmeng/lmnormalbullet.h"
#include "../p.o/initer.h"
#include "../p.o/calculate.h"
#include "../bullet/lingmeng/taijibullet.h"
class LingMeng:public Personage
{
        float Angel;
    public:

        //“ı—Ù”„œ‡πÿ
        static int InitListMode;
        int NumberOfBall;
        static void InitFunction(void);
        std::list<Handle<TaiJiBullet> > BulletList;
        Calculate RechardBall;
        void NormalShoot(Realm*);
        void Main(Realm*,long);
        void Accessorial(Realm*,long);
        void AboutTheTaiJi(Realm*,long);
        LingMeng():Personage(PRESONAGE_LINGMENG),RechardBall(5000),NumberOfBall(0),Angel(0.0)
        {
            
            //SP.GetSpell(new StarSpell);
        }
};
int LingMeng::InitListMode=0;
void LingMeng::InitFunction(void)
{
    if(InitListMode==0)
    {
        InitListMode=glGenLists(1);
        glNewList(InitListMode,GL_COMPILE);
        glColor3f(1.0,1.0,0.0);
        DrawAquare(XYZF(0.0,0.6,0.0),0.3,0.3,0.3);
        DrawAquare(XYZF(0.35,0.0,0.0),0.05,0.3,0.05);
        DrawAquare(XYZF(-0.35,0.0,0.0),0.05,0.3,0.05);
        DrawAquare(XYZF(-0.15,-0.6,0.0),0.05,0.3,0.05);
        DrawAquare(XYZF(0.15,-0.6,0.0),0.05,0.3,0.05);
        glColor3f(1.0,0.0,0.0);
        DrawAquare(XYZF(0.0,0.0,0.0),0.3,0.3,0.2);
        glColor3f(1.0,1.0,1.0);
        glEndList();

    }
}

void LingMeng::NormalShoot(Realm* RB)
{
    Coordinate Tc;
    Tc.Location=Location+V.Front();
    Tc.Front=V.Front();
    Tc.Left=V.Left();
    Tc.Up=V.Up();
    Handle<Object> Ty=new LingMengNormalBullet(this,Tc);
    RB->GetObject(Ty);
}
void LingMeng::Main(Realm* C,long T)
{
    Realm* RB=static_cast<Realm*>(C);
    if(!FristPersonal())
    {
        glPushMatrix();
        float TemM[16];
        /*Coordinate Tem;
        Tem.Location=Location;
        Tem.Up=(RB->Up());
        Tem.Left=(RB->HorizontalU&Front).Uint();
        Tem.Front=(Left&RB->HorizontalU).Uint();*/
        ToGlMatrix(this,TemM);
        glMultMatrixf(TemM);
        //glCallList(InitListMode);
        Personage::Main(C,T);
        glColor3f(1.0,1.0,0.0);
        DrawAquare(XYZF(0.0,0.6,0.0),0.3,0.3,0.3);
        DrawAquare(XYZF(0.35,0.0,0.0),0.05,0.3,0.05);
        DrawAquare(XYZF(-0.35,0.0,0.0),0.05,0.3,0.05);
        DrawAquare(XYZF(-0.15,-0.6,0.0),0.05,0.3,0.05);
        DrawAquare(XYZF(0.15,-0.6,0.0),0.05,0.3,0.05);
        glColor3f(1.0,0.0,0.0);
        DrawAquare(XYZF(0.0,0.0,0.0),0.3,0.3,0.2);
        glColor3f(1.0,1.0,1.0);
        glPopMatrix();
    }
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    //error<<"ssfsdf"<<Location.Y<<endl;
    glVertex(Location);
    glVertex3f(Location.X,0.0f,Location.Z);
    glVertex3f(Location.X-0.5f,0.0f,Location.Z);
    glVertex3f(Location.X+0.5f,0.0f,Location.Z);
    glVertex3f(Location.X,0.0f,Location.Z-0.5f);
    glVertex3f(Location.X,0.0f,Location.Z+0.5f);
    glEnd();
    Personage::Main(C,T);
}
void LingMeng::AboutTheTaiJi(Realm *R,long T)
{
    if(NumberOfBall<=6)
    {
        RechardBall+T;
        if(RechardBall)
        {
            Coordinate Tc;
            Tc.Set(this);
            Handle<TaiJiBullet> Pc=new TaiJiBullet(this,Tc);
            NumberOfBall+=1;
            BulletList.push_front(Pc);
            RechardBall=0;
            R->GetObject(Pc);
        }
    }
}

void LingMeng::Accessorial(Realm* RB,long T)
{
    Personage::Accessorial(RB,T);
    AboutTheTaiJi(RB,T);
    float Tc=T/1000.0;
    Angel+=NumberOfBall*1.0*Tc;
    int Size;
    for(std::list<Handle<TaiJiBullet> >::iterator Po=BulletList.begin();Po!=BulletList.end();++Po,++Size)
    {
        (*Po)->Location=(Location+2.0*V.Up()*sin(6.28/NumberOfBall*Size+Angel)+2.0*V.Left()*cos(6.28/NumberOfBall*Size+Angel));
    }
}

InitNote LMIN(Ini_Sho,"LINGMENG",&LingMeng::InitFunction);
#endif
