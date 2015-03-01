#include <iostream>
using namespace std;
#include "SDL/SDL.h"
#include <string>
#include "../po.h"
#include "pogigl.h"
#include "popluginimage.h"
#include "popluginttf.h"
#include "../popicture.h"
#include "../pottf.h"
#include "../dialog.h"
//#include "../../scene/scenedata.h"
class XX:public Plugin
{
    POPicture KPK;
    POPicture Try;
    POTTF PT;
    Dialog DI;
    bool Key(){return true;}
    XYF L;
    long Time;
    int Mode;
    //SceneData S;
public:
    void Ana(Handle<Information>);
    void Layer2D(POMain * P)
    {
        KPK.Display(XYF(-0.5,0.5),XYF(1.0,0.0),XYF(0.0,-1.0),1.0,1.0,1.0);
        PT.DisplayMiddle(XYF(0.0,0.0),XYF(1.0,0.0),0.2,1.0,1.0,1.0);
        DI.Display(XYF(-1.0,0.0),XYF(1.0,-1.0),0.5,1.0,0.8);
    }
    void Init(PO *K)
    {
        KPK=CreatPicture("../../texture/welcome/shenshenew22.jpg",K);
        PT=CreatTTF("What the fuck",K);
        DI.Add("Fucking you~");
        DI.AddLine("What the fuck!!!!!!!!");
        DI.Init(K);
    }
    void Accessorial(POAccessorial * K)
    {
        Analyze(&XX::Ana,this);
        Time+=K->Time();
        L.Y=sin(Time/1000.0);
    }
    XX():Plugin("XXX"),L(0.0,0.0){}
};
void XX::Ana(Handle<Information> K)
{
    if(K)
    {
        if(K->IsKeyDown())
        {
            if(K->IsKey('d'))
                L.X+=0.5;
            else if(K->IsKey('a'))
                L.X-=0.5;
        }
    }
}
int main(int argc, char* argv[])
{
    PO::GetAgent(POGIGL::Agent());
    PO::Regedit(new XX());
    PO::GetPlugin(new POPluginImage());
    PO::GetPlugin(new POPluginTTF())->Set("../../font/fksnjt.ttc");
    PO::Init();
    PO::CreatFramework();
    PO::MainLoop();
}
