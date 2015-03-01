#ifndef DIY_STARSPELL_SL_H
#define DIY_STARSPELL_SL_H
#include "bullet.h"
class StarSpellSmallStar:public Bullet
{
    public:
        StarSpellSmallStar(Handle<Personage> Ter,Coordinate& C):Bullet(Ter,C,3.0,6000){}
};
class StarSpellLeader:public Bullet
{
    public:
        StarSpellLeader(Handle<Personage> Ter,Coordinate& C):Bullet(Ter,C,6.0,4000){}
};
class StarSpellBullet:public Bullet
{
    bool Follow;
    Coordinate Center;
    Calculate RefleshP;
    Calculate Small;
    Handle<Object> Ter;
    public:
        StarSpellBullet(Handle<Personage> Ter,Coordinate& C):Bullet(Ter,C,4.0,20000),Follow(false),Center(C),RefleshP(100),Small(1000){}
        void Analyze(void*,long);
        void Show(void*,long);
};
void StarSpellBullet::Show(void* V,long T)
{
    Bullet::Show(V,T);
    glColor3f(1.0,1.0,0.0);
    DrawAquare(Center.Location,0.3,0.3,0.3);
}
void StarSpellBullet::Analyze(void* V,long T)
{
    Realm* RB=static_cast<Realm*>(V);
    float Time=(float)T/1000.0;
    Base(RB,T);
    //Coordinate::Set(Center);
    RefleshP+T;
    //error<<"�׶�1"<<endl;
    if(RefleshP)
    {
        Ter.Unused();
        //error<<"С�׶�1"<<endl;
        if(RB->Find(OBJ_BULLET))
        {
            std::list<Handle<Object> > &P=RB->ObjectList[OBJ_BULLET];
            //error<<"С�׶�2"<<endl;
            Handle<StarSpellLeader> SSL;
            std::list<Handle<Object> >::iterator Po;
            //error<<"С�׶�3"<<endl;
            for(Po=P.begin();Po!=P.end();++Po)
            {
                SSL=*Po;
                if(SSL)
                {
                    if(SSL->Resource==Resource)
                    {
                        //error<<"����"<<endl;
                        Ter=*Po;
                    }
                    //error<<"�ٶȾͻ�����������"<<endl;
                }
                //error<<"С�׶�5"<<endl;
            }
            //error<<"С�׶�6"<<endl;
        }
        RefleshP=0;
    }
    //error<<"�׶�2"<<endl;
    if(Ter)
    {
        FollowMove(1.0,Time,Speed,Ter.Data,&Center);
    }else{
        NormalMove(Time,Speed,&Center);
    }
    //error<<"�׶�3"<<endl;
    Location=Center.Location+1.5*sin((~Live)*20.0*6.291)*Center.Up+1.5*cos((~Live)*20.0*6.291)*Center.Left;
    Front=Speed*Center.Front+(float)(Bullet::Live.NeedTime)/500.0*6.291*cos((~Live)*20.0*6.291)*Center.Up
               -(float)(Bullet::Live.NeedTime)/500.0*6.291*sin((~Live)*20.0*6.291)*Center.Left;
    Front=Front.Uint();
    Up=(Front&Center.Front).Uint();
    Left=(Up&Front).Uint();
    Small+T;
    //error<<"�׶�4"<<endl;
    if(Small)
    {
        Coordinate Tp;
        Tp.Location=Location;
        Tp.Up=-1.0*Front;
        for(int i=0;i<5;++i)
        {
            Tp.Front=(cos(i/5.0*3.141592653)*Left+sin(i/5.0*3.141592653)*Up).Uint();
            Tp.Left=(Tp.Up&Tp.Front).Uint();
            Handle<Object> Tv=new StarSpellSmallStar(Resource,Tp);
            RB->GetObject(Tv);
        }
        Small=0;
    }
    //error<<"�׶�5"<<endl;
}
#endif
