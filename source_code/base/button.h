#ifndef BUTTON_H
#define BUTTON_H
#include "../p.o/sgprint.h"
#include "../p.o/singlestaff.h"
class ButtonCenter;

class ButtonSeed:public HandleSeed
{
public:
    virtual void Run(int ID){}
};

template <class T>
        class MemoryRealButton:public ButtonSeed
{
public:
    void (T::*FunctionPoint)(int);
    T* User;
    virtual void Run(int ID){(User->*FunctionPoint)(ID);}
    MemoryRealButton(void (T::*FP)(int),T* U):FunctionPoint(FP),User(U){}
};

class NormalRealButton:public ButtonSeed
{
public:
    void (*FP)(int);
    virtual void Run(int ID){(*FP)(ID);}
    NormalRealButton(void (*Tc)(int)):FP(Tc){}
};

class Button:public SingleStaff<ButtonCenter*,long>
{
public:
    std::string Name;
    Sentence N;
    XYF Location;
    XYZF UnChooseColor;
    XYZF ChooseColor;
    Handle<ButtonSeed> Func;
    long Time;
    int ID;
    bool ChooseB;
    void Main(ButtonCenter*,long);
    void Add(std::string K){N.Add(K);}
    void Init(ButtonCenter* B,long T){N.Add(Name);SingleStaff<ButtonCenter*,long>::Init(B,T);}
    void SetID(int I){ID=I;}
    bool Choose(XYF Tk){if(((Tk.X-Location.X)<N.Size()*0.02&&(Tk.X-Location.X)>N.Size()*(-0.02))&&Tk.Y-Location.Y>-0.1&&Tk.Y<=Location.Y) ChooseB=true;else ChooseB=false;return ChooseB;}
    bool Choose(int I){if(I==ID) ChooseB=true;else ChooseB=false;return ChooseB;}
    void Respond(){if(Func){Func->Run(ID);}}
    template<class T>
    Button(XYF LO,std::string S,void (T::*FP)(int),T *L,XYZF UCC=XYZF(1.0,1.0,1.0),XYZF CC=XYZF(1.0,0.0,0.0))
        :ChooseB(false),Name(S),Location(LO),UnChooseColor(UCC),ChooseColor(CC)
    {
        Func=new MemoryRealButton<T>(FP,L);
        Time=rand()%5986;
    }
    Button(XYF L,std::string S,void (*FP)(int),XYZF UCC=XYZF(1.0,1.0,1.0),XYZF CC=XYZF(1.0,0.0,0.0))
        :ChooseB(false),Name(S),Location(L),UnChooseColor(UCC),ChooseColor(CC)
    {
        Func=new NormalRealButton(FP);
    }
};
void Button::Main(ButtonCenter*,long T)
{
    if(ChooseB)
        N.ShowXMiddle(Location+XYF(0.02*sin(Time/1000.0*3.14),0.02*cos(Time/1000.0*3.14)),ChooseColor.X,ChooseColor.Y,ChooseColor.Z);
    else
        N.ShowXMiddle(Location+XYF(0.02*sin(Time/1000.0*3.14),0.02*cos(Time/1000.0*3.14)),UnChooseColor.X,UnChooseColor.Y,UnChooseColor.Z,0.1);
    glColor3f(0.0,1.0,1.0);glBegin(GL_POINTS);glVertex(Location);glEnd();
    Time+=T;
}
#endif
