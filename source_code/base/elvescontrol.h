#ifndef ELVESCONTROL_H
#define ELVESCONTROL_H
#include <list>
#include <string>
#include "../p.o/handle.h"
#include "../p.o/elvestexture.h"
#include "../p.o/calculate.h"
#include "../elves/elvesspace.h"
#include "../elves/elves.h"


class ElvesControl
{
public:
    Handle<ElvesSpace> HES;
    bool FinishInit;
    bool AnalyzeInit;
    Handle<Elves> Select(float , float , float);
    void Show(long);
    void Analyze(long);
    void Set(Handle<ElvesSpace>);
    void Add(Handle<Elves>);
    ElvesControl():FinishInit(true){}
};

void ElvesControl::Add(Handle<Elves> EB)
{
    if(HES)
    {
        HES->Add(EB);
    }
}

void ElvesControl::Set(Handle<ElvesSpace> HS)
{
    if(HS)
    {
        HES=HS;
        FinishInit=false;
    }
}


void ElvesControl::Show(long T)
{
    if(HES)
    {
        if(!FinishInit)
        {
            HES->Init();
            FinishInit=true;
        }
        HES->ElvesShow(T);
    }
}
void ElvesControl::Analyze(long T)
{
    if(HES)
        if(FinishInit)
        {
            HES->ElvesAnalyze(T);
        }
}

Handle<Elves> ElvesControl::Select(float x, float y,float Range)
{
    Handle<Elves> Tem;
    bool Finish=false;
    if(HES)
    {
        /*for(std::list<Handle<ElvesBase> >::iterator Po=HES->ELA.begin();Po!=HES->ELA.end();++Po)
        {
            Handle<Elves> Tem2=*Po;
            if(Tem2)
            {
                if(Finish)
                {
                    (Tem2)->Choose=false;
                }else{
                    if((Tem2->X-x)*(Tem2->X-x)+(Tem2->Y-y)*(Tem2->Y-y)<Range*Range)
                    {
                        Tem=*Po;
                        Finish=true;
                    }
                }
            }
        }*/
    }
    return Tem;
}




#endif // ELVESCONTROL_H
