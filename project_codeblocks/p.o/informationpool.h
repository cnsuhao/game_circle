#ifndef INFORMATIONPOOL_H
#define INFORMATIONPOOL_H
#include <set>
#include "tank.h"
#include "information.h"
#include "informationviewer.h"
class InformationPool
{
    Tank<Handle<Information> > OutPool;
    std::set<InformationViewer*> Key;
    std::set<InformationViewer*> Mouse;
    std::set<InformationViewer*> Window;
    std::set<InformationViewer*> Special;
public:
    void GetInformation(Handle<Information>);
    void SentMessage();
    void Regedit(InformationViewer*);
    void UnRegedit(InformationViewer*);
};
void InformationPool::GetInformation(Handle<Information> K)
{
    OutPool.PushBack(K);
}
void InformationPool::SentMessage()
{
    //Error<<"Start Sent"<<endl;
    while(!OutPool.Empty())
    {
        //Error<<"Sent1"<<endl;
        Tank<Handle<Information> >::Ladle PoInf=OutPool.Begin();
        if(*PoInf)
        {
            if((*PoInf)->IsKeyUp()||(*PoInf)->IsKeyDown())
            {
                for(std::set<InformationViewer*>::iterator Po=Key.begin();Po!=Key.end();++Po)
                {
                    (*Po)->GetInformation(*PoInf);
                }
            }else if((*PoInf)->IsMouse())
            {
                for(std::set<InformationViewer*>::iterator Po=Mouse.begin();Po!=Mouse.end();++Po)
                {
                    (*Po)->GetInformation(*PoInf);
                }
            }else if((*PoInf)->IsWindow())
            {
                for(std::set<InformationViewer*>::iterator Po=Window.begin();Po!=Window.end();++Po)
                {
                    (*Po)->GetInformation(*PoInf);
                }
            }else{
                for(std::set<InformationViewer*>::iterator Po=Special.begin();Po!=Special.end();++Po)
                {
                    (*Po)->GetInformation(*PoInf);
                }
            }
        }
        //Error<<"Sent 2"<<endl;
        OutPool.PopFront();
    }
    //Error<<"Finish Sent"<<endl;
}

void InformationPool::Regedit(InformationViewer* K)
{
    if(K->Key()||K->All()) Key.insert(K);
    if(K->Mouse()||K->All()) Mouse.insert(K);
    if(K->Window()||K->All()) Window.insert(K);
    if(K->Special()||K->All()) Special.insert(K);
}

void InformationPool::UnRegedit(InformationViewer* K)
{
    if(K->Key()||K->All()) Key.erase(Key.find(K));
    if(K->Mouse()||K->All()) Mouse.erase(Mouse.find(K));
    if(K->Window()||K->All()) Window.erase(Window.find(K));
    if(K->Special()||K->All()) Special.erase(Special.find(K));
}

#endif // INFORMATIONPOOL_H
