#ifndef DIY_TAIJISPELL_H
#define DIY_TAIJISPELL_H
#include "specialshoot.h"
#include "../personage/bolilingmeng.h"
#include "../bullet/taiji.h"
#include "../bullet/bigtaiji.h"
class TaiJiSpecial:public SpecialShoot
{
    int Number;
    public:
        void Lanch(Personage *P, Realm *RB,bool& B);
        void Analyze(Personage*,Realm*,long,bool&);
        //void Show(Personage*,Realm*,long);
        TaiJiSpecial():SpecialShoot(1000){}
};
void TaiJiSpecial::Lanch(Personage *P, Realm *RB,bool& B)
{
    if(SS==SS_READY)
    {
        if(P->Name==PRESONAGE_LINGMENG)
        {
            LingMeng* LM=dynamic_cast<LingMeng*>(P);
            if(LM!=NULL)
            {
                Number=LM->NumberOfBall;
                Number+=3;
                LM->TaiJi=true;//先播放一段动画
            }
        }
        SpecialShoot::Lanch(P,RB,B);
    }
}
void TaiJiSpecial::Analyze(Personage  *P, Realm *RB, long T,bool& B)
{
    Base(P,RB,T,B);
    if(SS==SS_USING)
    {
        if(P->Name==PRESONAGE_LINGMENG)
        {
            LingMeng* LM=dynamic_cast<LingMeng*>(P);
            if(LM!=NULL)
            {
                if(!LM->TaiJi)//播放完毕，创建
                {
                    for(int i=0;i<Number;++i)
                    {
                        Coordinate Tc;
                        if(Number==6)
                        {
                            Tc.Up=LM->Up;
                            Tc.Front=P->Front;
                            Tc.Location=P->Location+P->Front;
                            Tc.Left=(Tc.Up&Tc.Front).Uint();
                            Handle<Bullet> Tr=new BigTaiJi(LM,Tc,P->L.Target);
                            //Tr->Live=100000;
                            Handle<Object> Tv=Tr.Data;
                            RB->GetObject(Tv);
                            break;
                        }else{
                            if(LM->A.AM==AVI_WALK)
                                Tc.Up=RB->HorizontalU;
                            else if(LM->A.AM==AVI_FLY)
                                Tc.Up=LM->Up;
                            XYZF Ter(sin(i*(6.2831/Number)),0.0,cos(i*(6.2831/Number)));
                            Ter=Ter.Uint();
                            Tc.Location = LM->Location+Ter;
                            Tc.Front=Ter;
                            Tc.Left=(Tc.Up&Tc.Front).Uint();
                            Handle<Bullet> Tr=new TaiJi(LM,Tc,P->L.Target);
                            Handle<Object> Tv=Tr.Data;
                            RB->GetObject(Tv);
                        }
                    }
                    Finish(P,RB,B);
                }
            }
        }
    }
}

#endif // TAIJISPELL_H
