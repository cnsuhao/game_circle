#ifndef SCENE_H
#define SCENE_H
#include "../p.o/popicture.h"
#include "../p.o/handle.h"
#include "../p.o/scriptionbase.h"
#include "../p.o/dialog.h"
#include "scenedata.h"
#include <list>

class NormalScene:public SceneBase
{
    CommentPoint CP;
    bool UsingOption;
    int CL;
    std::vector<int> Block;
    std::vector<CommentPoint> CommentBlock;
    XYF ML;
    int TitleLine;
    bool UsingMouse;
    std::map<CommentPoint,Router> RouterMap;
    std::list<Router> Buffer;
    std::list<CommentPoint> ChooseOption;
    std::map<CommentPoint,CommentPoint> JumpPlace;
    bool StartConstruct;
public:
    void Clean();
    void SetStart(){CP=Begin();CommentBlock.clear();Block.clear();Buffer.clear();}
    bool Stop;
    bool ContinueT;
    void MouseChoosing(XYF L);
    void Init(){Stop=false;ContinueT=false;Option.MaxChar(30);UsingMouse=false;UsingOption=false;StartConstruct=false;}
    NormalScene(){Init();}
    NormalScene(SceneData *SD,FileFactorPoint B,FileFactorPoint E):SceneBase(B,E){ScriptionCheck(SD,Begin(),End());CommentCheck(SD);SetStart();Init();}
    bool Run(SceneData*);
    void Show();
    bool ReadComment(){return !Stop;}
    void Continue(){Stop=false;}
    void StartOptionConstruct(){StartConstruct=true;}
    bool OptionConstructing(){return StartConstruct;}
    void FinishOptionConstruct(){StartConstruct=false;UsingOption=true;CL=-1;}
    bool OptionReady(){return UsingOption;}
    void CleanOption(){Option.Clear();UsingOption=false;}
    void Click(){ContinueT=true;if(OptionReady()&&CL>0&&CL<=CommentBlock.size()){CP=*CommentBlock.begin()+CL;Router Tem=RouterMap[CP];Buffer.push_back(Tem);}}
    void Pause(){Stop=true;}
    void MeetEnd();
    void AddOption(CommentPoint K,std::string S){CommentBlock.push_back(K);int P=Option.Line();Option.AddLine(S);Block.push_back(Option.Line()-P);}
    CommentPoint RunComment(SceneData*,CommentPoint);
    void OptionAddTitle(std::string K){StartOptionConstruct();Option.Clear();Option.AddLine(K);TitleLine=Option.Line();}
    bool RunOperator(SceneData*,CommentPoint,std::string &Arr);
    void ScriptionCheck(SceneData*,CommentPoint S,CommentPoint E);
    void CommentCheck(SceneData *SD,CommentPoint U);
    void CommentCheck(SceneData *SD){CommentPoint K=Begin();while(K!=End()){CommentCheck(SD,K);++K;}}
    virtual void Control(Handle<Information> I);
    void CheckRouter(std::fstream &);
};

void NormalScene::CheckRouter(std::fstream & K)
{
    for(std::map<CommentPoint,Router>::iterator Po=RouterMap.begin();Po!=RouterMap.end();++Po)
    {
        Po->second.Check(K);
    }
}

void NormalScene::CommentCheck(SceneData* SD,CommentPoint U)
{
    OperatorPoint P;
    if(U->Is("O")||U->Is("S")||U->Is("D")||U->Is("CS")||U->Is("C")||U->Is("SENT"))
    {
        P=U->Begin();
        while(P!=U->End())
        {
            if(!P->Is("IF")&&!P->Is("C")&&!P->Is("S")&&!P->Is("SR")&&!P->Is("A")&&!P->Is("PA"))
            {
                ScriptionPacket::Push("Comment <"+ (*U->Comment).Data + "> Meet Unkonw Option <"+(*P->Operator).Data+">. ",P->Line());
                break;
            }
            ++P;
        }
    }else if(U->Is("IF"))
    {
        P=U->Begin();
        while(P!=U->End())
        {
            if(!P->Is("C")&&!P->Is("S")&&!P->Is("SR"))
            {
                ScriptionPacket::Push("Comment <"+ (*U->Comment).Data + "> Meet Unkonw Option <"+(*P->Operator).Data+">. ",P->Line());
                break;
            }
            ++P;
        }
    }else if(U->Is("END")||U->Is("SJ")||U->Is("JL")||U->Is("CSP")||U->Is("CLP")||U->Is("CRP")||U->Is("J"))
    {
        if(U->Begin()!=U->End())
        {
            ScriptionPacket::Push("Comment <"+(*U->Comment).Data+"> Can Not Use Any Operator <"+(*P->Operator).Data+">. ",P->Line());
        }
    }else if(U->Is("RP")||U->Is("LP")||U->Is("SP")||U->Is("B"))
    {}else{
        ScriptionPacket::Push("Unknow Comment <"+(*(U->Comment)).Data+">.",U->Line());
    }
}

