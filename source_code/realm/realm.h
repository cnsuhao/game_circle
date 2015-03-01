#ifndef DIY_REALM_H
#define DIY_REALM_H
#include <map>
#include <list>
#include "../p.o/handle.h"
#include "../personage/personage.h"
#include "../bullet/bullet.h"
#include "../tool/tool.h"
#include "../p.o/calculate.h"
#include "../p.o/plugin.h"
#define Multiply(X) ((X)*(X))


#define REALM_BOLI 45
#define REALM_BIG_INF_LEFT 45
#define REALM_BIG_INF_INSIDE 47
#define REALM_MIDDLE_INF_LEFT 40
#define REALM_SMALL_INF_LEFT 12

#define Rea_OuR 0x1
#define Rea_In 0x2
#define Rea_FTW   0x3//means the object have to change fly to walk
#define Rea_WTF   0x4 //means the object can change walk to fly

class Realm:public Plugin
{
public:
    Tank<Personage> TPL;
    Tank<Bullet> TBL;
    Tank<Tool> TTL;
    Handle<Realm> Return;
    Handle<Realm> Next;
    bool Avalible;
    bool CrashLand(Object& L,XYZF T,XYZF& R){if(L.Location.Y+T.Y-L.Range<=0){R.Set(T.X,0.0-L.Location.Y+L.Range,T.Z);return true;}else{return false;}}
    bool OutRealm(XYZF K,float R=1.0){if(HorizontalU.Location.Distance(K)+R<100.0&&K.Y-R>=0.0f)return false;else return true;}
    virtual void Layer3D(POMain*){}
    virtual void Layer2d(POMain*){}
    virtual void Accessorial(POAccessorial *){}
    void Get(){if(K) UB.Employ(K);}
    void Disapear();
    Handle<Realm> CreatNext(Handle<Realm> K){if(K){K->Return=this;NextRealm+=1;Transfer(K,OBJ_PERSONAGE);}return K;}
    Realm():Avalible(true){}
};

void Realm::Disapear()
{
    if(Avalible)
    {
        if(Return)
        {
            for(Tank<Personage>::Ladle Po=TPL.Begin();!TPL.IsEnd(Po);++Po)
            {
                Return->Get(*Po);
                TPL.PopFront();
            }
            for(Tank<Bullet>::Ladle Po=TBL.Begin();!TBL.IsEnd(Po);++Po)
            {
                Return->Get(*Po);
                TBL.PopFront();
            }
            Return->Avalible=true;
        }
    }else{
        if(Next)
        {
            Next->Return=Return;
        }
    }
}

void Realm::Transfer(Handle<Realm> K)
{
    if(Avalible)
    {
        if(K)
        {
            Next=K;
            K->Return=this;
            for(Tank<Personage>::Ladle Po=TPL.Begin();!TPL.IsEnd(Po);++Po)
            {
                K->Get(*Po);
                TPL.PopFront();
            }
            for(Tank<Bullet>::Ladle Po=TBL.Begin();!TBL.IsEnd(Po);++Po)
            {
                K->Get(*Po);
                TBL.PopFront();
            }
            Avalible=false;
        }
    }
}
void Realm::ShowObject(long Time)
{
    UB.Train(OBJ_PERSONAGE,&Realm::ChooseViewer,this);
    UB.Main(this,Time);
}
void Realm::AnalyzeObject(long Time)
{
    SE.Analyze(this,Time);
    if(W.Analyze(Time))
    {
        UB.Train(OBJ_PERSONAGE,&Realm::GiveWeaterEvent,this);
    }
    UB.Accessorial(this,Time);
}
#endif
