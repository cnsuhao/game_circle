#ifndef DIY_BIGTAIJI_H
#define DIY_BIGTAIJI_H
#include "bullet.h"
class BigTaiJiPlugin:public Bullet
{
    public:
    BigTaiJiPlugin(Handle<Personage> Tc, Coordinate &C):Bullet(Tc,C,4.0){}
};
class BigTaiJi:public Bullet
{
    int Plugin;
    Handle<Personage> ThisTarget;
    public:
        void Analyze(void *, long);
        //void Show(void *, long);
        BigTaiJi(Handle<Personage> Tc,Coordinate& C,Handle<Personage> Tz):Bullet(Tc,C,4.0,100000),Plugin(0),
                                            ThisTarget(Tz){}
};
/*void BigTaiJi::Show(void * C, long T)
{
    Realm* RB=static_cast<Realm*>(C);
    float Time=T/1000.0;
    if(LiveTime<=2000)
    {
        glColor3f(0.5,1.0,0.8);
        glBegin(GL_LINES);
        if(RB->ObjectListForShow.count(OBJ_PERSONAGE)>0)
        {
            std::list<Handle<Object> >& Tem=RB->ObjectListForShow[OBJ_PERSONAGE];
            std::list<Handle<Object> >::iterator Po;
            if(!Tem.empty())
            {
                for(Po=Tem.begin();Po!=Tem.end();++Po)
                {
                    if(*Po)
                    {
                        if((*Po)->Location.Distance(Resource->Location)<=Range)
                        {
                            glVertex(Location);
                            glVertex((*Po)->Location);
                        }
                    }
                }
            }
        }
        glEnd();
    }
    Bullet::Show(C,T);
}*/

void BigTaiJi::Analyze(void * C, long T)
{
    static float Angle=0.0;
    Realm* RB=static_cast<Realm*>(C);
    float Time=T/1000.0;
    Coordinate Tc;
    Tc.Location=Location;
    Tc.Up=Front;
    if(IsLive(T))
    {
        if(Live>=Plugin*250)
        {
            Plugin+=1;
            for(int i=0;i<10;++i)
            {
                Tc.Front=(sin(Angle+i*0.6283)*Up+cos(Angle+i*0.6283)*Left).Uint();
                Tc.Left=(Tc.Up&Tc.Front).Uint();
                Handle<Object> Ter=new BigTaiJiPlugin(Resource,Tc);
                RB->GetObject(Ter);
            }
        }
        TargetReflesh(RB,T);
        if(ThisTarget)
            FollowMove(0.15,Time,ThisTarget.Data);
        else
            NormalMove(Time);
        Judge();
        Angle+=Time*2.0;
    }
}
#endif // BIGTAIJI_H
