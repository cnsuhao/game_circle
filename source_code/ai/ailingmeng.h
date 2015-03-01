#ifndef DIY_AI_LINGMENG_H
#define DIY_AI_LINGMENG_H
#include "ai.h"
#include "../personage/bolilingmeng.h"
class AILingMeng:public AI
{
    bool Jumping;
    Handle<LingMeng> LM;
    public:
        void Accessorial(Personage*,Realm*,long);
        AILingMeng(Handle<Personage> P,Handle<LingMeng> lm):AI(P),LM(lm),Jumping(false){}
};
void AILingMeng::Accessorial(Personage *P, Realm *R, long T)
{
    if(Target)
    {
        XYZF Tc=Target->Location-P->Location;
        XYZF KK=Tc.Uint();
        if(KK*P->V.Front()<=0.99999)
        {
            P->Shoot=false;
            if(KK*P->V.Left()<0)
            {
                P->V.TakeControl(Vie_Rig);
            }else{
                P->V.TakeControl(Vie_Lef);
            }
            if(KK*P->V.Up()<0)
            {
                P->V.TakeControl(Vie_Dow);
            }else{
                P->V.TakeControl(Vie_Up);
            }
        }else{
            P->Shoot=true;
        }
        if(Jumping)
        {
            if(R->CanFly(P->Location.Y))
            {
                P->A.StartJump();
                Jumping=false;
            }
        }else
        if(P->A.AM==Avi_Wal)
        {
            P->A.StartJump();
            Jumping=true;
        }else{
            if(Target->Location.Distance(P->Location)<20.0)
            {
                P->A.Back();
            }else if(Target->Location.Distance(P->Location)>40.0){
                P->A.Front();
            }else{
                P->A.StopFAD();
            }
        }
    }
}

#endif // AI_LINGMENG_H
