#ifndef DIY_START_CPP
#define DIY_START_CPP
#include <string>
#include "../p.o/plugin_base.h"
#include "../base/readsetting.h"
Setting AllSet("setting/resource.txt");
#include "../p.o/picture.h"
#include "../p.o/sgprint.h"
#include "../p.o/elvestexture.h"
//#include "../realm/bolirealm.cpp"
//#include "../personage/bolilingmeng.h"
#include "viewer.cpp"
#include "../elves/bolishenshe/elvesspacebolishenshe.h"
#include "../elves/elves.h"

class Start:public Plugin_Base
{
    Picture Text;
    Picture Text2;
    Sentence Se;
    Sentence Se2;
    Sentence Se3;
    float X;
    float Y;
    Handle<ElvesSpace> EC;
    PublicValue<Handle<Elves> > Hv;
    //Handle<Personage> Player;
    //Handle<Personage> Enermy;
    Calculate MS;
    long Time;
    bool StartChange;
    public:
        //void Main(ControlCenter*,long);
        void FlatShow(ControlCenter*);
        void Accessorial(ControlCenter*,long);
        //void Show(ControlCenter*);
        void Init(ControlCenter*,long);
        Start():Plugin_Base("Start"),MS(100),Time(0),StartChange(false)
        {

        }
};
/*void Start::Show(ControlCenter* CC)
{
    Text2.Show(-1.0,1.0,1.0,-1.0);
    Text.Show(-1.0,1.0,0.0,-1.0);
}*/
void Start::FlatShow(ControlCenter* CC)
{
    if(!(StartChange&&Time>2000))
    {
        if(EC)
            EC->ElvesShow(CC->IntervalTimeShow);
        Se.ShowXMiddle(0.0,0.8,0.0,1.0,0.0,0.1);
    }
    /*if(StartChange)
    {
        Time+=CC->IntervalTimeShow;
        bool IsBland=glIsEnabled(GL_BLEND);
        glEnable(GL_BLEND);
        if(Time<2000)
            glColor4f(0.0,0.0,0.0,1.0-(2000-Time)/1000.0);
        else
            glColor4f(0.0,0.0,0.0,1.0);
        glBegin(GL_QUADS);
        glVertex2f(-1.0,1.0);
        glVertex2f(-1.0,-1.0);
        glVertex2f(1.0,-1.0);
        glVertex2f(1.0,1.0);
        glEnd();
        if(!IsBland)
            glDisable(GL_BLEND);
    }else{
        if(Time<=2000)
        {
            bool IsBland=glIsEnabled(GL_BLEND);
            glEnable(GL_BLEND);
            glColor4f(0.0,0.0,0.0,(2000-Time)/1000.0);
            glBegin(GL_QUADS);
            glVertex2f(-1.0,1.0);
            glVertex2f(-1.0,-1.0);
            glVertex2f(1.0,-1.0);
            glVertex2f(1.0,1.0);
            glEnd();
            if(!IsBland)
                glDisable(GL_BLEND);
            Time+=CC->IntervalTimeShow;
        }
    }*/
    //Text2.Show(-1.0,1.0,1.0,-1.0);
    //Text.Show(0.0,0.6,1.0,-1.0);
    //ET.Show(0.0,0.0,H,L);
    //Se3.Show(0.0,0.7,0.0,1.0,0.0,0.1);
    //Se2.Show(-1.0,0.0,0.0,1.0,0.0,0.1);
}
void Start::Accessorial(ControlCenter* CC,long T)
{
    while(!InformationEmpty())
    {
        Handle<Information> HI=Plugin_Base::GetInformation();
        if(HI)
        {
            if(HI->IsMouseMotion())
            {
                X=HI->Data1;
                Y=HI->Data2;
            }else if(HI->IsMouseButtonUp()&&HI->IsMouseButtonLeft())
            {
                if(EC->Choosing)
                {
                    Time=0;
                    StartChange=true;
                }
            }
        }
        MS+CC->IntervalTimeAnalyze;
        if(MS)
        {
            if(EC)
            {
                //Handle<Staff<ElvesSpace,long> > Tem;
                //Handle<Elves> Trcc;
                EC->Choose(X,Y);
            }
            MS=0;
        }
        if(EC)
        {
            EC->ElvesAnalyze(CC->IntervalTimeAnalyze);
        }
        if(StartChange)
        {
            if(Time>2000)
            {
                //error<<"regedit viewer"<<endl;
                //CC->Regedit(new Viewer());
                //error<<"strt to kill"<<endl;
                Killmyself();
            }
        }
    }
}
    /*static bool KeyPush=false;
    static float Angle=0;
    Angle+=0.02*CC->IntervalTimeAnalyze/1000.0;
    if(Enermy)
    {
        Enermy->Location.Set(10.0*sin(Angle),0.0,10.0*cos(Angle));
    }
    while(!Library.empty())
    {
        Handle<Information> Tem=GetInformation();
        if(Tem)
        {
            if(Tem->Category1==INFEVENT)
            {
                if(Tem->Category2==INFKEY)
                {
                    if(Tem->Category3==INFKEYDOWN)
                    {
                        Tc+=Tem->Data1.uc;
                        if(Tem->Data1.uc=='a')
                        {
                            KeyPush=true;
                        }
                    }
                    if(Tem->Category3==INFKEYUP)
                    {
                        if(Tem->Data1.uc=='a')
                        {
                            if(KeyPush&&!InitRealm)
                            {
                                Handle<BoliRealm> Ty=new BoliRealm(Player);
                                Handle<Plugin_Base> Re=Ty.Data;
                                Player=new LingMeng();
                                Enermy=new LingMeng();
                                Handle<Object> Pc=Player.Data;
                                //Player->SC.GetSpecial(new TaiJiSpecial());
                                //Player->SC.GetSpecial(new StarSpecial());
                               // Handle<Spell> S=new Spell(2000,10000);
                                //S->SC.GetSpecial(new TaiJiSpecial());
                                //S->SC.GetSpecial(new StarSpecial());
                                //Player->SP.GetSpell(S);
                                Pc->Location.Set(0.0,-0.4,0.0);
                                Ty->GetObject(Pc);
                                
                                Pc=Enermy.Data;
                                Pc->Location.Set(0.0,-0.4,-10.0);
                                Ty->GetObject(Pc);
                                CC->Regedit(Re);
                                //FunFla=false;
                                LockMouse();
                                InitRealm=true;
                            }
                            KeyPush=false;
                        }else if(Tem->Data1.uc==27)
                        {
                            Exit();
                        }
                    }
                }
            }
            if(InitRealm)
            {
                Player->BaseControl(Tem);
            }
        }
    }
}*/
void Start::Init(ControlCenter* CC,long T)
{
    std::fstream Setting("setting/welcomesetting.txt",std::ios::in);
    std::string Tem;
    int Mode=0;
    while(Setting>>Tem)
    {
        if(Tem=="CHARACTER")
        {
            Mode=1;
        }else if(Tem=="SCENE")
        {
            Mode=2;
        }else if(Mode==1)
        {
            if(Tem=="NULL"||Tem=="LINGMENG")
            {
                //Text.Load("texture/lingmeng/lingmenglihui.png");
                //EC.Set(new Elv_Bolishenshe());
                EC=new Elv_Bolishenshe();
                EC->Init();
                EC->Add(new Elves("LINGMENG",8,4,(rand()%201-100)/100.0,(rand()%201-100)/100.0));
                EC->Add(new Elves("MOLISHA",8,4,(rand()%201-100)/100.0,(rand()%201-100)/100.0));
                //error<<"¼ÓÈë"<<endl;
            }
        }else if(Mode==2)
        {
            if(Tem=="NULL"||Tem=="BOLISHENSHE")
            {
                //Text2.Load("texture/welcome/bolishenshe.jpg");
            }
        }
    }
    Setting.close();
    Se.Add("Touhou Big RUn");
    Plugin_Base::Init(CC,T);
    //ET.Load("texture/lingmeng/lingmengjingling.png",4,8);
}

#endif
