#ifndef TOUHOUSCENE_H
#define TOUHOUSCENE_H
#include "scene.h"
#include "../p.o/plugin_base.h"
#include "debugforviewer.h"
class TouhouScene:public Plugin_Base,public Scene
{
    std::list<std::string> MessageList;
public:
    void Init(ControlCenter* Data,long T);
    void SentMessage(std::string K){MessageList.push_back(K);}
    TouhouScene():Plugin_Base("TouHouScene"){}
    void Main(ControlCenter *Data, long L);
    void FlatShow(ControlCenter *Data);
    void Accessorial(ControlCenter *Data, long L);
};
void TouhouScene::FlatShow(ControlCenter *Data)
{
    Scene::Run();
}
void TouhouScene::Init(ControlCenter *Data, long T)
{
    Load("textscene2.txt");
    LoadResource("textresource2.txt");
    SceneData::CheckDetail(error);
    if(!ScriptionPacket::Ready())
    {
        ScriptionPacket::Display(error);
        Data->Exit();
    }
}

void TouhouScene::Main(ControlCenter *Data, long L)
{
    while(!MessageList.empty())
    {
        std::string K=*MessageList.begin();
        MessageList.pop_front();
        if(K=="FULIREALM")
        {
            Handle<Plugin_Base> Pc=new DebugViewer();
            Data->Regedit(Pc);
        }
    }
}
void TouhouScene::Accessorial(ControlCenter *Data, long L)
{
    while(Handle<Information> I=GetInformation())
    {
        Control(I);
    }

}

#endif // TOUHOUSCENE_H
