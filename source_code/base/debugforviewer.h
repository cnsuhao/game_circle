#ifndef DEBUGFORVIEWER_H
#define DEBUGFORVIEWER_H
#include "../p.o/plugin_base.h"
#include "viewer.cpp"
class DebugViewer:public Plugin_Base
{
public:
    //void Init(ControlCenter*,long);
    DebugViewer():Plugin_Base("NULL"){}
    void Main(ControlCenter*,long);
};
void DebugViewer::Main(ControlCenter * CC, long T)
{
    Handle<Personage> Player=new LingMeng();
    Handle<Personage> Enermy=new LingMeng();
    Handle<BoliRealm> Ty=new BoliRealm(Player);

    //Enermy->SetAI(new AILingMeng(Player,Enermy));
    Ty->SetViewer(Player);
    Player->SP.GetSpell(new Spell(5000),Player);
    Player->Location=XYZF(0.0,0.0,-8.0);
    Player->Location.Set(0.0,-0.4,0.0);
    Ty->GetObject(Player);
    Enermy->Location.Set(0.0,-0.4,-10.0);
    Ty->GetObject(Enermy);
    Destory();
    CC->Regedit(new Viewer(Player));
    CC->Regedit(Ty);
}

#endif // DEBUGFORVIEWER_H
