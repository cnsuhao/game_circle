#ifndef VIEW_H
#define VIEW_H
#include "../p.o/baseclass.h"
#include "../p.o/information.h"
#include "../p.o/handle.h"
#define Vie_Up 1
#define Vie_Dow 2
#define Vie_Rig 3
#define Vie_Lef 4
class View
{
    int UAD;
    int RAL;
public:
    Coordinate ViewCD;
    XYZF& Front(){return ViewCD.Front;}
    XYZF& Up(){return ViewCD.Up;}
    XYZF& Left(){return ViewCD.Left;}
    void Run(float Time,Coordinate &Co,float UL=0.95,float Dl=-0.95,float AngleUD=0.005, float AngleLR=0.005);
    void TakeControl(int Mode);
};
void View::TakeControl(int Mode)
{
    switch(Mode)
    {
            case Vie_Up:
                UAD=1;
        break;
    case Vie_Dow:
        UAD=-1;
        break;
    case Vie_Rig:
        RAL=1;
        
        break;
    case Vie_Lef:
        RAL=-1;
        break;
    }
}
void View::Run(float Time, Coordinate &Co, float UL, float DL,float AngleUD, float AngleLR)
{
    if(UAD==1)
        {
            if(ViewCD.Front*Co.Up<=UL)
            {
                ViewCD.Front=(sin(AngleUD*Time)*ViewCD.Up+cos(AngleUD*Time)*ViewCD.Front).Uint();
                ViewCD.Up=(ViewCD.Front&ViewCD.Left).Uint();
            }
        }
    if(UAD==-1)
        {
            if(ViewCD.Front*Co.Up>=DL)
            {
                ViewCD.Front=(sin(-AngleUD*Time)*ViewCD.Up+cos(-AngleUD*Time)*ViewCD.Front).Uint();
                ViewCD.Up=(ViewCD.Front&ViewCD.Left).Uint();
            }
        }
    if(RAL==1)
        {
            XYZF F=Co.Up&ViewCD.Left;
            ViewCD.Left=(cos(-AngleLR*Time)*ViewCD.Left+sin(-AngleLR*Time)*F).Uint();
            float TemX=ViewCD.Front*F;
            float TemY=ViewCD.Front*Co.Up;
            F=Co.Up&ViewCD.Left;
            ViewCD.Front=(TemX*F+TemY*Co.Up).Uint();
            ViewCD.Up=(ViewCD.Front&ViewCD.Left).Uint();
            //View
/*
            XYZF R=ViewCD.Front.ToCoordinate(Co.Left,Co.Up,Co.Front);
            XYZF F=ViewCD.Up.ToCoordinate(Co.Left,Co.Up,Co.Front);
            R.Set(cos(AngleLR*Time)*R.X-sin(AngleLR*Time)*R.Z,R.Y,sin(AngleLR*Time)*R.X+cos(AngleLR*Time)*R.Z);
            F.Set(cos(AngleLR*Time)*F.X-sin(AngleLR*Time)*F.Z,F.Y,sin(AngleLR*Time)*F.X+cos(AngleLR*Time)*F.Z);
            R.FromCoordinate(Co.Left,Co.Up,Co.Front);
            F.FromCoordinate(Co.Left,Co.Up,Co.Front);
            ViewCD.Front=R.Uint();
            ViewCD.Up=F.Uint();*/
        }
    if(RAL==-1)
        {
                        XYZF F=Co.Up&ViewCD.Left;
            ViewCD.Left=(cos(AngleLR*Time)*ViewCD.Left+sin(AngleLR*Time)*F).Uint();
            float TemX=ViewCD.Front*F;
            float TemY=ViewCD.Front*Co.Up;
            F=Co.Up&ViewCD.Left;
            ViewCD.Front=(TemX*F+TemY*Co.Up).Uint();
            ViewCD.Up=(ViewCD.Front&ViewCD.Left).Uint();
            /*XYZF R=ViewCD.Front.ToCoordinate(Co.Left,Co.Up,Co.Left);
            XYZF F=ViewCD.Up.ToCoordinate(Co.Left,Co.Up,Co.Left);
            R.Set(cos(-AngleLR*Time)*R.X-sin(-AngleLR*Time)*R.Z,R.Y,sin(-AngleLR*Time)*R.X+cos(-AngleLR*Time)*R.Z);
            F.Set(cos(-AngleLR*Time)*F.X-sin(-AngleLR*Time)*F.Z,F.Y,sin(-AngleLR*Time)*F.X+cos(-AngleLR*Time)*F.Z);
            R.FromCoordinate(Co.Left,Co.Up,Co.Left);
            F.FromCoordinate(Co.Left,Co.Up,Co.Left);
            ViewCD.Front=R.Uint();
            ViewCD.Up=F.Uint();*/
        }
    UAD=0;
    RAL=0;
}




#endif // VIEW_H
