#ifndef DIY_EFFECT_H
#define DIY_EFFECT_H
#include <set>
#include <map>
#include <string>
#include "signal.h"
#include "../p.o/error.h"
#include "../p.o/handle.h"
#define Eff_Mod_Ext 1
#define Eff_Mod_Onl 2
#define Eff_Mod_Def 4
class Effect;
namespace ExEffect
{
    int StarExEffectID=100;
    std::map<int, void (*) (Signal *,Effect *,bool) > ExMap;
    std::map<std::string,int> CallMap;
}
class Effect:virtual public HandleSeed
{
    Calculate RefleshTime;
    int Mode;
public:
    std::set<int> Extrel;
    std::set<int> Only;
    std::list<Handle<Signal> > SignalList;
    std::list<Handle<Signal> > ContinueSignal;
    static void Add(std::string,void (*)(Signal *,Effect *,bool));
    void Analyze(long T);
    void Get(Handle<Signal>);
    virtual void IceCold(Signal*,bool){}//The Second bool means weather this signal is start of the continue is end
    virtual void ChangeWeather(Signal*,bool){}
    Effect(int T=Eff_Mod_Ext):RefleshTime(100),Mode(T){}
};
void Effect::Get(Handle<Signal> S)
{
    if(S)
    {
        bool OK=true;
        if(Mode&Eff_Mod_Ext==Eff_Mod_Ext)
        {
            if(Extrel.count(S->Style)==1)
                OK=false;
        }else if(Mode&Eff_Mod_Onl==Eff_Mod_Onl)
        {
            if(Extrel.count(S->Style)==0)
                OK=false;
        }
        if(Mode&Eff_Mod_Def==Eff_Mod_Def)
        {
            if(S->Style>=100)
                OK=false;
        }
        if(OK)
        {
            if(S->Continue)
            {
                if(!ContinueSignal.empty())
                {
                    for(std::list<Handle<Signal> >::iterator Po2=ContinueSignal.begin();Po2!=ContinueSignal.end();++Po2)
                    {
                        if(*Po2)
                            if(S->Style==(*Po2)->Style)
                            {
                                ContinueSignal.erase(Po2--);
                                break;
                            }
                    }
                }        
                ContinueSignal.push_back(S);
            }
            switch(S->Style)
            {
            case Sig_Sty_CW:
                ChangeWeather(S,true);
                break;
            case Sig_Sty_IC:
                IceCold(S,true);
                break;
            default:
                if(ExEffect::ExMap.count(S->Style)==1)
                {
                    (*ExEffect::ExMap[S->Style])(S,this,true);
                }
                break;
            }
        }
    }
}
void Effect::Analyze(long T)
{
    RefleshTime+T;
    if(RefleshTime)
    {
        for(std::list<Handle<Signal> >::iterator Po=ContinueSignal.begin();Po!=ContinueSignal.end();++Po)
        {
            if(*Po)
            {
                (*Po)->ContinueTime-=RefleshTime.Time;
                if((*Po)->ContinueTime<=0)
                {
                    switch((*Po)->Style)
                    {
                    case Sig_Sty_IC:
                        IceCold(*Po,false);
                        break;
                    default:
                        if(ExEffect::ExMap.count((*Po)->Style)==1)
                            (*ExEffect::ExMap[(*Po)->Style])((*Po),this,false);
                        break;
                    }
                }
            }else{
                ContinueSignal.erase(Po--);
            }
        }
        RefleshTime=0;
    }
}
void Effect::Add(std::string N,void (*Tem)(Signal *,Effect *,bool))
{
    if(ExEffect::CallMap.count(N)==0)
    {
        ExEffect::CallMap[N]=ExEffect::StarExEffectID;
        ExEffect::ExMap[ExEffect::StarExEffectID]=Tem;
        ExEffect::StarExEffectID+=1;
    }else{
        std::string Err;
        Err="The Effect ID: "+N+" is Already Exist!!!Please Change Another Name";
        throw RunInitError(Err);
    }
}
#endif
