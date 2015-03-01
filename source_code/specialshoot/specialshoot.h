#ifndef DIY_SPECIALSHOOT_H
#define DIY_SPECIALSHOOT_H
#include "../p.o/handle.h"
#include "../p.o/baseclass.h"
#include "../p.o/calculate.h"
class Realm;
class Personage;
enum SpecialSituation
{
    Special_Rec,
    Special_Rea,
    Special_Usi
};
class SpecialShoot:public HandleSeed
{
public:
    bool Avaliable;
    bool Actived;
    bool NeedInterrupt;
    Calculate Rechard;
    SpecialSituation SS;
    bool ShowAvailable;
    virtual void Init(Personage*,Realm*){}
    virtual void Analyze(Personage*,Realm*,long)=0;
    virtual void Show(Personage*,Realm*,long){ShowAvailable=false;}
    virtual void FlatShow(XYF);
    virtual void Interrupt(Personage* P,Realm *RB);
    virtual void Lanch(Personage *,Realm *)=0;
    void Interrupt();
    void Active();
    SpecialShoot(long RE):Avaliable(true),Actived(false),NeedInterrupt(false),ShowAvailable(true),Rechard(RE),SS(Special_Rec){}
    void Base(Personage* P,Realm *RB,long T);
};
void SpecialShoot::Active()
{
    Actived=true;
}
void SpecialShoot::FlatShow(XYF T)
{
    if(SS==Special_Usi||SS==Special_Rec)
    {
        glColor3f(0.5,0.5,0.5);
    }else if(SS==Special_Rea)
    {
        glColor3f(1.0,1.0,1.0);
    }
    glBegin(GL_QUADS);
    glVertex(T);
    glVertex(T+XYF(0.0,-0.05));
    glVertex(T+XYF(0.025,-0.05));
    glVertex(T+XYF(0.025,0.0));
    glEnd();
    if(SS==Special_Rec)
    {
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_QUADS);
        glVertex(T+XYF(0.0,Rechard.Present()*0.05-0.05));
        glVertex(T+XYF(0.0,-0.05));
        glVertex(T+XYF(0.025,-0.05));
        glVertex(T+XYF(0.025,Rechard.Present()*0.05-0.05));
        glEnd();
    }
}
void SpecialShoot::Interrupt()
{
    NeedInterrupt=true;
}

void SpecialShoot::Interrupt(Personage* P,Realm *RB)
{
    if(SS==Special_Usi)
    {
        Rechard=0;
        SS=Special_Rec;
    }
}
void SpecialShoot::Base(Personage* P,Realm *RB,long T)
{
    if(SS==Special_Rec)
    {
        Rechard+T;
        if(Rechard)
        {
            SS=Special_Rea;
            Using=0;
        }
    }else if(SS==Special_Rea)
    {
        if(Actived)
        {
            Lanch(P,RB);
        }
        if(NeedInterrupt)
        {
            Interrupt(P,RB);
            NeedInterrupt=true;
        }
    }
    Actived=false;
}
void SpecialShoot::Lanch(Personage* P,Realm* R)
{
    SS=Special_Usi;
}
#endif
