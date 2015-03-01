#ifndef OPTION_H
#define OPTION_H
#include "../p.o/dialog.h"
#include "../p.o/publicvalue.h"
#include "../p.o/scription/scriptioncomment.h"
float OptionAspectL[8]={-0.6,0.0,-0.6,0.0,0.6,0.0,0.6,0.0};
float OptionChooseC1[16]={0.0,0.0,0.0,0.6,0.0,0.0,0.0,0.6,0.0,0.0,0.0,0.6,0.0,0.0,0.0,0.6};
float OptionChooseC2[16]={1.0,0.0,1.0,1.0,1.0,0.0,1.0,1.0,1.0,0.0,1.0,1.0,1.0,0.0,1.0,1.0};
class Option
{
    PublicLock PL;
    Dialog DOption;
    CommentPoint Title;
    std::vector<XYF> OptionLocation;
    std::vector<CommentPoint> OptionList;
    std::vector<int> LineRemember;
    int Choose;
    float Start;
    bool Using;
    float L[8];
    float C[16];
    float C2[16];
public:
    void AddTitle(CommentPoint O);
    void AddOption(CommentPoint P);
    void Finish();
    operator bool(){return DOption;}
    void Clear(){DOption.Clear();OptionLocation.clear();LineRemember.clear();OptionList.clear();Using=false;}
    bool GetResource(CommentPoint& CP);
    void Display(POMain*);
    void ChooseMouse(XYF Tem);
    void KeyUp();
    void KeyDown();
    bool IsUsing(){return Using;}
    Option():Using(0),Choose(0){}
};
bool Option::GetResource(CommentPoint& CP)
{
    PL.Lock();
    if(!OptionList.empty())
    {
        if(Choose>0&&Choose<=OptionList.size())
        {

            CP=OptionList[Choose-1];
            //CP->CheckDetail(Error,"Run");
            ++CP;
            Clear();
            //CP->CheckDetail(Error,"Run");
            PL.UnLock();
            return true;
        }else{
            PL.UnLock();
            return false;
        }
    }else{
        if(Using)
        {
            CP->Jump(CP);
            Clear();
        }
    }
    PL.UnLock();
    return true;
}
void Option::KeyDown()
{
    PL.Lock();
    if(!OptionLocation.empty())
    {
                    ++Choose;
        if(Choose>OptionLocation.size())
            Choose=1;
    }
    PL.UnLock();
}


void Option::KeyUp()
{
    PL.Lock();
    if(!OptionLocation.empty())
    {
        if(Choose<=1)
        {
            Choose=OptionLocation.size();
        }else{
            --Choose;
        }
    }
    PL.UnLock();
}


void Option::ChooseMouse(XYF Tem)
{
    if(Tem.X>=-0.6&&Tem.X<=0.6)
    {
        PL.Lock();
        Choose=0;
        for(int i=0;i<OptionLocation.size();++i)
        {
            if(Tem.Y>=OptionLocation[i].Y&&Tem.Y<OptionLocation[i].X)
            {
                Choose=i+1;
                break;
            }
        }
        PL.UnLock();
    }
}


void Option::AddTitle(CommentPoint K)
{
    PL.Lock();
    Title=K;
    DOption.AddLine(K->Scription());
    if(!LineRemember.empty())
        LineRemember[0]=DOption.Line();
    else
        LineRemember.push_back(DOption.Line());
    PL.UnLock();
}

void Option::AddOption(CommentPoint P)
{
    PL.Lock();
    OptionList.push_back(P);
    PL.UnLock();
}

void Option::Finish()
{
    PL.Lock();
    for(int i=0;i<OptionList.size();++i)
    {
        DOption.AddLine(OptionList[i]->Scription());
        LineRemember.push_back(DOption.Line());
    }
    if(LineRemember.size()>=2)
    {
        float Each=3.0/DOption.MaxChar();
        Start=DOption.Line()*Each/2.0+0.2;
        float Last=-LineRemember[0]*Each+Start;
        for(int i=1;i<LineRemember.size();++i)
        {
            float Temf=-LineRemember[i]*Each+Start;
            XYF Tem(Last,Temf);
            Last=Temf;
            OptionLocation.push_back(Tem);
        }
    }
    if(OptionList.size()>=1)
        Choose=1;
    else
        Choose=0;
    Using=true;
    PL.UnLock();
}

void Option::Display(POMain* P)
{
    if(DOption)
    {
        bool Tem=glIsEnabled(GL_BLEND);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        OptionAspectL[1]=Start;OptionAspectL[7]=Start;OptionAspectL[3]=0.4-Start;OptionAspectL[5]=0.4-Start;
        unsigned int Order[4]={0,1,2,3};
        glVertexPointer(2,GL_FLOAT,0,OptionAspectL);
        glColorPointer(4,GL_FLOAT,0,OptionChooseC1);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawElements(GL_QUADS,4, GL_UNSIGNED_INT,Order);
        if(Choose>0&&Choose<=OptionList.size())
        {
            OptionAspectL[1]=OptionLocation[Choose-1].X;OptionAspectL[7]=OptionLocation[Choose-1].X;OptionAspectL[3]=OptionLocation[Choose-1].Y;OptionAspectL[5]=OptionLocation[Choose-1].Y;
            glColorPointer(4,GL_FLOAT,0,OptionChooseC2);
            glDrawElements(GL_QUADS,4, GL_UNSIGNED_INT,Order);
        }
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        if(!Tem)
            glDisable(GL_BLEND);
        DOption.Init(P);
        DOption.Display(XYF(-0.6,Start),XYF(0.6,0.4-Start));
    }
}

#endif // OPTION_H
