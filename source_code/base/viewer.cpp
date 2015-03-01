#ifndef DIY_VIEWER_CPP
#define DIY_VIEWER_CPP
#include <string>
#include "../p.o/plugin_base.h"
#include "../p.o/picture.h"
#include "../p.o/sgprint.h"
#include "../realm/bolirealm.cpp"
#include "../personage/bolilingmeng.h"
#include "../p.o/initer.h"
#include "../ai/ailingmeng.h"
class Viewer:public Plugin_Base
{
    Sentence Se;
    Sentence C;
    std::string Tc;
    Handle<Personage> Player;
    Initer IT;
    public:
        void Accessorial(ControlCenter*,long);
        void FlatShow(ControlCenter*);
        void Main(ControlCenter*,long);
        void Init(ControlCenter*,long);
        Viewer(Handle<Personage> K):Player(K),Plugin_Base("Viewer")
        {
        }
};
void Viewer::Main(ControlCenter* CC,long)
{
    if(Player)
        Player->SetView();
}
void Viewer::FlatShow(ControlCenter* CC)
{
    if(Player)
    {
        Player->FlatShow(CC);
        int S,M;
        C.ShowXMiddle(0.0,0.0);
    }
}
void Viewer::Accessorial(ControlCenter* CC,long T)
{
    while(Handle<Information> Tem=GetInformation())
    {
        if(Tem->IsKeyUp())
        {
            if(Tem->Data1.uc==27)
                Exit();
        }
        if(Player)
            Player->BaseControl(Tem,T);

    }
}
void Viewer::Init(ControlCenter* CC,long T)
{
    C.Add("jdsfkasdf\ndafgasdfe");
    LockMouse();
    Plugin_Base::Init(CC,T);
}
#endif
