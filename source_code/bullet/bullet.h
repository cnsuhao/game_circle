#ifndef DIY_BULLET_H
#define DIY_BULLET_H
#include "../p.o/baseclass.h"
#include "../object/object.h"

#include "../base/drawaquare.h"
#include "../realm/realm.h"
#include "../base/effect.h"
#include "../personage/personage.h"
#include "../event/bulletdamage.h"
#define BULLET_CHECK_RANGE 1.2*Range+0.5
class Personage;
class Bullet:public Object,public Effect
{
    public:
        static bool Initt;
        static int TextureMode;
        float Speed;
        Calculate Reflesh;
        Calculate Live;
        long Style;
        long Damage;
        Handle<Personage> Resource;
        Handle<Personage> Target;
        void NormalMove(float,float,Coordinate*);//time,itself
        inline void NormalMove(float T){NormalMove(T,Speed,this);}
        void FollowMove(float,float,float,Coordinate*,Coordinate*);//转弯系数，时间，速度，目标，自身 
        void FollowMove(float A,float T,Coordinate* O){FollowMove(A,T,Speed,O,this);}
        void RefleshDetail(Realm*);
        void TargetReflesh(Realm*,long T);
        bool IsLive(long T);
        void Judge(void);
        void Init(void*);
        virtual void Attack(Handle<Personage> Tc){if(Tc){Tc->GetEvent(new BulletDamage);}}//决定在触碰到目标后会发生什么事
        virtual void Main(Realm*,long );
        virtual void Accessorial(Realm*,long);
        void Base(Realm*,long);
        void FindTarget(Handle<Object>,float*);
        Bullet(Handle<Personage> Ter,Coordinate& C,float S,long E=10000,float Range=0.1):Object(OBJ_BULLET,Range),Resource(Ter),Speed(S),
                                                                                            Live(E),Reflesh(static_cast<long>(Range/(3.5*Speed)*1000))
        {
            Coordinate::Set(C);
        }
};
void Bullet::FindTarget(Handle<Object> P,float* Dis)
{
    if(P!=Resource)
    {
        float Tem=P->Location.Distance(Location)-P->Range-Range;
        if(Tem<(*Dis))
        {
            *Dis=Tem;
            Target=P;
        }
    }
}

bool Bullet::Initt=false;
int Bullet::TextureMode=0;
bool Bullet::IsLive(long T)
{
    Live+T;
    if(Live)
    {
        HandleSeed::Destory();
        Live=0;
        return false;
    }else{
        return true;
    }
}
void Bullet::Init(void *V)
{
    if(!Initt)
    {
        TextureMode=glGenLists(1);
        glNewList(TextureMode,GL_COMPILE);
        for(int i=0;i<10;++i)
        {
            if(i==0)
            {
                glBegin(GL_TRIANGLE_FAN);
                glColor3f(1.0,1.0,1.0);
                glVertex3f(0.0,0.0,1.0);
                glColor3f(1.0-i*0.1,1.0-i*0.1,1.0-i*0.1);
                for(int k=0;k<=10;++k)
                {
                    glVertex3f(sin((i+1)*0.31514926)*sin(-k*0.31415926*2),sin((i+1)*0.31514926)*cos(k*0.31415926*2),cos((i+1)*0.31415926));
                }
                glEnd();
            }else if(i==9)
            {
                glBegin(GL_TRIANGLE_FAN);
                glColor3f(0.0,0.0,0.0);
                glVertex3f(0.0,0.0,-1.0);
                glColor3f(1.0-i*0.1,1.0-i*0.1,1.0-i*0.1);
                for(int k=0;k<=10;++k)
                {
                    glVertex3f(sin(i*0.31514926)*sin(k*0.31415926*2),sin(i*0.31514926)*cos(k*0.31415926*2),cos(i*0.31415926));
                }
                glEnd();
            }else{
                glBegin(GL_QUAD_STRIP);
                for(int k=0;k<=10;++k)
                {
                    glColor3f(1.0-i*0.1,1.0-i*0.1,1.0-i*0.1);
                    glVertex3f(sin(i*0.31514926)*cos(k*0.31415926*2),sin(i*0.31514926)*sin(k*0.31415926*2),cos(i*0.31415926));
                    glColor3f(1.0-i*0.1-0.1,1.0-i*0.1-0.1,1.0-i*0.1-0.1);
                    glVertex3f(sin((i+1)*0.31514926)*cos(k*0.31415926*2),sin((i+1)*0.31514926)*sin(k*0.31415926*2),cos((i+1)*0.31415926));
                }
                glEnd();
            }
        }
        glEndList();
        Initt=true;
    }
}

void Bullet::Judge()
{
    if(Target)
    {
        if(Target->Coordinate::Location.Distance(this->Coordinate::Location)<(Target->Range+Range))
        {
            Attack(Target);
            HandleSeed::Destory();
        }
    }
}
void Bullet::Main(Realm* V,long T)
{
    glPushMatrix();
    AddMatrix(this,Range,Range,Range);
    //BulletDrawAquare(XYZF(0.0,0.0,0.0),0.1,0.1,0.1);
    glCallList(TextureMode);
    glPopMatrix();

}
void Bullet::TargetReflesh(Realm *RB,long T)
{
    Reflesh+T;
    if(Reflesh)
    {
        RefleshDetail(RB);
    }
}
void Bullet::Accessorial(Realm * RB, long T)
{
    float Time=T/1000.0;
    Base(RB,T);
    NormalMove(Time);
}
void Bullet::Base(Realm* RB,long T)
{
    IsLive(T);
    TargetReflesh(RB,T);
    Judge();
    if(RB->OutRealm(this->Location,this->Range))
    {
        Destory();
    }
}
void Bullet::RefleshDetail(Realm* RB)
{
    Target.Unused();
    float LastDistance=100000000.0;
    Train(OBJ_PERSONAGE,&Bullet::FindTarget,this,&LastDistance);
}
void Bullet::NormalMove(float T,float F,Coordinate* O)
{
    O->Location+=F*T*O->Front;
}
void Bullet::FollowMove(float Angle,float Time,float Spe,Coordinate* T,Coordinate* O)
{
    XYZF Vector=T->Location-O->Location;
    Vector=Vector.Uint();
    float Tem=Vector*O->Left;
    if(Tem>0.0)
    {
        O->Front=(sin(Angle*Time)*O->Left+cos(Angle*Time)*O->Front).Uint();
    }else if(Tem<0.0)
    {
        O->Front=(sin(-Angle*Time)*O->Left+cos(-Angle*Time)*O->Front).Uint();
    }
    Tem=Vector*O->Up;
    if(Tem>0.0)
    {
        O->Front=(sin(Angle*Time)*O->Up+cos(Angle*Time)*O->Front).Uint();
    }else if(Tem<0.0)
    {
        O->Front=(sin(-Angle*Time)*O->Up+cos(-Angle*Time)*O->Front).Uint();
    }
    O->Left=(O->Up&O->Front).Uint();
    O->Up=(O->Front&O->Left).Uint();
    O->Front=(O->Left&O->Up).Uint();
    NormalMove(Time,Spe,O);
}

#endif
