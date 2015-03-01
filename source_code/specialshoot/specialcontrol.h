#ifndef DIY_SPECIALSCONTROL_H
#define DIY_SPECIALSCONTROL_H
#include "../p.o/handle.h"
#include "../p.o/information.h"
#include "../specialshoot/specialshoot.h"
class Personage;
class SpecialControl
{
    friend class Persongae;
    bool InterruptSignal;
    public:
        std::vector<Handle<SpecialShoot> >  SpecialList;
        bool UsingSpecial;
        void FlatShow(XYF);
        void Analyze(Realm*,Personage*,long);
        void Show(Personage*,Realm*,long);
        void Control(Handle<Information>);
        void Interrupt(){InterruptSignal=true;}
        void Interrupt(Personage* P,Realm *RB){}
        void GetSpecial(Handle<SpecialShoot> S){SpecialList.push_back(S);}
        SpecialControl():UsingSpecial(false),InterruptSignal(false){}
};
void SpecialControl::FlatShow(XYF Tem)
{
    if(!SpecialList.empty())
    {
        std::vector<Handle<SpecialShoot> >::iterator Po;
        for(Po=SpecialList.begin();Po!=SpecialList.end();++Po)
        {   
            Tem.X+=0.05;
            if(*Po)
            {
                (*Po)->FlatShow(Tem);
            }
        }
    }
}
void SpecialControl::Analyze(Realm *RB,Personage *P,long T)
{
    std::vector<Handle<SpecialShoot> >::iterator Po;
    for(Po=SpecialList.begin();Po!=SpecialList.end();++Po)
    {   
        if(*Po)
        {
            (*Po)->Analyze(P,RB,T);
        }
    }
    if(InterruptSignal)
    {
        for(Po=SpecialList.begin();Po!=SpecialList.end();++Po)
        {   
            if(*Po)
            {
                (*Po)->Interrupt(P,RB);
            }
        }
        InterruptSignal=false;
    }
}
void SpecialControl::Show(Personage *P,Realm *RB,long T)
{
    std::vector<Handle<SpecialShoot> >::iterator Po;
    for(Po=SpecialList.begin();Po!=SpecialList.end();++Po)
    {   
        if(*Po)
        {
            if((*Po)->ShowAvailable)
                (*Po)->Show(P,RB,T);
        }
    }
}
void SpecialControl::Control(Handle<Information> I)
{
    if(!SpecialList.empty())
    {
        if(I)
        {
            if(I->Category1==INFEVENT&&I->Category2==INFKEY&&I->Category3==INFKEYDOWN)
            {
                if(I->Data1.uc>='0'&&I->Data1.uc<='9')
                {
                    int N=I->Data1.uc-'1';
                    if(I->Data1.uc=='0')
                        N=9;
                    std::vector<Handle<SpecialShoot> >::iterator Po=SpecialList.begin()+N;
                    if(Po<SpecialList.end()&&Po>=SpecialList.begin())
                    {
                        if(*Po)
                        {
                            (*Po)->Active();
                        }
                    }
                }
            }
        }
    }
}
#endif
