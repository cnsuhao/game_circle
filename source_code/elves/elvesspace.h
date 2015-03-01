#ifndef DIY_ELVESSPACE_H
#define DIY_ELVESSPACE_H
#include <list>
#include "../p.o/calculate.h"
#include "elves.h"
#include "../p.o/boss.h"
#include "../base/readsetting.h"
    typedef Handle<Staff<ElvesSpace*,long> > HS;
class ElvesSpace:public HandleSeed
{
public:
    XYF Mouse;
    Boss<ElvesSpace*,long> Bo;
    Calculate CTS;
    Calculate CTA;
    bool FinishInit;
    bool Change;
    Handle<Elves> Choosing;
    std::string ChooseName;
    std::map<std::string,Picture> Lihui;
    std::list<std::string> InitList;
    Picture Tk;
    virtual int Check(Handle<Elves>);//it have to return the valibal location
    virtual void ElvesAnalyze(long T);
    virtual void ElvesShow(long T);
    virtual int Check(float LX,float LY){return 0;}
    bool ChooseD(Handle<Elves>);
    void ToAll(Handle<Elves>);
    void Add(Handle<Elves>);
    void StaffCheckCrash(Handle<Elves> K,Handle<Elves> T);
    virtual void Init(){}
    void ForSetting(std::string,std::string,std::string,int);
    void ChangeBackGround(){}
    //Handle<Staff<ElvesSpace*,long> > FindA(bool (Staff<ElvesSpace*,long>::*P)(Handle<Staff<ElvesSpace*,long> >),Staff<ElvesSpace*,long>* Z){return Bo.FindSingle(P,Z);}
    Handle<Staff<ElvesSpace*,long> > Choose(float x,float Y);
    //Handle<ElvesBase> Select(float x, float y, float=0.1);
    ElvesSpace():CTS(200),CTA(200),FinishInit(true),Change(false){}
    void CheckCrash(Handle<Elves>);
};
void ElvesSpace::StaffCheckCrash(Handle<Elves> K,Handle<Elves> T)
{
    if(K)
    {
        if(T)
        {
            K->Solution(T);
        }
    }
}

void ElvesSpace::ForSetting(std::string N,std::string S,std::string T, int i)
{
    if(i==1)
    {
        Lihui[N].Load(T);
    }
}


void ElvesSpace::CheckCrash(Handle<Elves> T)
{
    if(T)
    {
        int Tem=Check(T);
        if(Tem!=0)
        {
            T->Stand=false;
            T->Movement=Tem;
        }
    }
}

int ElvesSpace::Check(Handle<Elves> H)
{
    if(H)
    {
        XYF Tem=Translate(H->Movement);
        XYF Tc;
        if(H->Location.X>0.8)
            Tc=Tc+XYF(-1.0,0.0);
        else         if(H->Location.X<-0.8)
            Tc=Tc+XYF(1.0,0.0);
        else        if(H->Location.Y>0.8)
            Tc=Tc+XYF(0.0,-1.0);
        else        if(H->Location.Y<-0.8)
            Tc=Tc+XYF(0.0,1.0);
        H->Movement=Translate(Tem+Tc);
    }
}


void ElvesSpace::ToAll(Handle<Elves> H)
{
    if(H)
    {
        H->Choose=false;
    }
}

bool ElvesSpace::ChooseD(Handle<Elves> H)
{
    if(H)
    {
        //return true;
        if((Mouse-H->Location).Long2()<0.005)
        {
            return true;
        }
    }
    return false;
}

Handle<Staff<ElvesSpace*,long> > ElvesSpace::Choose(float x,float Y)
{
    Mouse.Set(x,Y);
    //Choosing.Lock();
    Choosing.Unused();
    HS Tem;
    Bo.Train(&ElvesSpace::ToAll,this);
    
    if(Bo.Find(Tem,&ElvesSpace::ChooseD,this))
    {
        Choosing=Tem;
        if(Choosing)
        {
            Choosing->Choose=true;
        }
    }
    return Tem;
}

void ElvesSpace::Add(Handle<Elves> T)
{
    if(T)
    {
        if(AllSet.IsReady(T->Name,"JINGLING"))
        {
            std::string Tc;
            /*if(AllSet.FindFirst(T->Name,"JINGLING",Tc))
                //error<<"wanchngzairu"<<endl;
            else
                //error<<"sdfsdgf"<<endl;*/
            T->SetFile(Tc);
            AllSet.Search(T->Name,"LIHUI",&ElvesSpace::ForSetting,this);
            Bo.Employ(T);
        }else{
            //error<<"meiyouzhaodao"<<endl;
        }
    }
}


void ElvesSpace::ElvesAnalyze(long T)
{
    Bo.Accessorial(this,T);
    CTS+T;
    if(CTS)
    {
        //Bo.StaffTransfer(this,T);
        Bo.Conflict(&ElvesSpace::StaffCheckCrash,this);
        Bo.Train(&ElvesSpace::CheckCrash,this);
        CTS=0;
    }
}

void ElvesSpace::ElvesShow(long T)
{
    //Bo.Main(this,T);
    std::string Tem;
    if(Choosing)
    {
        Tem=Choosing->Name;
        if(Choosing->Location.X<0.0)
        {
            Lihui[Tem].Show(0.2,0.8,1.0,-1.0);
        }else{
            Lihui[Tem].Show(-1.0,0.8,-0.2,-1.0);
        }
    }
}

#endif // ELVESSPACE_H
