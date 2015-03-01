#ifndef WELCOMEASPCET_H
#define WELCOMEASPCET_H
#include "start.cpp"
#include "../p.o/calculate.h"
#include "../p.o/picture.h"
#include "../p.o/publicvalue.h"
#include "buttoncenter.h"
//#include <math>
#include "button.h"
class WelcomeAspect:public Plugin_Base
{
    class Push
    {
    public:
        XYF Location;
        long Time;
        float Max;
        Push(XYF Tc,long T,float M=1.0):Location(Tc),Time(T),Max(M){}
        float Function(XYF Tk,float Speed,long T)
        {
            float Tc=Tk.Distance(Location)/Speed;
            float Timecc=(T-Time)/1000.0+Tc;
            //if(Timecc>0){
            //error<< 3.0*(1/(Timecc+1.0))*sin(-3.1415926*Timecc)<<endl;
            return 0.2*Max*pow(2.1,-Timecc)*sin(-9.42*Timecc);

        }
    };
    XYF ML;
    int WPoint;
    int LPoint;
    int Time;
    float Speed;
    float Deep;
    long AllTime;
    bool StartChange;
    long StartTime;
    int Choose;
    Calculate Yc;
    ButtonCenter BC;
    std::list<Push> AllPush;
    PublicLock PL;
    XYZF *Point;
    Picture3D ShenSheOld;
    Picture3D ShenSheNew;
    float CalculateDeep(XYZF&);
public:
    WelcomeAspect(int W=80,int L=80,float S=0.5):Yc(50),Plugin_Base("WA"),WPoint(W),LPoint(L),Speed(S),Deep(-1.1),StartChange(false),StartTime(0)
    {
        Time=0;
        Choose=0;
        Point=new XYZF[(WPoint+1)*(LPoint+1)];
        for(int i=0;i<=LPoint;++i)for(int k=0;k<=WPoint;++k)
        {
            GetPoint(i,k)->Set((float(k)/WPoint*2.0-1.0),(1.0-float(i)/LPoint*2.0),0.0);
        }
    }
    ~WelcomeAspect(){delete[] Point;}
    XYZF* GetPoint(int i,int k){return &Point[i*(WPoint+1)+k];}
    void Init(ControlCenter *,long);
    void Main(ControlCenter *,long);
    void FlatShow(ControlCenter *Data);
    void Accessorial(ControlCenter *Data, long L);
    void ButtonStartGame(int K);
    void ButtonTeachGame(int K);
    void ButtonExitGame(int K);
    void BlendShow(ControlCenter *Data);
};

void WelcomeAspect::BlendShow(ControlCenter *Data)
{
    //error<<"透明"<<endl;
    if(StartChange&&StartTime>=5000)
    {
        if(StartTime<8000)
            glColor4f(0.0,0.0,0.0,1.0-(8000-StartTime)/3000.0);
        else
            glColor4f(0.0,0.0,0.0,1.0);
        glBegin(GL_QUADS);
        glVertex3f(-1.0,1.0,Deep+0.5);
        glVertex3f(-1.0,-1.0,Deep+0.5);
        glVertex3f(1.0,-1.0,Deep+0.5);
        glVertex3f(1.0,1.0,Deep+0.5);
        glEnd();
    }

}


void WelcomeAspect::ButtonStartGame(int K)
{
    AllPush.push_back(Push(XYF(0.0,0.0),AllTime));
    StartChange=true;
    BC.Disactive();
}
void WelcomeAspect::ButtonTeachGame(int K){}
void WelcomeAspect::ButtonExitGame(int K){Exit();}


void WelcomeAspect::FlatShow(ControlCenter* Data)
{
    //if(!StartChange)
    //{
        BC.Main(Data->IntervalTimeShow);
    //}
}


void WelcomeAspect::Init(ControlCenter *, long)
{
    ShenSheOld.Load("texture/welcome/shensheold22.jpg");
    ShenSheNew.Load("texture/welcome/shenshenew22.jpg");
    BC.Active();
    BC.Add(new Button(XYF(0.4,0.7),"开始游戏",&WelcomeAspect::ButtonStartGame,this));
    BC.Add(new Button(XYF(-0.2,0.0),"游戏教学",&WelcomeAspect::ButtonTeachGame,this));
    BC.Add(new Button(XYF(0.5,-0.6),"退出",&WelcomeAspect::ButtonExitGame,this));
}