bool NormalScene::RunOperator(SceneData *SD, CommentPoint CP, std::string &Arr)
{
    OperatorPoint K=CP->Begin();
    bool Avalible=true;
    std::string Temstr;
    while(K!=CP->End())
    {
        Temstr.clear();
        Temstr=GetParameter(SD,K->Begin(),K->End());
        if(K->Is("S"))
            SD->SentMessage(Temstr);
        else if(K->Is("SR"))
            Arr=SD->RespondMessage(Temstr);
        else if(K->Is("A"))
            Arr+=Temstr;
        else if(K->Is("PA"))
            Arr=Temstr+Arr;
        else if(K->Is("IF"))
        {
            if(Temstr==Scr_True)
                Avalible=true;
            else
                Avalible=false;
        }
        ++K;
    }
    return Avalible;
}

void NormalScene::ScriptionCheck(SceneData *SD,CommentPoint S,CommentPoint E)
{
    CommentPoint Go=S;
    while(Go!=E)
    {
        if(Go->Is("SJ"))
        {
            CommentPoint Tem=S;
            while(Tem!=E)
            {
                if(Tem->Is("JL"))
                {
                    if(Tem->Scription()==Go->Scription())
                    {
                        if(JumpPlace.count(Go)==0)
                            JumpPlace[Go]=Tem;
                        else{
                            ScriptionPacket::Push("Jump Comment "+Go->Scription()+" Meet Two Different Locations . ",Go->Line());
                            break;
                        }
                    }
                }
                ++Tem;
            }
        }else if(Go->Is("CS"))
        {
            int Size=-1;
            CommentPoint Tem=Go;
            CommentPoint Mid=Go;
            while(Tem!=E)
            {
                if(Tem->Is("CS")||Tem->Is("IF"))
                {
                    Size+=1;
                }else if(Tem->Is("END"))
                {
                    if(Size==0)
                    {
                        if(Mid==Go)
                            Mid=Tem;
                        Router TemR(Go,Mid,Tem);
                        RouterMap[Go]=TemR;
                        Size=-10;
                        break;
                    }else{
                        Size-=1;
                    }
                }else if(Tem->Is("O"))
                {
                    if(Mid==Go)
                        Mid=Tem;
                }
                ++Tem;
            }
            if(Size!=-10)
                ScriptionPacket::Push("Comment \"CS\" Need An \"END\" . ",Go->Line());
            else{
                CommentPoint Tem2=Go;
                CommentPoint Tem3=Go;
                int Size=0;
                while(Tem2!=Tem)
                {
                    if(Tem2->Is("O"))
                    {
                        if(Tem3==Go)
                            Tem3=Tem2;
                        else
                        {
                            Router TemR(Tem3,Tem2,Tem);
                            RouterMap[Tem3]=TemR;
                            Tem3=Tem2;
                        }
                    }
                    ++Tem2;
                }
                if(Go!=Tem)
                {
                    Router TemR(Tem3,Tem);
                    RouterMap[Tem3]=TemR;
                }
            }
        }else if(Go->Is("IF"))
        {
            CommentPoint K=Go;
            CommentPoint M=Go;
            int Size=-1;
            while(K!=E)
            {
                if(K->Is("IF")||K->Is("CS"))
                {
                    Size+=1;
                }else if(K->Is("ELSE"))
                {
                    if(Size==0)
                        M=K;
                }else if(K->Is("END"))
                {
                    if(Size==0)
                    {
                        if(M==Go)
                            M=K;
                        Router Yc(Go,M,K);
                        RouterMap[Go]=(Yc);
                        Size=-10;
                        break;
                    }else
                        Size-=1;
                }
                ++K;
            }
            if(Size!=-10)
            {
                ScriptionPacket::Push("Comment \"IF\" Need An \"END\"",Go->Line());
            }
        }
        ++Go;
    }
}

