#ifndef DIY_PERSONAGE_H
#define DIY_PERSONAGE_H
#include <vector>
//#include "CrashLive.h"
//#include "Brain.h"
//#include "Storehouse.h"
#include <math.h>
//#include "Pretarget.h"
#include "../base/drawaquare.h"
#include "../base/ladar.h"
#include "../p.o/information.h"
#include "../realm/realm.h"
#include "../base/aviate.h"

#include "../ai/ai.h"
//#include "../spell/spellcontrol.h"
//#include "../specialshoot/specialcontrol.h"
#include "../spell/spellcontrol.h"
//#include "../bullet/bullet.h"
enum PersonageName
{
    PRESONAGE_LINGMENG
};
class Personage:public Object
{
    bool ViewMode;//如果为true，则为第一人称设计形式，如果为false，则为第三人称形式
    bool NormalShootReady;
    bool FirstPersonal;
    public:
    bool UsingAI;
    Handle<AI> Ai;
    bool Shoot;
        PersonageName Name;
        SpellControl SP;
        Ladar L;
        Aviate A;
        View V;
        Calculate JieCao;
        Calculate NormalRechard;
        XYZF ViewShift;
        Handle<Realm> LiveAt;
        void SetView();//偏移量
        virtual void Main(Realm* RB,long T){SP.Show(this,RB,T);}//显示函数
        virtual void Accessorial(Realm*,long);//分析函数
        virtual void FlatShow(ControlCenter*);//菜单函数 
        virtual void ReSet();//重置
        virtual void BaseControl(Handle<Information>& Inf,long);
        virtual void Interrupt(Realm *RB);
        virtual void Interrupt();
        virtual void SetPlayer();
        bool FristPersonal(){return ViewMode;}
        void SetAI(Handle<AI>);
        bool ShowMySelf(Realm* RB){return !RB->IsViewer(this)||!ViewMode;}

        //void IceCold(Signal*,bool){}
        void ChangePlace(void* S);
		//virtual void ShowCharicter(XYF);
        virtual void NormalShoot(Realm*){}
        Personage(PersonageName I,float P=4.0):Name(I),Object(OBJ_PERSONAGE),
                                                            FirstPersonal(false),A(P),ViewShift(XYZF(-1.0,1.0,-4.0)),Shoot(false),
                                                            NormalShootReady(false),JieCao(8000),ViewMode(false),
                                                            NormalRechard(1),UsingAI(false)
        {
			JieCao+4000L;
        }
};
#include "personage.cpp"
#endif
