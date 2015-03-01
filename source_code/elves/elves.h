#ifndef DIY_ELVES_H
#define DIY_ELVES_H
#include <string>
#include <fstream>
#include "../p.o/handle.h"
#include "../p.o/elvestexture.h"
#include "../p.o/calculate.h"
#include "../p.o/staff.h"
#define Elv_Up 4
#define Elv_Dow 1
#define Elv_Rig 3
#define Elv_Lef 2
#define Elv_UR 8
#define Elv_UL 7
#define Elv_DR 6
#define Elv_DL 5
class ElvesSpace;
XYF Translate(int);
int Translate(XYF);

class Elves:public Staff<ElvesSpace*,long>
{
public:
    std::string File;
    int H;
    int L;
    ElveTexture ET;
    XYF Location;
    std::string Name;
    int Movement;
    int TX;
    Calculate Ti;
    Calculate TC;
    Calculate Pi;
    int Hungry;
    int Happy;
    bool Stand;
    bool Stop;
    bool Choose;
    virtual void Main(ElvesSpace*,long);
    void Solution(Handle<Elves>);
    void SetFile(std::string F){File=F;}
    virtual void Accessorial(ElvesSpace*,long);
    void Init(ElvesSpace *, long );
    int Contribution(ElvesSpace *, long );
    //virtual Analyze();
    Elves(std::string N,int h,int l,float LX,float LY):Name(N),H(h),L(l),Location(LX,LY),Stand(false),
        Movement(1),TX(1),Ti(800),TC(500),Pi(100),Choose(false),Happy(10000),Hungry(10000){}
    virtual ~Elves(){ET.Delete();}
    void Judge();
};

void Elves::Solution(Handle<Elves> H)
{
    if(H)
    {
        XYF Tc=Location-H->Location;
        if(Tc.Long2()<0.005)
        {
            XYF Tc=H->Location-Location;
            H->Movement=Translate(1.5*Tc+Translate(H->Movement));
            Tc=-1.0*Tc;
            Movement=Translate(1.5*Tc+Translate(Movement));
        }
    }
}

int Elves::Contribution(ElvesSpace *t, long p)
{
    return (int)((Location.Y+2.0)*1000);
}


void Elves::Init(ElvesSpace * E, long T)
{
    ET.Load(File,H,L,1.0);
    Staff<ElvesSpace*,long>::Init(E,T);
}


void Elves::Main(ElvesSpace*,long)
{
    glColor3f(1.0,0.0,0.0);
    if(Choose)
    {
        ET.ShowMiddle(Location.X,Location.Y,1,1,0.1);
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_QUADS);
        glVertex(Location.X-0.05,Location.Y+0.08);
        glVertex(Location.X-0.05,Location.Y+0.07);
        glVertex(Location.X-0.05+0.1*(Happy/10000.0),Location.Y+0.07);
        glVertex(Location.X-0.05+0.1*(Happy/10000.0),Location.Y+0.08);
        glEnd();
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_QUADS);
        glVertex(Location.X-0.05,Location.Y+0.09);
        glVertex(Location.X-0.05,Location.Y+0.08);
        glVertex(Location.X-0.05+0.1*(Hungry/10000.0),Location.Y+0.08);
        glVertex(Location.X-0.05+0.1*(Hungry/10000.0),Location.Y+0.09);
        glEnd();
    }
    else
        ET.ShowMiddle(Location.X,Location.Y,Movement,TX,0.1);
}


void Elves::Accessorial(ElvesSpace* ES,long T)
{
    //Hungry-=1;
    //if(Hungry<=0) Destory();
    Pi+T;
    if(Pi)
    {
        Pi=0;
    }
    if(!Choose)
    {
        if(!Stand)
        {
            if(rand()%5001==0)
            {
                Stand=true;
            }else if(rand()%10001==0)
            {
                Movement=rand()%8+1;
            }
            Location=Location+0.00008*(T)*Translate(Movement);
        }else{
            if(rand()%1000==0)
            {
                Stand=false;
                Movement=rand()%8+1;
            }
        }
        TC+T;
        if(TC)
        {
            if(!Stand)
            {
                TX+=1;
                if(TX>4)
                    TX=1;
            }else{
                TX=1;
            }
            TC=0;
        }
    }

}

int Translate(XYF T)
{
    if(T.X>0&&T.Y>0)
        return Elv_UR;
    else if(T.X>0&&T.Y<0)
        return Elv_DR;
    else if(T.X<0&&T.Y<0)
        return Elv_DL;
    else if(T.X<0&&T.Y>0)
        return Elv_UL;
    else if(T.X>0)
        return Elv_Rig;
    else if(T.X<0)
        return Elv_Lef;
    else if(T.Y<0)
        return Elv_Dow;
    else if(T.Y>0)
        return Elv_Up;
    else
        return 0;
}

XYF Translate(int T)
{
    XYF Tem;
    if(T==Elv_Up)
    {
        Tem.Set(0.0,1.0);
        return Tem;
    }else     if(T==Elv_Dow)
    {
        Tem.Set(0.0,-1.0);
        return Tem;
    }else    if(T==Elv_Lef)
    {
        Tem.Set(-1.0,0.0);
        return Tem;
    }else    if(T==Elv_Rig)
    {
        Tem.Set(1.0,0.0);
        return Tem;
    }else    if(T==Elv_UR)
    {
        Tem.Set(1.0,1.0);
        return Tem.Uint();
    }else if(T==Elv_UL)
    {
        Tem.Set(-1.0,1.0);
        return Tem.Uint();
    }else if(T==Elv_DR)
    {
        Tem.Set(1.0,-1.0);
        return Tem.Uint();
    }else if(T==Elv_DL)
    {
        Tem.Set(-1.0,-1.0);
        return Tem.Uint();
    }else
        return Tem;
}

#endif // ELVES_H
