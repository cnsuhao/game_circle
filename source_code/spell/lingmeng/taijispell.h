#ifndef DIY_TAIJISPELL_H
#define DIY_TAIJISPELL_H
#include "../spellhum.h"
#include "../../personage/bolilingmeng.h"
#include "../../bullet/lingmeng/taijibullet.h"
class TaiJiSpell:public SpellHum
{
    int Number;
    public:
        void Analyze(Personage*,Realm*,long);
        TaiJiSpell():SpellHum(10000,10000){}
};

void TaiJiSpell::Analyze(Personage  *P, Realm *RB, long T)
{
    Base(P,RB,T);
    if(SS==Spell_Usi)
    {
        if(P->Name==PRESONAGE_LINGMENG)
        {
            LingMeng* LM=dynamic_cast<LingMeng*>(P);
            if(LM!=NULL)
            {

            }
        }
    }
    Finish(P,RB);
}

#endif // TAIJISPELL_H
