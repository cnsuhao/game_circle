#ifndef SCENE_H
#define SCENE_H
#include "scenefile.h"
#include "sceneresource.h"
#include "../p.o/po.h"
#include "../p.o/popicture.h"
#include "../p.o/dialog.h"
#include "../p.o/publicvalue.h"
#include "option.h"

float SceneTalkL[8]={-1.0,-0.4,-1.0,-1.0,1.0,-1.0,1.0,-0.4};
float SceneTalkC[16]={0.0,0.0,0.0,0.6,0.0,0.0,0.0,0.6,0.0,0.0,0.0,0.6,0.0,0.0,0.0,0.6};

class Scene: public HandleSeed
{
    public:
    PublicLock PV;
    POPicture RP;
    POPicture SP;
    POPicture LP;
    POPicture Black;
    Dialog Talk;
    Option OD;
    bool UsingOption;
    SceneFile SF;
    SceneResource SR;
    bool Pause;
    bool Finish;
    bool Continue;
    CommentPoint CP;
    std::list<std::string> MessageList;
    Handle<BlockControl> HSB;
    int ComCal;
    void LoadScene(std::string,POMain*);
    void RunOperator(CommentPoint U,std::string &);
    void Click(){PV.Lock();Continue=true;PV.UnLock();}
    void Run(POMain* P);
    void Show(POMain*);
    bool IsFinish(){return Finish;}
    Scene():Pause(false),Finish(true),Continue(false),ComCal(0),UsingOption(false){}
    void CleanAll(){LP.Unused();RP.Unused();SP.Unused();Black.Unused();}
    void ChooseMouse(XYF Tem){OD.ChooseMouse(Tem);}
    void KeyUp(){OD.KeyUp();}
    void KeyDown(){OD.KeyDown();}
    bool Message(){return !MessageList.empty();}
    std::string GetMessage(){std::string K=*MessageList.begin();MessageList.pop_front();return K;}
};

void Scene::LoadScene(std::string A,POMain* P)
{
    SceneResource SRT;
    Finish=false;
    SF.LoadFile(A);
    CommentPoint Po=SF.InitComment.Begin();
    while(!SF.InitComment.IsEnd(Po))
    {
        if(Po->Is("Resource"))
            SRT.LoadScription(Po->Scription());
        else if(Po->Is("Start"))
        {
            HSB=SF.GetBlock(Po->Scription());
            if(!(HSB))
            {
                std::map<std::string,Handle<BlockControl> >::iterator Po2=SF.BlockList.begin();
                if(Po2!=SF.BlockList.end())
                {
                    HSB=Po2->second;
                    CP=HSB->Begin();
                }else
                    Finish=true;
            }else
                CP=HSB->Begin();
        }
        ++Po;
    }
    SRT.LoadResource(P);
    SR.RelesePicture(P);
    SR=SRT;
}

void Scene::RunOperator(CommentPoint U, std::string& S)
{
    for(OperatorPoint OP=U->Begin();OP!=U->End();++OP)
    {
        S+=OP->Detail();
    }
}

void Scene::Run(POMain* P)
{
    if(!Finish)
    {
        PV.Lock();
        if(Continue&&Pause)
        {
            if(OD.IsUsing())
            {
                if(OD.GetResource(CP))
                {
                    Pause=false;
                    Talk.Clear();
                }
            }else{
                Pause=false;
                Talk.Clear();
            }
        }
        Continue=false;
        PV.UnLock();
        if((!Pause))
        {
            while(!HSB->IsEnd(CP))
            {
                std::string Operator;
                std::string Scription=CP->Scription();
                std::string Style=CP->Detail();
                RunOperator(CP,Operator);
                if(CP->Is("B"))
                    Black=SR.GetResource(CP->Scription()+"_B_"+Operator);
                else if(CP->Is("RP"))
                    RP=SR.GetResource(CP->Scription()+"_P_"+Operator);
                else if(CP->Is("SP"))
                    SP=SR.GetResource(CP->Scription()+"_SP_"+Operator);
                else if(CP->Is("CRP"))
                    RP.Unused();
                else if(CP->Is("LP"))
                    LP=SR.GetResource(CP->Scription()+"_P_"+Operator);
                else if(CP->Is("CLP"))
                    LP.Unused();
                else if(CP->Is("CSP"))
                    SP.Unused();
                else if(CP->Is("CB"))
                    Black.Unused();
                else if(CP->Is("CA"))
                    CleanAll();
                else if(CP->Is("S"))
                {
                    ++CP;
                    Pause=true;
                    break;
                }else if(CP->Is("D"))
                    Talk.AddLine(Scription);
                else if(CP->Is("DS"))
                {
                    Talk.AddLine(Scription);
                    ++CP;
                    Pause=true;
                    break;
                }else if(CP->Is("J"))
                    CP->Jump(CP);
                else if(CP->Is("OT"))
                {
                    OD.AddTitle(CP);
                    CommentPoint Tem;
                    CP->Jump(Tem);
                    while(!HSB->IsEnd(Tem))
                    {
                        if(Tem->Is("O"))
                            OD.AddOption(Tem);
                        else if(Tem->Is("END"))
                        {
                            OD.Finish();
                            Pause=true;
                            break;
                        }
                        Tem->Jump(Tem);
                    }
                }else if(CP->Is("O"))
                {
                    CP->Jump(CP);
                    continue;
                }else if(CP->Is("JS"))
                {
                    HSB=SF.GetBlock(CP->Scription());
                    if(HSB)
                    {
                        CP=HSB->Begin();
                        break;
                    }else{
                        GetError("Can not Find Scene<"+CP->Scription()+">.",CP->Line());
                        Finish=false;
                        break;
                    }
                }else if(CP->Is("JF"))
                {
                    LoadScene(CP->Scription(),P);
                    CleanAll();
                    break;
                }else if(CP->Is("SENT"))
                    MessageList.push_back(CP->Scription());
                if(Pause)
                    break;
                ++CP;
            }
            if(!Pause&&HSB->IsEnd(CP))
            {
                Finish=true;
                CleanAll();
            }
        }
        Show(P);
    }
}

void Scene::Show(POMain* P)
{
    if(!Finish)
    {
        if(Black)
            Black.Display(XYF(-1.0,1.0),XYF(2.0,0.0),XYF(0.0,-2.0));
        if(RP)
            RP.Display(XYF(0.2,0.8),XYF(0.8,0.0),XYF(0.0,-1.8));
        if(LP)
            LP.Display(XYF(-1.0,0.8),XYF(0.8,0.0),XYF(0.0,-1.8));
        if(Talk)
        {
            glEnableClientState(GL_COLOR_ARRAY);
            glEnableClientState(GL_VERTEX_ARRAY);
            unsigned int Order[4]={0,1,2,3};
            glVertexPointer(2,GL_FLOAT,0,SceneTalkL);
            glColorPointer(4,GL_FLOAT,0,SceneTalkC);
            bool Tem=glIsEnabled(GL_BLEND);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glDrawElements(GL_QUADS,4, GL_UNSIGNED_INT,Order);
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
            if(!Tem)
                glDisable(GL_BLEND);
            Talk.Init(P);
            if(SP)
            {
                SP.Display(XYF(-0.95,-0.5),XYF(0.4,0.0),XYF(0.0,-0.4));
                Talk.Display(XYF(-0.4,-0.5),XYF(0.8,-0.9));
            }else{
                Talk.Display(XYF(-0.6,-0.5),XYF(0.6,-0.9));
            }
        }
        if(OD)
            OD.Display(P);
    }
}

#endif // SCENE_H
