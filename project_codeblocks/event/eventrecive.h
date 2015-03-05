#ifndef EVENTRECIVE_H
#define EVENTRECIVE_H
#include "../p.o/boss.h"
#include "event.h"

class Personage;
class EventRecive
{
public:
    Boss<Object*,long> Bo;
    int ListNumber;
    std::list<Handle<EventMessage> > EveList;
    bool FindTheSameEvent(Handle<Event>,Handle<Event>);
    void GetEvent(Handle<Event>,Object*);
    void SympleDetail(Handle<Event>,Object*,long);
    void ShowSymple(Object* S,long T){Bo.Train(&EventRecive::SympleDetail,this,S,T);}
    void Main(Object* S,long L){Bo.Train(&EventRecive::CheckOut,this,L);Bo.Main(S,L);}
    void Accessorial(Object* S,long T){Bo.Accessorial(S,T);}
    void CheckOut(Handle<Event>,long);
    void AddList(Handle<EventMessage>);
    Handle<EventMessage> LastMessage(){Handle<EventMessage> Tem;if(!EveList.empty()){Tem=*EveList.begin();EveList.pop_front();ListNumber-=1;}return Tem;}
    EventRecive():ListNumber(0){}
};
void EventRecive::AddList(Handle<EventMessage> K)
{
    if(K)
    {
        EveList.push_back(K);
        if(ListNumber>=20)
        {
            EveList.pop_front();
        }else{
            ListNumber+=1;
        }
    }
}
void EventRecive::CheckOut(Handle<Event> K, long T)
{
    if(K)
    {
        if(K->ExistTime.Time+T>K->ExistTime.NeedTime)
        {
            AddList(K->OutMessage());
        }
    }
}

void EventRecive::SympleDetail(Handle<Event> P, Object * S, long T)
{
    if(P)
    {
        P->Symple();
    }
}

void EventRecive::GetEvent(Handle<Event> P,Object* S)
{
    if(P)
    {
        if(P->IsContinue())
        {
            Handle<Event> Tem;
            Bo.Find(Tem,&EventRecive::FindTheSameEvent,this,P);
            Bo.Employ(P);
        }
        AddList(P->InsertMessage());
        P->Effect(S);
    }
}

bool EventRecive::FindTheSameEvent(Handle<Event> I, Handle<Event> P)
{
    if(I)
    {
        if(P)
        if(I->Style()==P->Style())
        {
            AddList(I->RepMessage());
            I->Combine(P);
            return true;
        }
    }
    return false;
}

#endif // EVENTRECIVE_H
