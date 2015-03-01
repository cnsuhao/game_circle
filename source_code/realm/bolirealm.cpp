#ifndef DIY_BOLIREALM_CPP
#define DIY_BOLIREALM_CPP
#include "../p.o/plugin_base.h"
#include "realm.h"
#include "../personage/personage.h"
class BoliRealm:public Plugin_Base,public Realm
{
    public:
        //Picture Ty;
        void Main(ControlCenter*,long);
        void Accessorial(ControlCenter*,long);
        void FlatShow(ControlCenter*);
        void Init(ControlCenter*,long);
        void BackgroundShow();
        Sentence KK;
        BoliRealm(Handle<Object> H):Plugin_Base("Boli"),Realm(REALM_BOLI,H){}
};
void BoliRealm::BackgroundShow()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    for(int i=0;i<=50;++i)
    {
        glVertex3f(-250.0+i*10,-1.0,250.0);
        glVertex3f(-250.0+i*10,-1.0,-250.0);
    }
    for(int i=0;i<=50;++i)
    {
        glVertex3f(-250.0,-1.0,-250.0+i*10);
        glVertex3f(250.0,-1.0,-250.0+i*10);
    }
    glEnd();
}
void BoliRealm::Init(ControlCenter* CC,long )
{
    //Ty.Load("texture//try2.jpg");
    KK.Add("GgfurthtfghsdG");
}
void BoliRealm::FlatShow(ControlCenter* CC)
{
    ShowData();
    //Ty.Show(-1.0,1.0,1.0,-1.0);
    //KK.Show(0.0,0.0);
    //Season.Show(-1.0,1.0);
}
void BoliRealm::Main(ControlCenter* CC,long)
{
    ShowObject(CC->IntervalTimeShow);
    BackgroundShow();
}
void BoliRealm::Accessorial(ControlCenter* CC,long)
{
    Useless();
    AnalyzeObject(CC->IntervalTimeAnalyze);
}
#endif
