#ifndef DIY_SPELLHUM_H
#define DIY_SPELLHUM_H
#include "spell.h"
#include "../p.o/calculate.h"
#include "../specialshoot/specialcontrol.h"
class SpellHum:public Spell
{
    SpecialControl SC;
    Calculate Using;
public:
    virtual void Finish(Personage *,Realm *);
    virtual void Interrupt(Personage *P, Realm *RB);
    virtual void Lanch(Personage *, Realm *);
    virtual void Analyze(Personage *, Realm *, long);
    virtual void Get(Handle<SpecialShoot>);
    SpellHum(long R,long U,long CD=100L):Spell(R,CD),Using(U){}
};

void SpellHum::Get(Handle<SpecialShoot> S)
{
    SC.GetSpecial(S);
}

void SpellHum::Lanch(Personage *P, Realm *R)
{
    if(!R->SE.SpellUsing)
    {
        R->SE.SpellUsing=true;
        R->SE.US=this;
        R->SE.UP=P;
        SS=Spell_Usi;
        Using=0;
        P->SP.UsingSpell=true;
        P->SP.Using=this;
    }
}

void SpellHum::Interrupt(Personage *P, Realm *RB)
{
    if(SS==Spell_Usi)
    {
        if(RB->SE.SpellUsing)
        {
            if(RB->SE.US==this&&RB->SE.UP==P)
            {
                RB->SE.SpellUsing=false;
                RB->SE.US.Unused();
                RB->SE.UP.Unused();
            }
        }
        if(P->SP.UsingSpell)
        {
            if(P->SP.Using==this)
            {
                P->SP.AllClamDown(PublicCalmDown);
            }
        }
        SS=Spell_Rec;
        Rechard=0;
    }
}

void SpellHum::Finish(Personage *P, Realm *RB)
{
    if(SS==Spell_Usi)
    {
        if(RB->SE.SpellUsing)
        {
            if(RB->SE.US==this&&RB->SE.UP==P)
            {
                RB->SE.SpellUsing=false;
                RB->SE.US.Unused();
                RB->SE.UP.Unused();
                P->SP.AllClamDown(PublicCalmDown);
                P->SP.Using.Unused();
                P->SP.UsingSpell=false;
            }
        }
        SS=Spell_Rec;
        Rechard=0;
    }
}

void SpellHum::Analyze(Personage *P, Realm *R, long T)
{
    Base(P,R,T);
    Using+T;
    if(Using)
    {
        Finish(P,R);
    }
}

#endif // SPELLHUM_H
