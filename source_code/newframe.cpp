#include <fstream>
        using namespace std;
        fstream Error("Error.txt",ios::out);
#include <sstream>
#include <windows.h>
#include "p.o/po.h"
#include "p.o/popicture.h"
#include "scene/scene.h"
#include "p.o/baseclass.h"
#include "star/movestar.h"
#include "star/regularstar.h"
#include "p.o/dialog.h"
#include "p.o/scription/scriptionblock.h"
#include "p.o/scription/scriptionanalyze.h"
#include "p.o/popicture.h"
#include "star/motionstar.h"
#include "star/blackstar.h"
#include "star/jumpstar.h"
#include "star/antistar.h"
#include "star/playerstar.h"
#include "star/zhexuestar.h"
#include "star/baihestar.h"
#include "star/partystar.h"
#include "star/normalstar.h"
#define VIEW_SPEED 1.0
#define MAX_SPEED 0.5
#define GRAVITY_FORCE 2.25
#define MAP_POINT_X 81
#define MAP_POINT_Y 81
#define MAP_X 80.0
#define MAP_Y 80.0
        float CalculateForce(const XYF& T,const XYF& T2,const float& R1,const float& R2)
        {
            XYF Tc=T-T2;
            float R=Tc.Long2();
            float Rou=0.000;
            if(R>0.001)
                Rou=GRAVITY_FORCE*R1*R1*R2*R2/R;
            return Rou;
        }
std::string SScene;
std::string SFont="font/fksnjt.ttc";
class Tem:public Plugin
{
public:
    float* MapPoint;
    unsigned int* O;
    bool Win;
    bool Loose;
    PlayerStar SB;
    StarBase SBTarget;
    StarBase SBTargetSmall;
    POTTF WinT;
    POTTF Scr;
    POTTF Lose;
    Tank<Handle<RegularStar> > TRS;
    Tank<Handle<AntiStar> > ATRS;
    Tank<Handle<MoveStar> > TMS;
    Tank<Handle<MotionStar> > TMOS;
    Tank<Handle<BlackStar> > TBS;
    Tank<Handle<JumpStar> > TJS;
    Tank<Handle<ZhexueStar> > TZXS;
    Tank<Handle<BaiheStar> > TBHS;
    Tank<Handle<PartyStar> > TPS;
    Tank<Handle<NormalStar> > TNS;
    std::map<int,ScriptionBlock> SBM;
    FileFactor FF;
    XYF View;
    XYF Point;
    XYF Target;
    Dialog D;
    POPicture PP;
    POTTF PTTF;
    int Stage;
    int TStage;
    bool InitB;
    bool KeyUp,KeyDown,KeyRight,KeyLeft;
    bool SelectPlayer,MouseControl,Run;
    void ReSet(){SelectPlayer=false;MouseControl=false;Run=false;}
    void ReStartStage(){Stage=-1;ReSet();}
    bool Key(){return true;}
    bool Mouse(){return true;}
    void Layer2D(POMain *P);
    void Layer3D(POMain *P);
    void Init(PO *);
    void Accessorial(POMain *);
    void Ana(Information*,POMain*);
    Tem():Plugin("Tem"),InitB(false),SB(XYF(0.0,0.0),0.05),View(0.0,0.0),Stage(0),TStage(1)
    {
        MapPoint=new float[MAP_POINT_X*MAP_POINT_Y*2];
        O=new unsigned int[MAP_POINT_X*MAP_POINT_Y];
        for(int i=0;i<MAP_POINT_X;++i)
        {
            for(int k=0;k<MAP_POINT_Y;++k)
            {
                MapPoint[(i*MAP_POINT_X+k)*2]=MAP_X/(-2.0)+MAP_X/(MAP_POINT_X-1)*i;
                MapPoint[(i*MAP_POINT_X+k)*2+1]=MAP_Y/(2.0)-MAP_Y/(MAP_POINT_Y-1)*k;
            }
        }
        for(int i=0;i<MAP_POINT_X*MAP_POINT_Y;++i)
            O[i]=i;
    }
};

