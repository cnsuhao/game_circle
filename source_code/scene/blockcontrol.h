#ifndef BLOCKCONTROL_H
#define BLOCKCONTROL_H
#include <map>
#include "../p.o/scription/scriptionblock.h"
class BlockControl:public HandleSeed
{
    ScriptionBlock SB;
    void CommentAnalyze();
public:
    bool IsEnd(CommentPoint T){return T==SB.End();}
    BlockControl(FileFactorPoint S,FileFactorPoint E):SB(S,E){CommentAnalyze();}
    BlockControl(CommentPoint CPS,CommentPoint CPE):SB(CPS,CPE){CommentAnalyze();}
    BlockControl(CommentReversePoint CPS,CommentReversePoint CPE):SB(CPS,CPE){CommentAnalyze();}
    BlockControl(){}
    CommentPoint Begin(){return SB.Begin();}
    CommentPoint End(){return SB.End();}
    void CheckDetail(std::fstream& T);
    void CreatComment(FileFactorPoint Tem,FileFactorPoint Tem2){SB.CreatComment(Tem,Tem2);CommentAnalyze();}
    void CreatComment(CommentPoint Tem,CommentPoint Tem2){SB.CreatComment(Tem,Tem2);CommentAnalyze();}
    void CreatComment(CommentReversePoint Tem,CommentReversePoint Tem2){SB.CreatComment(Tem,Tem2);CommentAnalyze();}
    bool OrderNext(CommentPoint &CP, int &T);
    void Clear(){SB.Clear();}
};


void BlockControl::CheckDetail(std::fstream& T)
{
    SB.CheckDetail(T);
}

void BlockControl::CommentAnalyze()
{
    CommentPoint S=SB.Begin();
    while(S!=SB.End())
    {
        if(S->Is("J"))
        {
            std::string Scr=S->Scription();
            CommentPoint J=SB.Begin();
            while(J!=SB.End())
            {
                if(J->Is("JL"))
                    if(J->Scription()==Scr)
                    {
                        S->SetJump(J);
                        break;
                    }
                ++J;
            }
            if(J==SB.End())
                GetError("Comment J Can not Find The Target.",S->Line());
        }else if(S->Is("OT"))
        {
            int Size=0;
            CommentPoint P=S;
            while(P!=SB.End())
            {
                if(P->Is("OT")||P->Is("IF"))
                    Size+=1;
                else if(P->Is("END"))
                {
                    Size-=1;
                    if(Size==0)
                    {
                        S->SetJump(P);
                        break;
                    }
                }else if(P->Is("O"))
                {
                    bool FouceJump=false;
                    if(Size==1)
                    {
                        S->SetJump(P);
                        int Size2=1;
                        CommentPoint P2=P;
                        ++P2;

                        while(P2!=SB.End())
                        {
                            if(P2->Is("OT")||P2->Is("IF"))
                                Size2+=1;
                            else if(P2->Is("END"))
                            {
                                Size2-=1;
                                if(Size2==0)
                                {
                                    P->SetJump(P2);
                                    FouceJump=true;
                                    break;
                                }
                            }else if(P2->Is("O"))
                            {
                                if(Size2==1)
                                {
                                    P->SetJump(P2);
                                    P=P2;
                                }
                            }
                            ++P2;
                        }
                    }
                    if(FouceJump)
                        break;
                }
                ++P;
            }
            if(P==SB.End())
                GetError("Comment OT Can not FInd End Or O.",S->Line());
        }
        ++S;
    }
}

#endif // BLOCKCONTROL_H
