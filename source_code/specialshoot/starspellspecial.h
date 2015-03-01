#ifndef DIY_STARSPELL_SPECIAL_H
#define DIY_STARSPELL_SPECIAL_H
#include "../bullet/starspell_bullet.h"
class StarSpellLeaderSpecial:public SpecialShoot
{
    public:
        void Analyze(Personage*,Realm*,long,bool&);
        StarSpellLeaderSpecial():SpecialShoot(5000){}
};
void StarSpellLeaderSpecial::Analyze(Personage *P,Realm *RB,long T,bool& B)
{
    SpecialShoot::Base(P,RB,T);
    if(SS==Special_Usi)
    {
        Coordinate Tc;
        Tc.Location=P->Location+2.0*P->Front;
        Tc.Front=P->Front;
        Tc.Up=P->Up;
        Tc.Left=P->Left;
        Handle<Object> Tk=new StarSpellLeader(P,Tc);
        RB->GetObject(Tk);
        Finish(P,RB,B);
    }
}
#endif