void Tem::Layer3D(POMain *P)
{
    //if(Tr)Tr->Display();
}


void Tem::Layer2D(POMain *P)
{
    if(!InitB)
    {
        MoveStar::P=P->CreatTTF("飞");
        BlackStar::P=P->CreatTTF("传");
        JumpStar::P=P->CreatTTF("蛋");
        MotionStar::P=P->CreatTTF("动");
        RegularStar::P=P->CreatTTF("吸");
        AntiStar::P=P->CreatTTF("斥");
        PlayerStar::P=P->CreatTTF("军");
        ZhexueStar::P=P->CreatTTF("♂");
        BaiheStar::P=P->CreatTTF("♀");
        PlayerStar::P=P->CreatTTF("党");
        NormalStar::P=P->CreatTTF("障");
        WinT=P->CreatTTF("恭喜你，你过关了！");
        Scr=P->CreatTTF("点击鼠标左键继续");
        Lose=P->CreatTTF("对不起，你失败了。");
        InitB=true;
    }
    if(TStage!=Stage)
    {
        Win=false;
        Loose=false;
        TRS.Clear();
        TMS.Clear();
        ATRS.Clear();
        TMOS.Clear();
        TBS.Clear();
        TJS.Clear();
        TZXS.Clear();
        TBHS.Clear();
        TPS.Clear();
        TNS.Clear();
        std::map<int,ScriptionBlock>::iterator Po=SBM.find(TStage);
        D.Clear();
        SB.CleanAll();
        ReSet();
        if(Po!=SBM.end())
        {
            for(CommentPoint CP=Po->second.Begin();CP!=Po->second.End();++CP)
            {
                bool Co=true;
                if(CP->Is("D"))
                    D.AddLine(CP->Scription());
                else if(CP->Is("Player")||CP->Is("Target")||CP->Is("FX")||CP->Is("XL")||CP->Is("CL")||CP->Is("DL")||CP->Is("CS")||CP->Is("DD")
                        ||CP->Is("ZX")||CP->Is("BH")||CP->Is("GC")||CP->Is("ZA"))
                {
                    int Size=0;
                    float D[10];
                    for(FileFactorPoint FFP=CP->ScriptionBegin;FFP!=CP->ScriptionEnd&&Size<10;++FFP,++Size)
                    {
                        if(FFP->IsNumber()) Translate(FFP->Detail(),D[Size]);
                        else if(FFP->Is("-"))
                        {
                            ++FFP;
                            if(FFP!=CP->ScriptionEnd)
                            {
                                if(FFP->IsNumber()){Translate(FFP->Detail(),D[Size]);D[Size]=-D[Size];}else Co=false;
                            }else Co=false;
                        }else Co=false;
                        if(!Co)break;
                    }
                    if(Size==3)
                    {
                        if(CP->Is("Player")){SB.Set(XYF(D[0],D[1]),D[2]);View.Set(D[0],D[1]);}
                        else if(CP->Is("Target")) SBTarget.Set(XYF(D[0],D[1]),D[2],1.0,0.0,0.0);
                        else if(CP->Is("XL")){TRS.PushBack(new RegularStar(XYF(D[0],D[1]),D[2]));}
                        else if(CP->Is("CL")){ATRS.PushBack(new AntiStar(XYF(D[0],D[1]),D[2]));}
                        else if(CP->Is("ZX")){TZXS.PushBack(new ZhexueStar(XYF(D[0],D[1]),D[2]));}
                        else if(CP->Is("BH")){TBHS.PushBack(new BaiheStar(XYF(D[0],D[1]),D[2]));}
                        else if(CP->Is("GC")){TPS.PushBack(new PartyStar(XYF(D[0],D[1]),D[2]));}
                        else if(CP->Is("ZA")){TNS.PushBack(new NormalStar(XYF(D[0],D[1]),D[2]));}
                        else Co=false;
                    }else if(Size==4)
                    {
                        if(CP->Is("DL")){TMOS.PushBack(new MotionStar(XYF(D[0],D[1]),D[2],D[3]));}
                        else Co=false;
                    }else if(Size==5)
                    {
                        if(CP->Is("FX")){Handle<MoveStar> TemC=new MoveStar(XYF(D[0],D[1]),D[2]);TemC->Launch(XYF(D[3],D[4]));TMS.PushBack(TemC);}
                        else Co=false;
                    }else if(Size==6)
                    {
                        if(CP->Is("CS")){TBS.PushBack(new BlackStar(XYF(D[0],D[1]),D[2],XYF(D[3],D[4]),D[5]));}
                        else Co=false;
                    }else if(Size==7)
                    {
                        if(CP->Is("DD")){TJS.PushBack(new JumpStar(XYF(D[0],D[1]),D[2],XYF(D[3],D[4]),D[5],D[6],0.0));}
                        else Co=false;
                    }else if(Size==8)
                    {
                        if(CP->Is("DD")){TJS.PushBack(new JumpStar(XYF(D[0],D[1]),D[2],XYF(D[3],D[4]),D[5],D[6],D[7]));}
                        else Co=false;
                    }else Co=false;
                }else if(CP->Is("B"))
                    PP=P->CreatPicture(CP->Scription());
                if(!Co) {GetError("Comment "+CP->Detail()+" Is Not Correct",CP->Line());break;}
            }
            Stage=TStage;
            D.Init(P);
        }else{
            P->Exit();
        }
    }
    if(HaveScriptionError())
    {
        using namespace std;
        //fstream Error("Error.txt",ios::out);
        DisplayError(Error);
        P->Exit();
    }
    if(!Run)
        glTranslatef(-View.X,-View.Y,0.0);
    else
        glTranslatef(-SB.Location.X-View.X,-SB.Location.Y-View.Y,0.0);
    if(PP)
        PP.Display(XYF(-20.0,20.0),XYF(40.0,0.0),XYF(0.0,-40.0));
    glPointSize( 5 );
    glColor4f(1.0,1.0,1.0,0.5);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2,GL_FLOAT,0,MapPoint);
    glDrawElements(GL_POINTS,MAP_POINT_X*MAP_POINT_Y, GL_UNSIGNED_INT,O);
    glDisableClientState(GL_VERTEX_ARRAY);
    for(Tank<Handle<RegularStar> >::Ladle Po=TRS.Begin();Po!=TRS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<MoveStar> >::Ladle Po=TMS.Begin();Po!=TMS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<AntiStar> >::Ladle Po=ATRS.Begin();Po!=ATRS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<MotionStar> >::Ladle Po=TMOS.Begin();Po!=TMOS.End();++Po)
        if(*Po)  (*Po)->Display();
    for(Tank<Handle<BlackStar> >::Ladle Po=TBS.Begin();Po!=TBS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<JumpStar> >::Ladle Po=TJS.Begin();Po!=TJS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<ZhexueStar> >::Ladle Po=TZXS.Begin();Po!=TZXS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<BaiheStar> >::Ladle Po=TBHS.Begin();Po!=TBHS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<PartyStar> >::Ladle Po=TPS.Begin();Po!=TPS.End();++Po)
        if(*Po) (*Po)->Display();
    for(Tank<Handle<NormalStar> >::Ladle Po=TNS.Begin();Po!=TNS.End();++Po)
        if(*Po) (*Po)->Display();

    XYF T,L;
    if(!Run) T=SBTarget.Location-View;
    else if(Run) T=SBTarget.Location-View-SB.Loc();
    if(T.Long()>1.0)
    {
        T=T.Uint(0.9);
        if(!Run)
            L=T+View;
        else
            L=T+View+SB.Loc();
        SBTargetSmall.Set(L,0.02,1.0,0.0,0.0);
        SBTargetSmall.Display();
    }else
        SBTarget.Display();
    SB.Display();
    SBTarget.Display();
    if(SelectPlayer)
    {
        XYF Tem=Target-Point;
        if(Tem.Long()>=MAX_SPEED)
        {
            glColor3f(1.0,0.0,0.0);
            Tem=Tem.Uint(MAX_SPEED);
            glBegin(GL_LINES);
            glVertex(Point);
            glVertex(Point+Tem);
            glEnd();
        }else{
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_LINES);
            glVertex(Point);
            glVertex(Target);
            glEnd();
        }
    }
    glLoadIdentity();
    D.Display(XYF(-1.0,1.0),XYF(1.0,0.0),0.0,1.0,1.0,0.5);
    if(Win)
    {
        WinT.DisplayMiddle(XYF(0.0,0.2),XYF(1.0,0.0),0.1);
        Scr.DisplayMiddle(XYF(0.0,0.1),XYF(1.0,0.0),0.08);
    }else if(Loose)
    {
        Lose.DisplayMiddle(XYF(0.0,0.2),XYF(1.0,0.0),0.1);
        Scr.DisplayMiddle(XYF(0.0,0.1),XYF(1.0,0.0),0.08);
    }
}
void Tem::Init(PO * P)
{
    SBTarget.Set(XYF(2.0,2.0),0.1,1.0,0.0,0.0);
    FF.Separate("stage.txt");
    ScriptionBlock SBT(FF.Begin(),FF.End());
    std::map<int,ScriptionBlock>::iterator Po=SBM.end();
    int Stage=1;
    D.MaxChar(60);
    for(CommentPoint CP=SBT.Begin();CP!=SBT.End();++CP)
    {
        if(CP->Is("Stage"))
        {
            SBM[Stage];
            Po=SBM.find(Stage);
            Stage++;
        }else{
            if(Po!=SBM.end())
                Po->second.InsertComment(CP);
        }
    }
    if(HaveScriptionError())
    {
        using namespace std;
        //fstream Error("Error.txt",ios::out);
        DisplayError(Error);
        P->Exit();
    }
    //MoveStar::P=P->CreatTTF("飞");
    //PTTF=P->CreatTTF("Fei");
}

