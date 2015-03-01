#ifndef DIY_TAIJIBULLET_H
#define DIY_TAIJIBULLET_H
#include "../bullet.h"
#include "../../personage/bolilingmeng.h"
#include "../../p.o/picture.h"
#include "../../p.o/initer.h"
class TaiJiBullet:public Bullet
{
    int Size;
    std::list<XYZF> Point;
    public:
    Calculate PointTime;
        static Picture3D Tex1;
        static Picture3D Tex2;
        static int ListMode;
        static void InitFunction(void);
        bool Mode;//when it is true, the spell is control this bullet
        float Angle;
        Calculate NorRechard;
        bool NorReady;
        void Main(Realm*,long T);
        void StartAttack(Handle<Personage> T);
        void Accessorial(Realm* C,long );
        TaiJiBullet(Handle<Personage> Tc,Coordinate& C):Bullet(Tc,C,4.0),Angle(0.0),Mode(false),NorRechard(200),NorReady(false),PointTime(50),Size(0)
                                            {}
};

int TaiJiBullet::ListMode=0;
Picture3D TaiJiBullet::Tex1;
Picture3D TaiJiBullet::Tex2;

void TaiJiBullet::StartAttack(Handle<Personage> T)
{
    Mode=true;
    Target=T;
}

void TaiJiBullet::Main(Realm* C, long T)
{
    Realm* RB=static_cast<Realm*>(C);
    glPushMatrix();
    AddMatrix(this);
    //glRotatef(Angle,0.0,0.0,1.0);
    glColor3f(0.5,1.0,0.2);
    DrawAquare(XYZF(0.0,0.0,0.0),0.1,0.1,0.1);
    //glCallList(ListMode);
    glPopMatrix();
    XYZF LL=this->Location;
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    for(std::list<XYZF>::reverse_iterator Po=Point.rbegin();Po!=Point.rend();++Po)
    {
        glVertex(LL);
        glVertex(*Po);
        LL=*Po;
    }
    glEnd();
    Angle+=0.1*T;
    //Bullet::Show(C,T);
}

void TaiJiBullet::Accessorial(Realm * RB, long T)
{
    PointTime+T;
    if(PointTime)
    {
        if(Size>=10)
        {
            Point.pop_front();
            Point.push_back(this->Location);
        }else{
            Point.push_back(this->Location);
            Size+=1;
        }
        PointTime=0;
    }
    if(Resource)
    {
        float Time=T/1000.0;
        if(!Mode)
        {
            /*XYZF Tc=this->Location-Resource->Location;
            double Pc=Tc.Long();
            if(Pc>2.5)
            {
                FollowMove(1,Time,1.0,Resource,this);
            }else if(Pc<2.0)
            {
                float Tem=Tc*this->Left;
                if(Tem>0.0)
                {
                    this->Front=(sin(1.0*Time)*this->Left+cos(1.0*Time)*this->Front).Uint();
                }else if(Tem<0.0)
                {
                    this->Front=(sin(-1.0*Time)*this->Left+cos(-1.0*Time)*this->Front).Uint();
                }
                Tem=Tc*this->Up;
                if(Tem>0.0)
                {
                    this->Front=(sin(1.0*Time)*this->Up+cos(1.0*Time)*this->Front).Uint();
                }else if(Tem<0.0)
                {
                    this->Front=(sin(-1.0*Time)*this->Up+cos(-1.0*Time)*this->Front).Uint();
                }
                this->Left=(this->Up&this->Front).Uint();
                this->Up=(this->Front&this->Left).Uint();
                this->Front=(this->Left&this->Up).Uint();
                NormalMove(Time,1.0,this);
            }else{
                NormalMove(Time,0.5,this);
            }*/
            if(!NorReady)
            {
                NorRechard+T;
                if(NorRechard)
                {
                    NorReady=true;
                    NorRechard=0;
                }
            }
            if(Resource)
            {
                if(Resource->Shoot&&NorReady)
                {
                    Coordinate Tc;
                    if(Resource->L.LockReady)
                    {
                        Tc.Set(this);
                        XYZF Yu=Resource->L.Target->Location-this->Location;
                        Tc.Front=Yu.Uint();
                        Tc.Left=(Tc.Up&Tc.Front).Uint();
                        Tc.Up=(Tc.Front&Tc.Left).Uint();
                    }else{
                        Tc.Set(this);
                        Tc.Front=Resource->V.Front();
                        Tc.Left=Resource->V.Left();
                        Tc.Up=Resource->V.Up();
                    }
                    Handle<Bullet> Pc=new LingMengNormalBullet(Resource,Tc);
                    RB->GetObject(Pc);
                    NorReady=false;
                }
            }
        }else{
            Base(RB,T);
            FollowMove(1,Time,Target);
        }
    }else{
        Destory();
    }
}
void TaiJiBullet::InitFunction()
{
    /*Tex1.Load("texture\\lingmeng\\bullet\\normalshootrmb.jpg");
    //error<<"开始读取"<<endl;
    Tex2.Load("texture\\lingmeng\\bullet\\normalshootrmbb.jpg");
    //error<<"完成读取"<<endl;
    ListMode=glGenLists(1);
    glNewList(ListMode,GL_COMPILE);
    Tex1.Show(XYZF(0.1,0.0,0.2),XYZF(0.0,0.0,-0.2),XYZF(-0.2,0.0,0.0));
    Tex2.Show(XYZF(-0.1,0.0,0.2),XYZF(0.0,0.0,-0.2),XYZF(0.2,0.0,0.0));
    glEndList();*/
}


InitNote LMTJB(Ini_Sho,"TaijiBullet",&TaiJiBullet::InitFunction);
#endif // BIGTAIJI_H
