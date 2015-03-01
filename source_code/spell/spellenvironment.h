#ifndef DIY_SPELLENVIRONMENT_H
#define DIY_SPELLENVIRONMENT_H
#include "../p.o/handle.h"
#include "spell.h"
class Spell;
class Personage;
class SpellEnvironment
{
    bool SpellPrepare;
    bool SomeoneFinish;
public:
    bool SpellUsing;
    Handle<Spell> US;
    Handle<Personage> UP;
    std::list<Handle<Spell> > SpellPrepareList;
    bool SetSpell(Handle<Spell>);//it return false if this time a spell is runing and do nothing
    bool IsUsing(){return SpellUsing;}
    bool IsPrepare(){return SpellPrepare;}
    void Analyze(Realm*,long T);
    void ShowData();
    SpellEnvironment():SpellPrepare(false),SpellUsing(false),SomeoneFinish(false){}
};
void SpellEnvironment::ShowData()
{
    XYF Tem(-1.0,0.8);
    if(!SpellPrepareList.empty())
    {
        for(std::list<Handle<Spell> >::iterator Po=SpellPrepareList.begin();Po!=SpellPrepareList.end();++Po)
        {
            if(*Po)
            {
                glColor3f(1.0,0.0,0.0);
                glBegin(GL_QUADS);
                glVertex(Tem.X,Tem.Y);
                glVertex(Tem.X,Tem.Y-0.02);
                glVertex(Tem.X+(*Po)->PreparePresent()*0.5,Tem.Y-0.02);
                glVertex(Tem.X+(*Po)->PreparePresent()*0.5,Tem.Y);
                glEnd();
                Tem.Y+=0.03;
            }
        }
    }
}

bool SpellEnvironment::SetSpell(Handle<Spell> K)
{
    if(K)
    {
        if(IsUsing())
        {
            return false;
        }else{
            SpellPrepareList.push_back(K);
            K->PrepareStart();
            return true;
        }
    }
    return false;
}

void SpellEnvironment::Analyze(Realm * RB, long T)
{
    if(IsUsing())
    {
        if(US)
        {
            if(US->IsFinish())
            {
                SpellUsing=false;
                US.Unused();
            }
        }else{
            SpellUsing=false;
        }
    }
    for(std::list<Handle<Spell> >::iterator Po=SpellPrepareList.begin();Po!=SpellPrepareList.end();++Po)
    {
        if(*Po)
        {
            if((*Po)->Prepare(RB,T))
            {
                US=*Po;
                SpellUsing=true;
                for(std::list<Handle<Spell> >::iterator Po2=SpellPrepareList.begin();Po2!=SpellPrepareList.end();++Po2)
                {
                    if(*Po2)
                    {
                        if(Po2!=Po)
                        {
                            (*Po2)->PrepareInterrupt(RB);
                        }
                    }
                }
                SpellPrepareList.clear();
                break;
            }
        }
    }
}

#endif // SPELLENVIRONMENT_H