void Tem::Accessorial(POMain *P)
{
    Analyze(&Tem::Ana,this,P);
    if(KeyUp) View.Y+=VIEW_SPEED*P->Time()/1000.0;
    if(KeyDown) View.Y-=VIEW_SPEED*P->Time()/1000.0;
    if(KeyLeft) View.X-=VIEW_SPEED*P->Time()/1000.0;
    if(KeyRight) View.X+=VIEW_SPEED*P->Time()/1000.0;

    if((!Win)&&(!Loose))
    {
        SB.Assorial(P->Time());
        if(Run)
        {
            if(SBTarget.Crash(&SB))
            {
                Win=true;return ;
            }else{
                bool Sp=false;
                for(Tank<Handle<PartyStar> >::Ladle Po=TPS.Begin();Po!=TPS.End();++Po)
                    if(*Po)
                        if((*Po)->Crash(&SB))
                        {
                            Sp=true;
                        }
                SB.Special=Sp;
                for(Tank<Handle<MotionStar> >::Ladle Po=TMOS.Begin();Po!=TMOS.End();++Po)
                    if(*Po)
                        if((*Po)->Crash(&SB))
                        {
                            XYF Tecccc=SB.SM.Target;
                            float Tem=Tecccc.Long();
                            Tem=Tem+(*Po)->MA*P->Time()/1000.0/SB.Range();
                            SB.SM.Target=Tecccc.Uint(Tem);
                        }
                for(Tank<Handle<BlackStar> >::Ladle Po=TBS.Begin();Po!=TBS.End();++Po)
                    if(*Po) (*Po)->Change((*Po)->Crash(&SB),&SB);
                for(Tank<Handle<JumpStar> >::Ladle Po=TJS.Begin();Po!=TJS.End();++Po)
                    if(*Po)
                        if((*Po)->Crash(&SB)!=0){Loose=true;return ;}
                for(Tank<Handle<RegularStar> >::Ladle Po=TRS.Begin();Po!=TRS.End();++Po)
                    if(*Po)
                        if((*Po)->Crash(&SB))
                        {
                            if(!SB.Special){Loose=true;return ;}
                        }else{
                            XYF T=(*Po)->Loc()-SB.Location;
                            SB.GetForce(CalculateForce((*Po)->Loc(),SB.Location,(*Po)->Range(),SB.Range())*T.Uint());
                        }
                for(Tank<Handle<NormalStar> >::Ladle Po=TNS.Begin();Po!=TNS.End();++Po)
                    if(*Po)
                        if((*Po)->Crash(&SB))
                        {
                            if(!SB.Special){Loose=true;return ;}
                        }
                for(Tank<Handle<ZhexueStar> >::Ladle Po=TZXS.Begin();Po!=TZXS.End();++Po)
                    if(*Po)
                        if((*Po)->Crash(&SB))
                        {
                            if(!SB.Special){Loose=true;return ;}
                        }else{
                            XYF T;
                            if(SB.Genarl)
                                T=SB.Location-(*Po)->Loc();
                            else
                                T=(*Po)->Loc()-SB.Location;
                            SB.GetForce(CalculateForce((*Po)->Loc(),SB.Location,(*Po)->Range(),SB.Range())*T.Uint());
                        }
                for(Tank<Handle<BaiheStar> >::Ladle Po=TBHS.Begin();Po!=TBHS.End();++Po)
                    if(*Po)
                        if((*Po)->Crash(&SB))
                        {
                            if(!SB.Special){Loose=true;return ;}
                        }else{
                            XYF T;
                            if(!SB.Genarl)
                                T=SB.Location-(*Po)->Loc();
                            else
                                T=(*Po)->Loc()-SB.Location;
                            SB.GetForce(CalculateForce((*Po)->Loc(),SB.Location,(*Po)->Range(),SB.Range())*T.Uint());
                        }
                for(Tank<Handle<AntiStar> >::Ladle Po=ATRS.Begin();Po!=ATRS.End();++Po)
                    if(*Po)
                    {
                        if((*Po)->Crash(&SB))
                        {
                            if(!SB.Special){Loose=true;return ;}
                        }else{
                            XYF T=SB.Loc()-(*Po)->Loc();
                            SB.GetForce(CalculateForce((*Po)->Loc(),SB.Location,(*Po)->Range(),SB.Range())*T.Uint());
                        }
                    }
            }
        }
        for(Tank<Handle<MoveStar> >::Ladle Po2=TMS.Begin();Po2!=TMS.End();++Po2)
            if(*Po2)
            {
                if((*Po2)->Crash(&SB)) {if(!SB.Special){Loose=true;return ;}}
                for(Tank<Handle<RegularStar> >::Ladle Po=TRS.Begin();Po!=TRS.End();++Po)
                    if(*Po)
                    {
                        XYF T=(*Po)->Loc()-(*Po2)->Location;
                        (*Po2)->GetForce(CalculateForce((*Po)->Loc(),(*Po2)->Location,(*Po)->Range(),(*Po2)->Range())*T.Uint());
                    }
                for(Tank<Handle<AntiStar> >::Ladle Po=ATRS.Begin();Po!=ATRS.End();++Po)
                    if(*Po)
                    {
                        XYF T=(*Po2)->Location-(*Po)->Loc();
                        (*Po2)->GetForce(CalculateForce((*Po)->Loc(),(*Po2)->Location,(*Po)->Range(),(*Po2)->Range())*T.Uint());
                    }
            }
        for(Tank<Handle<MoveStar> >::Ladle Po=TMS.Begin();Po!=TMS.End();++Po)
            if(*Po)  (*Po)->Assorial(P->Time());
        for(Tank<Handle<JumpStar> >::Ladle Po=TJS.Begin();Po!=TJS.End();++Po)
            if(*Po) (*Po)->Accessorial(P->Time());
    }
}

