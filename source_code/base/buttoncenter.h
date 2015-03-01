#ifndef BUTTONCENTER_H
#define BUTTONCENTER_H
#include "../p.o/information.h"
#include "../p.o/singleboss.h"
#include "button.h"

class ButtonCenter
{
public:
    int AllID;
    bool BC_Active;
    bool UsingMouse;
    SingleBoss<ButtonCenter*,long> Bo;
    void Main(long);
    void Control(Handle<Information>);
    void MouseChoose(Handle<Button>);
    void Active(){BC_Active=true;}
    void Disactive(){BC_Active=false;}
    void KeyChoose(Handle<Button>);
    void Add(Handle<Button>);
    XYF ML;
    int ChooseID;
    Handle<Button> Choosing;
    ButtonCenter():AllID(0),BC_Active(true),UsingMouse(true){}
};
void ButtonCenter::Add(Handle<Button> H)
{
    if(H)
    {
        AllID+=1;
        H->SetID(AllID);
        Bo.Employ(H,this,0);
    }
}

void ButtonCenter::MouseChoose(Handle<Button> B)
{
    if(B)
    {
        if(B->Choose(ML))
        {
            Choosing=B;
            ChooseID=B->ID;
        }
    }
}

void ButtonCenter::KeyChoose(Handle<Button> B)
{
    if(B)
    {
        if(B->Choose(ChooseID))
        {
            Choosing=B;
        }
    }
}

void ButtonCenter::Main(long T)
{
    if(BC_Active)
        Bo.Main(this,T);
}

void ButtonCenter::Control(Handle<Information> I)
{
    if(BC_Active)
    {
        if(I)
        {
            if(I->IsMouseMotion())
            {
                ML.Set(I->Data1.f,I->Data2.f);
                Choosing.Unused();
                ChooseID=0;
                Bo.Train(&ButtonCenter::MouseChoose,this);
            }else if(I->IsKeyUp())
            {
                if(AllID!=0)
                {
                    if(I->Data1.uc==17||I->Data1.uc==18)
                    {
                        if(I->Data1.uc==17)
                        {
                            ChooseID-=1;
                            if(ChooseID<1)
                                ChooseID=AllID;
                        }else{
                            ChooseID+=1;
                            if(ChooseID>AllID)
                                ChooseID=1;
                        }

                        Bo.Train(&ButtonCenter::KeyChoose,this);
                    }
                }
                if(I->Data1.uc==13)
                {
                    if(Choosing)
                        Choosing->Respond();
                }
            }else if(I->IsMouseButtonUp())
            {
                if(I->IsMouseButtonLeft())
                {
                    if(Choosing)
                        Choosing->Respond();
                }
            }
            if(UsingMouse)
            {
            }else{

            }
        }
    }
}

#endif // BUTTONCENTER_H