void NormalScene::Control(Handle<Information> I)
{
    if(I)
    {
        if(I->IsKeyUp())
        {
            UsingMouse=false;
            if(I->IsKey(13))
            {
                Click();
            }else if(I->IsKey('w')&&OptionReady())
            {
                CL-=1;
                if(CL<=0)
                    CL=Block.size();
            }else if(I->IsKey('s')&&OptionReady())
            {
                if(CL==-1)
                    CL+=1;
                CL+=1;
                if(CL>Block.size())
                    CL=1;
            }
        }else if(I->IsMouseMotion())
        {
            I->GetMouse(ML.X,ML.Y);
            if(OptionReady())
            {
                UsingMouse=true;
                MouseChoosing(ML);
            }
        }else if(I->IsMouseButtonUp()&&I->IsMouseButtonLeft())
        {
            Click();
        }
    }
}

void NormalScene::MouseChoosing(XYF L)
{
    if(OptionReady())
    {
        ML=L;
        CL=-1;
        float Each=1.0/Option.MaxChar()/0.4;
        float Y=Option.Line()*Each/2.0;
        int T=TitleLine;
        if(ML.X>=-0.5&&ML.X<=0.5)
        {
            for(int i=0;i<Block.size();++i)
            {
                int TL=Block[i];
                if(ML.Y<Y-T*Each&&ML.Y>Y-(T+TL)*Each)
                {
                    CL=i+1;
                    break;
                }
                T+=TL;
            }
        }
    }
}

bool NormalScene::Run(SceneData *SD)
{
    if(ReadComment())
    {
        while(CP!=End())
        {
            if(!Buffer.empty())
            {
                std::list<Router>::reverse_iterator Po=Buffer.rbegin();
                if(Po->IsEnd(CP))
                {
                    CP=Po->Next();
                    Buffer.pop_back();
                }
            }
            CP=RunComment(SD,CP);
            if(!ReadComment())
                break;
            if(CP==End())
            {
                return true;
            }
        }
    }else if(ContinueT)
    {
        if(OptionReady())
        {
            CP=CommentBlock[CL-1];
            Buffer.push_back(RouterMap[CP]);
            CleanOption();
        }else{
            Dia.Clear();
        }
        Continue();
    }
    Show();
    ContinueT=false;
    return false;
}

void NormalScene::Show()
{
    if(Right)
        Right.Display(XYF(-1.0,0.8),XYF(0.8,0.0),XYF(0.0,-1.8));
    if(Left)
        Left.Display(XYF(0.2,0.8),XYF(0.8,0.0),XYF(0.0,-1.8));
    if(Dia)
    {
        glColor3f(218/255.0,165/255.0,32/255.0);
        glBegin(GL_QUADS);
        glVertex(-1.0,-0.4);
        glVertex(-1.0,-1.0);
        glVertex(1.0,-1.0);
        glVertex(1.0,-0.4);
        glEnd();
        if(Small)
        {
            //Small->Show(-0.9,-0.5,-0.5,-0.9);
            glColor3f(0.0,0.0,0.0);
            glBegin(GL_LINE_LOOP);
            glVertex(-0.9,-0.5);
            glVertex(-0.9,-0.9);
            glVertex(-0.5,-0.9);
            glVertex(-0.5,-0.5);
            glEnd();
        }
        Dia.Display(XYF(-0.4,-0.5),XYF(0.9,-0.9),1.0,1.0,1.0);
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex(-0.4,-0.5);
        glVertex(-0.4,-0.9);
        glVertex(0.9,-0.9);
        glVertex(0.9,-0.5);
        glEnd();
    }
    if(OptionReady())
    {
        float Each=1.0/Option.MaxChar()/0.4;
        glColor3f(218/255.0,165/255.0,32/255.0);
        float Y=Option.Line()*Each/2.0;
        glBegin(GL_QUADS);
        glVertex(-0.51,Y);
        glVertex(-0.51,-Y);
        glVertex(0.51,-Y);
        glVertex(0.51,Y);
        glEnd();
        int T=TitleLine;
        for(int i=0;i<Block.size();++i)
        {
            int TL=Block[i];
            if(CL==i+1)
            {
                glColor3f(1.0,0.0,0.0);
                glBegin(GL_QUADS);
                glVertex(-0.53,Y-T*Each);
                glVertex(-0.53,Y-(T+TL)*Each);
                glVertex(0.53,Y-(T+TL)*Each);
                glVertex(0.53,Y-(T)*Each);
                glEnd();
                break;
            }
            T+=TL;
        }
        Option.Display(XYF(-0.5,Y),XYF(0.5,-Y),1.0,1.0,1.0);
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex(-0.5,Y);
        glVertex(-0.5,-Y);
        glVertex(0.5,-Y);
        glVertex(0.5,Y);
        glEnd();
    }
}

