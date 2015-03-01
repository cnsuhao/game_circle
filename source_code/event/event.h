#ifndef EVENT_H
#define EVENT_H
#include "../p.o/staff.h"
#include "../p.o/calculate.h"
#include "../base/state.h"
//#include "object.h"
#define Eve_Mes_Nul 0
#define Eve_Mes_Ins 1
#define Eve_Mes_Out 2
#define Eve_Mes_Rep 3
class EventMessage:public HandleSeed
{
public:
    int IStyle;
    int IMode;
    int Style(){return IStyle;}
    int Mode(){return IMode;}
    EventMessage(int S=0,int M=Eve_Mes_Nul):IStyle(S),IMode(M){}
    //EventMessage(EventMessage& K){IStyle=K.Style();IMode=K.Mode();}
    void Set(int S,int M){IStyle=S;IMode=M;}
    virtual int Scription(){return 0;}
    bool IsStyle(int S){if(Style()==S)return true;return false;}
    bool IsInsert(){if(Mode()==Eve_Mes_Ins)return true;return false;}
    bool IsOut(){if(Mode()==Eve_Mes_Out)return true;return false;}
    bool IsReplace(){if(Mode()==Eve_Mes_Rep)return true;else return false;}
};
class EventRecive;
class Object;
class Personage;
class Event:public Staff<Object*,long>
{
    friend class EventRecive;
    Handle<Object> Resource;
    int EventStyle;
    Calculate ExistTime;
public:
    bool IsContinue(){if(ExistTime.NeedTime!=0) return true;return false;}
    int Style(){return EventStyle;}
    virtual void Effect(Object*){}
    virtual void Main(Object*,long){}
    virtual void Symple(){}
    virtual void Sentence(){}
    virtual Handle<EventMessage> CreatMessage(){Handle<EventMessage> Tem=new EventMessage();return Tem;}
    virtual Handle<EventMessage> InsertMessage(){Handle<EventMessage> EM=CreatMessage();if(EM){EM->Set(Style(),Eve_Mes_Ins);}return EM;}
    virtual Handle<EventMessage> OutMessage(){Handle<EventMessage> EM=CreatMessage();if(EM){EM->Set(Style(),Eve_Mes_Out);}return EM;}
    virtual Handle<EventMessage> RepMessage(){Handle<EventMessage> EM=CreatMessage();if(EM){EM->Set(Style(),Eve_Mes_Rep);}return EM;}
    virtual void Accessorial(Object*,long);
    virtual void EndEffect(Object*){}
    virtual void Combine(Handle<Event> P){if(P) P->HandleSeed::Destory();}
    void Destory(Object* P){EndEffect(P);HandleSeed::Destory();}
    Event(int K,long T=0):EventStyle(K),ExistTime(T){}
};
void Event::Accessorial(Object* S,long T)
{
    ExistTime+T;
    if(ExistTime)
    {
        EndEffect(S);
        Destory(S);
    }
}

#endif // EVENT_H