void WelcomeAspect::Main(ControlCenter *, long K)
{
    //error<<"显示"<<endl;
    XYZF * T1;
    XYZF * T2;
    XYZF * T3;
    //KK.Show(XYZF(0.0,0.0,-2.0),XYZF(0.0,-1.0,0.0),XYZF(1.0,0.0,0.0));
    //KK.Show(XYZF(-1.0,1.0,-2.0),XYZF(0.0,-1.0,0.0),XYZF(1.0,0.0,0.0));
    Picture3D &KK=ShenSheOld;
    KK.StartShow(GL_TRIANGLES,1.0,1.0,1.0);
    //error<<"开始载入"<<endl;
    for(int i=1;i<=LPoint;++i)
    {
        //error<<"*";
        for(int k=0;k<WPoint;++k)
        {
            //error<<*T1<<*T2<<*T3<<endl;
            if(!StartChange||sqrt((i-LPoint/2.0)*(i-LPoint/2.0)+(k-WPoint/2.0)*(k-WPoint/2.0))>=StartTime*0.015)
            {
                T1=GetPoint(i-1,k+1);
                T2=GetPoint(i-1,k);
                T3=GetPoint(i,k);
                            //error<<*T1<<*T2<<*T3<<endl;
                KK.SetPoint((T1->X+1.0)/2.0,-(T1->Y+1.0)/2.0,*T1+XYZF(0.0,0.0,Deep));
                KK.SetPoint((T2->X+1.0)/2.0,-(T2->Y+1.0)/2.0,*T2+XYZF(0.0,0.0,Deep));
                KK.SetPoint((T3->X+1.0)/2.0,-(T3->Y+1.0)/2.0,*T3+XYZF(0.0,0.0,Deep));
                T1=GetPoint(i,k+1);
                T2=GetPoint(i-1,k+1);
                T3=GetPoint(i,k);
                            //error<<*T1<<*T2<<*T3<<endl;
                KK.SetPoint((T1->X+1.0)/2.0,-(T1->Y+1.0)/2.0,*T1+XYZF(0.0,0.0,Deep));
                KK.SetPoint((T2->X+1.0)/2.0,-(T2->Y+1.0)/2.0,*T2+XYZF(0.0,0.0,Deep));
                KK.SetPoint((T3->X+1.0)/2.0,-(T3->Y+1.0)/2.0,*T3+XYZF(0.0,0.0,Deep));
            }
        }
    }
    KK.EndShow();
    if(StartChange&&StartTime<8000)
    {
        Picture3D &KK2=ShenSheNew;
        KK2.StartShow(GL_TRIANGLES,1.0,1.0,1.0);
        for(int i=1;i<=LPoint;++i)
        {
            for(int k=0;k<WPoint;++k)
            {
                if(sqrt((i-LPoint/2.0)*(i-LPoint/2.0)+(k-WPoint/2.0)*(k-WPoint/2.0))<=StartTime*0.015)
                {
                    T1=GetPoint(i-1,k+1);
                    T2=GetPoint(i-1,k);
                    T3=GetPoint(i,k);
                    KK2.SetPoint((T1->X+1.0)/2.0,-(T1->Y+1.0)/2.0,*T1+XYZF(0.0,0.0,Deep+0.001));
                    KK2.SetPoint((T2->X+1.0)/2.0,-(T2->Y+1.0)/2.0,*T2+XYZF(0.0,0.0,Deep+0.001));
                    KK2.SetPoint((T3->X+1.0)/2.0,-(T3->Y+1.0)/2.0,*T3+XYZF(0.0,0.0,Deep+0.001));
                    T1=GetPoint(i,k+1);
                    T2=GetPoint(i-1,k+1);
                    T3=GetPoint(i,k);
                    KK2.SetPoint((T1->X+1.0)/2.0,-(T1->Y+1.0)/2.0,*T1+XYZF(0.0,0.0,Deep+0.001));
                    KK2.SetPoint((T2->X+1.0)/2.0,-(T2->Y+1.0)/2.0,*T2+XYZF(0.0,0.0,Deep+0.001));
                    KK2.SetPoint((T3->X+1.0)/2.0,-(T3->Y+1.0)/2.0,*T3+XYZF(0.0,0.0,Deep+0.001));
                }
            }
        }
        KK2.EndShow();
    }
}

void WelcomeAspect::Accessorial(ControlCenter *Data, long L)
{
    Yc+L;
    AllTime+=L;
    if(StartChange)
    {
        StartTime+=Data->IntervalTimeAnalyze;
        if(StartTime>8050)
        {
            Data->Regedit(new Start());
            Destory();
            error<<"Exit End"<<endl;
        }
    }
        if(Yc)
        {
            for(int i=0;i<=LPoint;++i)
            {
                for(int k=0;k<=WPoint;++k)
                {
                    GetPoint(i,k)->Z=CalculateDeep(*GetPoint(i,k));
                }

            }
            Yc=0;
        }
        while(Handle<Information> Tc=GetInformation())
        {
            BC.Control(Tc);
            if(Tc->IsMouseMotion())
            {
                ML.Set(Tc->Data1.f,Tc->Data2.f);
                Time+=1;
                if(Time>=15)
                {
                    AllPush.push_back(Push(ML,AllTime,0.2));
                    Time=0;
                }
            }else if(Tc->IsKeyDown())
            {
                //UsingMouse=false;
            }
        }
}

float WelcomeAspect::CalculateDeep(XYZF& C)
{
    float Tem=0.0;
    XYF Tk(C.X,C.Y);
    //error<<"进入计算"<<endl;
    //error<<"+"<<endl;
    for(std::list<Push>::iterator Po=AllPush.begin();Po!=AllPush.end();++Po)
    {
        //error<<"!!"<<endl;
        //error<<"计算"<<endl;
        if(0.2*Po->Max*pow(2.1,-(AllTime-Po->Time)/1000.0)<=0.005)
        {
            AllPush.erase(Po--);
        }else if(Tk.Distance(Po->Location)/Speed<(AllTime-Po->Time)/1000.0)
            Tem+=Po->Function(Tk,Speed,AllTime);

    }
    //error<<"-"<<endl;
    return Tem;
}

#endif // WELCOMEASPCET_H
