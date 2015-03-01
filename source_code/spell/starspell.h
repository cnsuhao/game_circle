#ifndef DIY_STARSPELL_H
#define DIY_STARSPELL_H
#include "spell.h"
#include "../bullet/starspell_bullet.h"
#include "../specialshoot/starspellspecial.h"
class StarSpell:public Spell
{
    int Aspect;
    public:
        void Analyze(Personage*,Realm*,long,bool&,Handle<Spell>&);
        void Lanch(Personage*,Realm*,bool&,Handle<Spell>&);
        StarSpell():Spell(1000,20000),Aspect(0)
        {
            SC.GetSpecial(new StarSpellLeaderSpecial);
        }
};
void StarSpell::Lanch(Personage* P,Realm* RB,bool& B,Handle<Spell>& H)
{
    Spell::Lanch(P,RB,B,H);
    Aspect=0;
    Coordinate Tc;
    Tc.Set(P);
    Tc.Location=P->Location+3.0*P->Front;
    //Handle<Object> Tl=new Tool(TOOL_JIECAO,Handle<Object> (P),Tc,200);
    //RB->GetObject(Tl);
}
void StarSpell::Analyze(Personage *P,Realm *RB,long T,bool& B,Handle<Spell>& H)
{
    Spell::Analyze(P,RB,T,B,H);
    if(SM==S_USING)
    {
        switch(Aspect)
        {
            case 0:
                Coordinate Tv;
                Tv.Set(P);
                Tv.Location=P->Location+2.0*P->Left;
                Tv.Front=P->Left;
                Tv.Left=(Tv.Up&Tv.Left).Uint(); 
                Handle<Object> Yu=new StarSpellBullet(P,Tv);
                RB->GetObject(Yu);
                Tv.Location=P->Location-2.0*P->Left;
                Tv.Front=-1.0*P->Left;
                Tv.Left=(Tv.Up&Tv.Left).Uint();
                Yu=new StarSpellBullet(P,Tv);
                RB->GetObject(Yu);
                Aspect+=1;
                break;
            //case 1:
                //break;
        }
    }
}
#endif
