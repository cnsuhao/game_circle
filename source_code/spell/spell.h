#ifndef DIY_SPELL_H
#define DIY_SPELL_H
#include <vector>
#include "../p.o/handle.h"
#include "../p.o/baseclass.h"
#include "../p.o/calculate.h"
class Personage;
class Realm;
enum SpellSituation
{
    Spell_Rec=1,
    Spell_Usi,
    Spell_Rea,
    Spell_Pre
};

class Spell:public Staff<Realm*,long>
{
    long MaxShield;
    long NowShield;
    Handle<Personage> HPOwner;
    SpellSituation SS;
    bool HaveFinish;
    bool HaveStart;
    bool SpellOrBomb;//true is spell
    public:
        bool Avaliable;
        bool Actived;
        bool NeedInterrupt;
        Calculate RechardTime;
        Calculate PrepareTime;
        bool IsBomb(){return IsUsing()&&(!SpellOrBomb);}
        bool IsSpell(){return IsUsing()&&SpellOrBomb;}
        bool IsRechard(){if(SS==Spell_Rec)return true;return false;}
        bool IsReady(){if(SS==Spell_Rea)return true;return false;}
        bool IsUsing(){if(SS==Spell_Usi)return true;return false;}
        bool IsFinish(){return HaveFinish;HaveFinish=false;}
        bool IsPrepare(){if(SS==Spell_Pre)return true;return false;}
        void Rechard(){SS=Spell_Rec;}
        void Ready(){SS=Spell_Rea;}
        void Using(){SS=Spell_Usi;}
        virtual void ActiveBomb(Realm*){Using();SpellOrBomb=false;}
        virtual void ActiveSpell(Realm*){Using();SpellOrBomb=true;}
        void CalmDown(long Te){RechardTime=RechardTime.NeedTime-Te;Rechard();}
        void SetOwner(Handle<Personage> K){HPOwner=K;}
        Handle<Personage> Owner(){return HPOwner;}
        void Main(Realm*,long);
        virtual void Init(Realm*,long){}
        void Accessorial(Realm*,long);
        virtual void FlatShow(XYF);

        virtual void Effect(Realm* RB,long){EffectFinish(RB);}
        virtual void EffectShow(Realm*,long){}
        virtual void EffectFinish(Realm*){HaveFinish=true;CalmDown(RechardTime.NeedTime);}

        virtual void Bomb(Realm*RB,long T){BombFinish(RB);}
        virtual void BombShow(Realm*,long T){}
        virtual void BombFinish(Realm *){HaveFinish=true;CalmDown(RechardTime.NeedTime/2);}

        virtual void PrepareInterrupt(Realm* RB);
        virtual void PrepareStart(){PrepareTime=0;SS=Spell_Pre;}

        bool Prepare(Realm*,long T);
        float PreparePresent(){return PrepareTime.Present();}

        Spell(long RE,long Pre=5000,long Sh=10000):Avaliable(true),Actived(false),NeedInterrupt(false),RechardTime(RE),
            SS(Spell_Rea),MaxShield(Sh),NowShield(Sh),PrepareTime(Pre){}
};
void Spell::PrepareInterrupt(Realm* RB)
{
    CalmDown(10000);
}
bool Spell::Prepare(Realm *RB, long T)
{
    PrepareTime+T;
    if(PrepareTime)
    {
        ActiveSpell(RB);
        return true;
    }
    return false;
}

void Spell::FlatShow(XYF T)
{
    if(!IsUsing())
    {
        if(IsRechard())
        {
            glColor3f(0.1,0.0,0.1);
        }else if(IsReady())
        {
            glColor3f(1.0,1.0,0.2);
        }else if(IsPrepare())
        {
            glColor3f(1.0,0.0,1.0);
        }
        glBegin(GL_QUADS);
        glVertex(T);
        glVertex(T+XYF(0.0,-0.05));
        glVertex(T+XYF(0.025,-0.05));
        glVertex(T+XYF(0.025,0.0));
        glEnd();
        if(IsRechard())
        {
            glColor3f(1.0,0.0,0.0);
            glBegin(GL_QUADS);
            glVertex(T+XYF(0.0,RechardTime.Present()*0.05-0.05));
            glVertex(T+XYF(0.0,-0.05));
            glVertex(T+XYF(0.025,-0.05));
            glVertex(T+XYF(0.025,RechardTime.Present()*0.05-0.05));
            glEnd();
        }
    }else{
        //SC.FlatShow(T);
    }
}

void Spell::Accessorial(Realm *RB,long T)
{
    if(IsRechard())
    {
        RechardTime+T;
        if(RechardTime)
        {
            Ready();
        }
    }else if(IsBomb())
    {
        Bomb(RB,T);
    }else if(IsSpell())
    {
        Effect(RB,T);
    }
}
void Spell::Main(Realm *RB, long T)
{
    if(IsBomb())
    {
        BombShow(RB,T);
    }else if(IsSpell())
    {
        EffectShow(RB,T);
    }
}

#endif
