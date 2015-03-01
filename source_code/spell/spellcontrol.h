#ifndef DIY_SPELLSCONTROL_H
#define DIY_SPELLSCONTROL_H
#include "../p.o/information.h"
#include "../spell/spell.h"
#include "../realm/realm.h"
#include "spell.h"
class Personage;
class SpellControl
{
    int SpellSize;
    int MaxSpellSize;
    int UsingSpell;
    int MaxUsingSpell;
    Boss<Realm*,long> SpellList;
    std::list< Handle<Spell> > Using;
    int UseSpellLocation;
    bool HaveAddToSE;
public:
        bool IsUsing(){if(UsingSpell!=0)return true;return false;}
        void FlatShow(XYF);
        void Analyze(Realm*,Personage*,long);
        void Show(Personage*,Realm*,long);
        void Control(Handle<Information>);
        void AllClamDown(Handle<Spell>,long T);
        //void Interrupt(){InterruptSignal=true;}
        //void Interrupt(Personage* P,Realm *RB){}
        void GetSpell(Handle<Spell> S,Handle<Personage> K){SpellList.Employ(S);S->SetOwner(K);}
        void ShowFlat(Handle<Spell> S,XYF *Tem);
        bool FindSpell(Handle<Spell> S,int *Cal,int Tar);
        SpellControl(int Spe=4,int MaxU=1):HaveAddToSE(false),
            SpellSize(0),MaxSpellSize(Spe),UsingSpell(0),MaxUsingSpell(MaxU),UseSpellLocation(0){}
        ~SpellControl(){Using.clear();}
};
bool SpellControl::FindSpell(Handle<Spell> S, int *Cal, int Tar)
{
    if(S)
    {
        *Cal+=1;
        if(*Cal==Tar)
        {
            return true;
        }
    }
    return false;
}

void SpellControl::ShowFlat(Handle<Spell> S, XYF *Tem)
{
    if(S)
    {
        S->FlatShow(*Tem);
        Tem->X+=0.02;
    }
}

void SpellControl::AllClamDown(Handle<Spell> K,long Tem)
{
    if(K)
    {
        K->CalmDown(Tem);
    }
}

void SpellControl::FlatShow(XYF Tem)
{
    SpellList.Train(&SpellControl::ShowFlat,this,&Tem);
}

void SpellControl::Analyze(Realm *RB,Personage *P,long T)
{
    SpellList.Accessorial(RB,T);
    if(UseSpellLocation!=0)
    {
        if(UseSpellLocation<=MaxSpellSize)
        {
            int Cal=0;
            Handle<Spell> Target;
            SpellList.Find(Target,&SpellControl::FindSpell,this,&Cal,UseSpellLocation);
            if(Target)
            {
                if(Target->IsReady())
                {
                    if(UsingSpell+1<=MaxUsingSpell)
                    {
                        if(RB->SE.SetSpell(Target))
                        {
                            UsingSpell+=1;
                        }else{
                            Target->ActiveBomb(RB);
                            Using.push_back(Target);
                        }
                    }

                }
            }
        }
        UseSpellLocation=0;
    }
    if(!Using.empty())
    {
        for(std::list<Handle<Spell> >::iterator Po=Using.begin();Po!=Using.end();++Po)
        {
            if(*Po)
            {
                if((*Po)->IsFinish())
                {
                    Using.erase(Po--);
                }
            }else{
                Using.erase(Po--);
            }
        }
    }
        if(RB->SE.IsUsing())
        {
            UsingSpell=0;
            Using.clear();
        }
}
void SpellControl::Show(Personage *P,Realm *RB,long T)
{
    SpellList.Main(RB,T);
}
void SpellControl::Control(Handle<Information> I)
{
    if(UsingSpell<MaxUsingSpell)
    {
        if(I)
        {
            if(I->IsKeyUp())
            {
                if(I->Data1.uc>='0'&&I->Data1.uc<='9')
                {
                    UseSpellLocation=I->Data1.uc-'0';
                    if(I->Data1.uc=='0')
                        UseSpellLocation=9;
                }
            }
        }
    }
}
#endif
