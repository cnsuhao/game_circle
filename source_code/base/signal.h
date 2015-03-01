#ifndef DIY_SIGNAL_H
#define DIY_SIGNAL_H
#include "../p.o/handle.h"

#define Sig_Sty_IC  1  //ICE COLD
#define Sig_Sty_CW  98 //Change Weather
//Less then 100


#define Sig_Res_Re 2
#define Sig_Res_Pe 22
#define Sig_Res_Bu 23
#define Sig_Res_Sp 24

class Realm;
class Personage;
class Bullet;
class Spell;
class Signal:public HandleSeed
{
public:
    int Style;
    int Resource;
    bool Continue;
    Handle<Realm> R;
    Handle<Personage> P;
    Handle<Bullet> B;
    Handle<Spell> S;
    long ContinueTime;
    int Data1;
    int Data2;
    int Data3;
    int Data4;
    void SetData(int,int,int,int);
    void Set(int,Handle<Realm>);
    void Set(int,Handle<Personage>);
    void Set(int,Handle<Bullet>);
    void Set(int,Handle<Spell>);
    void SetContinue(long T);
    Signal(int S,Handle<Realm> C):Data1(0),Data2(0),Data3(0),Data4(0){Set(S,C);}
    Signal(int S,Handle<Personage> C):Data1(0),Data2(0),Data3(0),Data4(0){Set(S,C);}
    Signal(int S,Handle<Bullet> C):Data1(0),Data2(0),Data3(0),Data4(0){Set(S,C);}
    Signal(int S,Handle<Spell> C):Data1(0),Data2(0),Data3(0),Data4(0){Set(S,C);}
};

void Signal::SetContinue(long T)
{
    Continue=true;
    ContinueTime=T;   
}

void Signal::SetData(int A=0,int B=0,int C=0,int D=0)
{
    Data1=A;
    Data2=B;
    Data3=C;
    Data4=D;
}

void Signal::Set(int S,Handle<Realm> Tar)
{
    Style=S;
    R=Tar;
    Resource=Sig_Res_Re;
}

void Signal::Set(int S,Handle<Personage> Tar)
{
    Style=S;
    P=Tar;
    Resource=Sig_Res_Pe;
}

void Signal::Set(int S,Handle<Bullet> Tar)
{
    Style=S;
    B=Tar;
    Resource=Sig_Res_Bu;
}

void Signal::Set(int Sx,Handle<Spell> Tar)
{
    Style=Sx;
    S=Tar;
    Resource=Sig_Res_Sp;
}

#endif
