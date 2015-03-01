#ifndef DIY_AVIATE_H
#define DIY_AVIATE_H
#include "object.h"
#include "../realm/realm.h"
#include "view.h"
#include "../p.o/calculate.h"
#include <math.h>
//飞行模式转换到走路模式尚为完成。默认走路模式

#define Avi_Wal 1
#define Avi_Fly 2
#define JumpMaxSpeed 10.0


class Aviate
{
    int FAD,UAD,LAR;
    int VUAD,VLAR,VRAN;

    Calculate JumpSpeedC;
    bool Jump;
    bool Falling;
    int FlyStep;
public:
        int AM;
    bool ChangeTo(Coordinate& C,Coordinate& C2,float Angle,float Time);
    //bool Jump;
    float Speed;
    float DA,UADA,LARA;
    float WM;
    float VUADS,VLARS,VRANS;
    float JumpSpeed;
    bool MoveActived;
    bool ViewActived;
    bool ChangeView;
    bool Jumpping;
    void ChangeToWalk(){ChangeView=true;}
    void StartJump(){Jump=true;}
    void EndJump(){Jump=false;}
    //void Up(){}
    //void Down(){}
    //void StopUAD(){}
    void Front(){FAD=1;}
    void Back(){FAD=-1;}
    void StopFAD(){FAD=0;}
    void Left(){LAR=1;}
    void Right(){LAR=-1;}
    void StopLAR(){LAR=0;}
    void ResetMove(void){FAD=0;UAD=0;LAR=0;}
    void ResetView(void){VUAD=0;VLAR=0;VRAN=0;}
    void Run(Object* O,View* V,Realm *RB,long T);
    Aviate(float);
};
Aviate::Aviate(float P=1.0):Speed(P),AM(Avi_Wal),DA(0.4),UADA(0.7),LARA(0.7),VUADS(2.0),VLARS(2.0),VRANS(2.0),MoveActived(true),
                        ViewActived(true),ChangeView(false),WM(0.5),Jumpping(false),Falling(false),JumpSpeedC(200),Jump(false),FlyStep(0)
{}

/*bool Aviate::ChangeTo(Coordinate &C, Coordinate &C2, float Angle, float Time,bool TheSame=false)
{
    bool ReadyX=false,ReadyY=false;
    if(C.Front*C2.Front>=0.95)
    {
        C.Front=C2.Front;
        ReadyX=true;
    }else{
        XYZF K1=C.Front&C2.Front;
        XYZF K3=(K1&C2.Front).Uint();
        float X=C.Front*K3;
        float Y=C.Front*C2.Front;
        float AT=Time*Angle;
        C.Front=((cos(AT)*X-sin(AT)*Y)*K3+(sin(AT)*X+cos(AT)*Y)*C2.Front).Uint();
    }
    C.Left=(C.Up&C.Front).Uint();
    C.Up=(C.Front&C.Left).Uint();
    if(TheSame)
    {
        if(C.Left*C2.Left>=0.95)
        {
            C.Left=C2.Left;
            ReadyY=true;
        }else{
            XYZF K1=C.Left&C2.Left;
            XYZF K3=(K1&C2.Left).Uint();
            float X=C.Left*K3;
            float Y=C.Left*C2.Left;
            float AT=Time*Angle;
            C.Front=((cos(AT)*X-sin(AT)*Y)*K3+(sin(AT)*X+cos(AT)*Y)*C2.Left).Uint();
        }
        C.Up=(C.Front&C.Left).Uint();
        C.Front=(C.Left&C.Up).Uint();
    }
    if(ReadyX&&((TheSame&&ReadyY)||!TheSame)) return true;
    else return false;
}*/

