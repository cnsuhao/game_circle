#ifndef WEATHEREVENT_H
#define WEATHEREVENT_H
#include "event.h"
#include "../base/object.h"
#define Eve_Wea 99
#define Eve_Wea_Win 90
#define Eve_Wea_Sum 91
#define Eve_Wea_Aut 92
#define Eve_Wea_Spr 93
#define Eve_Tim_Mor 94
#define Eve_Tim_Aft 95
#define Eve_Tim_Nig 96
class WinterMessage:public EventMessage
{
public:
    int Scription(){return Eve_Wea_Win;}
    WinterMessage(){}
};
class WinterEvent:public Event
{
    float CutDownSpeed;
public:
    WinterEvent():Event(Eve_Wea,100000000){}
    void Effect(Object *O)
    {
        CutDownSpeed=O->GetState()->Speed*0.2;
        O->GetState()->RealSpeed-=CutDownSpeed;
    }
    void EndEffect(Object *O)
    {
        O->GetState()->RealSpeed+=CutDownSpeed;
    }
    Handle<EventMessage> CreatMessage(){Handle<WinterMessage> Tem=new WinterMessage();return Tem;}
};
class SpringMessage:public EventMessage
{
public:
    int Scription(){return Eve_Wea_Spr;}
};
class SpringEvent:public Event
{
public:
    SpringEvent():Event(Eve_Wea,100000000){}
    Handle<EventMessage> CreatMessage(){Handle<SpringMessage> Tem=new SpringMessage();return Tem;}
};
class AutumnMessage:public EventMessage
{
public:
    int Scription(){return Eve_Wea_Aut;}
};
class AutumnEvent:public Event
{
public:
    AutumnEvent():Event(Eve_Wea,100000000){}
    Handle<EventMessage> CreatMessage(){Handle<AutumnMessage> Tem=new AutumnMessage();return Tem;}
};
class SummerMessage:public EventMessage
{
public:
    int Scription(){return Eve_Wea_Sum;}
};
class SummerEvent:public Event
{
public:
    SummerEvent():Event(Eve_Wea,100000000){}
    Handle<EventMessage> CreatMessage(){Handle<SummerMessage> Tem=new SummerMessage();return Tem;}
};
#endif // WEATHEREVENT_H