void Tem::Ana(Information* HI,POMain* P)
{
    if(HI->IsKeyDown())
    {
        if(!MouseControl)
        {
            if(HI->IsKey('w')||HI->IsKey(046)||HI->IsKey('W')) KeyUp=true;
            else if(HI->IsKey('s')||HI->IsKey(050)||HI->IsKey('S')) KeyDown=true;
            else if(HI->IsKey('a')||HI->IsKey(046)||HI->IsKey('A')) KeyLeft=true;
            else if(HI->IsKey('d')||HI->IsKey(050)||HI->IsKey('D')) KeyRight=true;
        }
        if(HI->IsKey(27)){Stage=-1;ReSet();}
    }else if(HI->IsKeyUp())
    {
        if(HI->IsKey('w')||HI->IsKey(046)||HI->IsKey('W')) KeyUp=false;
        else if(HI->IsKey('s')||HI->IsKey(050)||HI->IsKey('S')) KeyDown=false;
        else if(HI->IsKey('a')||HI->IsKey(046)||HI->IsKey('A')) KeyLeft=false;
        else if(HI->IsKey('d')||HI->IsKey(050)||HI->IsKey('D')) KeyRight=false;
        else if(HI->IsKey('q')) SB.ChangeGenal();
        else if(HI->IsKey('e')) if(SB.Special) SB.Location+=SB.SM.Target*3.0;
    }else if(HI->IsMouseButtonDown()&&HI->IsMouseButtonLeft())
    {
        if(!Run)
        {
            XYF Mouse;
            int TemW,TemH;
            HI->GetMouse(TemW,TemH);
            Mouse=P->GetFloatMouse(TemW,TemH);
            Mouse=View+Mouse;
            if(Mouse.Distance(SB.Loc())<SB.Range()){SelectPlayer=true;Point=Mouse;Target=Point;}
            MouseControl=true;
            KeyUp=false;KeyDown=false;KeyRight=false;KeyLeft=false;
        }
    }else if(HI->IsMouseButtonUp()&&HI->IsMouseButtonLeft())
    {
        MouseControl=false;
        if(Win||Loose)
        {
            if(Win)
            {
                TStage+=1;
                Win=false;
            }
            if(Loose)
            {
                Stage=-1;
                Loose=false;
            }
        }else if(!Run)
        {
            if(SelectPlayer)
            {
                XYF Tem=Target-Point;
                if(Tem.Long()>MAX_SPEED)
                    Tem=Tem.Uint(MAX_SPEED);
                SB.Launch(Tem);
                View=XYF(0.0,0.0);
                Run=true;
                SelectPlayer=false;
            }
        }else{
            if(SB.Special)
            {
                XYF Mouse;
                
                Mouse=P->GetFloatMouse(HI);
                SB.CreatSmall(Mouse+View);
            }
        }
    }else if(HI->IsMouseMotion())
    {
        if(MouseControl)
        {
            XYF Mouse;
            int TemW,TemH;
            HI->GetMouse(TemW,TemH);
            Mouse=P->GetFloatMouseMove(HI);
            if(SelectPlayer)
                Target=Target+Mouse;
            else
                View-=Mouse;
        }

    }
}
int main(int K,char** P)
{
    FileFactor FF;
    FF.Separate("setting.set");
    ScriptionBlock SB(FF.Begin(),FF.End());
    CommentPoint CP=SB.Begin();
    while(CP!=SB.End())
    {
        if(CP->Is("TITLE"))
            PO::SetTitle(CP->Scription());
        else if(CP->Is("WINDOW"))
        {
            FileFactorPoint OP=CP->ScriptionBegin;
            int W;
            int H;
            if(OP!=CP->ScriptionEnd)
            {
                std::stringstream K;
                K<<OP->Detail();
                K>>W;
                ++OP;
                if(OP!=CP->ScriptionEnd)
                {
                    std::stringstream P;
                    P<<OP->Detail();
                    P>>H;
                    PO::SetWindow(W,H);
                }
            }
        }else if(CP->Is("FONT"))
            SFont=CP->Scription();
        else if(CP->Is("SCENE"))
            SScene=CP->Scription();
        ++CP;
    }

    PO::Regedit(new Tem);
    PO::Init();

    PO::InitFinish();
    PO::SetDefultFont(SFont);
    glLineWidth(3.0);
    
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    PO::MainLoop();
}