void Aviate::Run(Object* O,View* V,Realm *RB,long T)
{
    float Time=T/1000.0;
    XYZF Di(0.0,0.0,0.0);
    //XYZF &U=RB->HorizontalU;
    if(Jump)
    {
        if(!Falling&&AM==Avi_Wal)
        {
            JumpSpeedC+T;
            if(JumpSpeedC)
            {
                Falling=true;
                JumpSpeed=JumpMaxSpeed;
                JumpSpeedC=0;
            }
        }else if(AM==Avi_Fly)
        {
            Di+=0.5*Time*RB->Horizontal().Up;
        }
        if(FlyStep==2)
        {
            AM=Avi_Fly;
        }
        if(AM==Avi_Wal)
        {
            if(RB->CanFly(O->Location))
            {
                FlyStep=1;
            }
        }
    }else{
        if(FlyStep==1)
        {
            FlyStep=2;
        }
        if(JumpSpeedC.Time!=0)
        {
            if(!Falling)
            {
                Falling=true;
                JumpSpeed=JumpMaxSpeed*~JumpSpeedC;
                JumpSpeedC=0;
            }
        }
    }
    if(AM==Avi_Fly)
    {
        if(FAD==1)
        {
            Di+=Speed*Time*V->Front();
        }else if(FAD==-1)
        {
            Di-=DA*Speed*Time*V->Front();
        }
        /*
        if(UAD==1)
        {
            Di+=UADA*Speed*Time*V->Up();
        }else if(UAD==-1)
        {
            Di-=UADA*Speed*Time*V->Up();
        }*/
        if(LAR==1)
        {
            Di+=LARA*Speed*Time*V->Left();
        }else if(LAR==-1)
        {
            Di-=LARA*Speed*Time*V->Left();
        }
        if(RB->CanWalk(O->Location))
        {
            AM=Avi_Wal;
            Falling=true;
            JumpSpeed=0.0;

        }
    }else if(AM==Avi_Wal)
    {
        if(FAD==1) {Di+=WM*Speed*Time*O->Front;}else if(FAD==-1){Di-=WM*DA*Speed*Time*O->Front;}
        if(LAR==1){Di+=WM*LARA*Speed*Time*O->Left;}else if(LAR==-1){Di-=WM*LARA*Speed*Time*O->Left;}
        if(Falling)
            Di+=JumpSpeed*Time*RB->Up();
        if(RB->CrashLand(*O,Di,Di))
        {
            JumpSpeed=0.0;
            Falling=false;
        }else{
            JumpSpeed-=10.0*Time;
            if(JumpSpeed<=0)
                FlyStep=0;
            Falling=true;
        }
    }
    if(!RB->OutRealm(O->Location+Di))
    {
        O->Location+=Di;
    }
    O->Up=(RB->Up()).Uint();
    O->Left=(V->Left()).Uint();
    O->Front=(O->Left&RB->Up()).Uint();
}
    /*if(AM==AVI_FLY&&(!RB->FlyAvilable))
    {
        ControlAvalible=false;
        ChangeView=true;
    }
    if(ChangeView)
    {
        ControlAvalible=false;
        if(ChangeTo(*O,RB->Horizontal(),0.02,Time))
        {
            ChangeView=false;
        }
    }
    if(ControlAvalible)
    {
        XYZF &U=-RB->Horizontal().Up;
        if(FAD==1)
        {
            if(AM==AVI_FLY)
                O->Location+=Speed*Time*O->Front;
            else if(AM==AVI_WALK)
                O->Location+=WM*Speed*Time*(U&(O->Front&U)).Uint();
        }else if(FAD==-1)
        {
            if(AM==AVI_FLY)
                O->Location-=DA*Speed*Time*O->Front;
            else if(AM==AVI_WALK)
                O->Location-=WM*DA*Speed*Time*(U&(O->Front&U)).Uint();
        }
        if(UAD==1)
        {
            if(AM==AVI_FLY)
                O->Location+=UADA*Speed*Time*O->Up;
            //else if(AM==AVI_WALK)
                //Location+=WM*UADA*Speed*HorizontalU;
        }else if(UAD==-1)
        {
            if(AM==AVI_FLY)
                O->Location-=UADA*Speed*Time*O->Up;
        }
        if(LAR==1)
        {
            if(AM==AVI_FLY)
                O->Location+=LARA*Speed*Time*O->Left;
            else if(AM==AVI_WALK)
                O->Location+=WM*LARA*Speed*Time*(U&O->Front).Uint();
        }else if(LAR==-1)
        {
            if(AM==AVI_FLY)
                O->Location-=LARA*Speed*Time*O->Left;
            else if(AM==AVI_WALK)
                O->Location-=WM*LARA*Speed*Time*(U&O->Front).Uint();
        }

        if(ViewActived&&(!ChangeView))
        {
            if(VUAD==1)
            {
                if(AM==AVI_WALK)
                {
                    if(O->Front*U<0.9)
                    {
                        O->Front=(sin(VUADS*Time)*O->Up+cos(VUADS*Time)*O->Front).Uint();
                        O->Up=(O->Front&O->Left).Uint();
                    }
                }else if(AM==AVI_FLY)
                {
                    O->Front=(sin(VUADS*Time)*O->Up+cos(VUADS*Time)*O->Front).Uint();
                    O->Up=(O->Front&O->Left).Uint();
                }
            }else if(VUAD==-1)
            {
                if(AM==AVI_WALK)
                {
                    if(O->Front*U>-0.9)
                    {
                        O->Front=(sin(-VUADS*Time)*O->Up+cos(-VUADS*Time)*O->Front).Uint();
                        O->Up=(O->Front&O->Left).Uint();
                    }
                }else if(AM==AVI_FLY)
                {
                    O->Front=(sin(-VUADS*Time)*O->Up+cos(-VUADS*Time)*O->Front).Uint();
                    O->Up=(O->Front&O->Left).Uint();
                }
            }
            if(AM==AVI_FLY)
            {
                if(VLAR==1)
                {
                    O->Front=(sin(VLARS*Time)*O->Left+cos(VLARS*Time)*O->Front).Uint();
                    O->Left=(O->Up&O->Front).Uint();
                }else if(VLAR==-1)
                {
                    O->Front=(sin(-VLARS*Time)*O->Left+cos(-VLARS*Time)*O->Front).Uint();
                    O->Left=(O->Up&O->Front).Uint();
                }
            }else if(AM==AVI_WALK)
            {
                XYZF R=(O->Front&U).Uint();
                XYZF F=(U&R).Uint();
                float Y1=O->Front*U,Z1=O->Front*F;
                float Y2=O->Up*U,Z2=O->Up*F;
                if(VLAR==1)
                {
                    O->Front=(Y1*U+Z1*(sin(-VLAR*Time)*R+cos(-VLAR*Time)*F)).Uint();
                    O->Up=(Y2*U+Z2*(sin(-VLAR*Time)*R+cos(VLAR*Time)*F)).Uint();
                    O->Left=(O->Up&O->Front).Uint();
                }else if(VLAR==-1)
                {
                    O->Front=(Y1*U+Z1*(sin(-VLAR*Time)*R+cos(-VLAR*Time)*F)).Uint();
                    O->Up=(Y2*U+Z2*(sin(-VLAR*Time)*R+cos(VLAR*Time)*F)).Uint();
                    O->Left=(O->Up&O->Front).Uint();
                }
            }
            if(AM==AVI_FLY)
            {
                if(VRAN==1)
                {
                    O->Up=(sin(VRANS*Time)*O->Left+cos(VRAN*Time)*O->Up).Uint();
                    O->Left=(O->Up&O->Front).Uint();
                }else if(VRAN==-1)
                {
                    O->Up=(sin(-VRANS*Time)*O->Left+cos(-VRAN*Time)*O->Up).Uint();
                    O->Left=(O->Up&O->Front).Uint();
                }
            }

        }
    }
}*/
#endif