CommentPoint NormalScene::RunComment(SceneData *SD,CommentPoint U)
{
    std::string Tem;
    FileFactorPoint OP=U->ScriptionBegin;
    FileFactorPoint OP2=U->ScriptionEnd;
    Tem=GetParameter(SD,OP,OP2);
    if(RunOperator(SD,U,Tem))
    {
        if(U->Is("IF"))
        {
            if(Tem==Scr_True)
            {
                Buffer.push_back(RouterMap[U]);
            }else{
                Router Tem=RouterMap[U];
                Tem.Set(Tem.End,Tem.Next());
                Buffer.push_back(Tem);
                U=Tem.End;
            }
        }else if(U->Is("CS"))
        {
            OptionAddTitle(Tem);
        }else if(U->Is("RP"))
            Right=SD->SearchResource(Tem+"Pic");
        else if(U->Is("LP"))
            Left=SD->SearchResource(Tem+"Pic");
        else if(U->Is("SP"))
            Small=SD->SearchResource(Tem+"SmaPic");
        else if(U->Is("CRP"))
            Right.Unused();
        else if(U->Is("CLP"))
            Left.Unused();
        else if(U->Is("CSP"))
            Small.Unused();
        else if(U->Is("SJ"))
        {
            U=JumpPlace[U];
            while(!Buffer.empty())
            {
                std::list<Router>::reverse_iterator Po=Buffer.rbegin();
                if(U<Po->Start||U>Po->End)
                {
                    Buffer.pop_back();
                }else
                    break;
            }
        }else if(U->Is("J"))
            SD->CallNextScene(Tem);
        else if(U->Is("S"))
        {
            Pause();
        }else if(U->Is("D"))
        {
            Dia.AddLine(Tem);
        }else if(U->Is("O"))
        {
            if(OptionConstructing())
            {
                AddOption(U,Tem);
                U=RouterMap[U].End;
                return U;
            }
        }else if(U->Is("END"))
        {
            if(OptionConstructing())
            {
                FinishOptionConstruct();
                Pause();
            }
        }else if(U->Is("SENT"))
        {
            SD->SentMessage(Tem);
        }
    }else if(U->Is("O"))
    {
        if(OptionConstructing())
        {
            U=RouterMap[U].End;
            return U;
        }
    }
    ++U;
    return U;
}

class Scene:public ScriptionData,public SceneData
{
    bool Using;
public:
    std::map<std::string,Handle<SceneBase> >::iterator Point;
    std::map<std::string,Handle<SceneBase> > AllScene;
    void Pause(){Using=false;}
    void StartWith(std::string);
    bool Runing(){return Using;}
    void Load(std::string K);
    void SetStart(){Point=AllScene.begin();}
    bool Run();
    void Control(Handle<Information> I){if(Using){Point->second->Control(I);}}
    Scene():Using(true){SetStart();}
};
void Scene::StartWith(std::string K)
{
    if(!Runing())
    {
        if(AllScene.count(K)==0)
        {
            ScriptionPacket::Push("Unknow Scene Name <"+K+">",-1);
        }else{
            Point=AllScene.find(K);
            Point->second->SetStart();
            Using=true;
        }
    }
}

void Scene::Load(std::string A)
{
    AllScene.clear();
    std::string Name("\0");
    std::string Style("NS");
    ScriptionData::Load(A);
    FileFactorPoint S=Begin();
    FileFactorPoint Po=Begin();
    if(Po!=End())
    {
        while(Po!=End())
        {
            if(*Po=="#")
            {
                if(End()-Po<3)
                {
                    ScriptionPacket::Push("Wrong End of Scene",Po->Line());
                }else{
                    if(Style=="NS")
                        AllScene[Name]=new NormalScene(this,S,Po);
                    Style=*(Po+1);
                    Name=*(Po+2);
                    S=Po+3;
                    Po=S-1;
                }
            }
            ++Po;
        }
        AllScene[Name]=new NormalScene(this,S,End());
    }
    SetStart();
}

bool Scene::Run()
{
    if(Runing())
    {
        if(NeedJump())
        {
            Point=AllScene.find(TargetScene());
            Point->second->SetStart();
        }
        if(Point->second->Run(this))
        {
            Pause();
        }
        return false;
    }
    return true;
}

#endif // SCENE_H
