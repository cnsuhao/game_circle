#ifndef PO_H
#define PO_H
#include "pobase/pomain.h"
#include "pobase/poaccessorial.h"
#include "poerror.h"
#include "handle.h"
#include "plugin.h"
#include "informationpool.h"
#include "pobase/sdleventtoinformation.h"
#include <map>
#include <string>
int Thread_1_Function(PO*);
class PO:public POMain,public POAccessorial,public HandleSeed,public InformationPool
{
    friend int Thread_1_Function(PO* Data);
    PublicLock PL;
    bool Runing;
    long StartTime;
    PO():Runing(false){}
public:
    static std::list<void(*)(void)> ExitList;
    std::map<std::string,Handle<Plugin> > Define;
    static void Creat();
    Tank<Handle<Plugin> > Library;
    static Handle<PO> POPoint;
    static void SetDefultFont(std::string K){Creat(); POPoint->SDL_TTF_FONT=TTF_OpenFont(K.c_str(),60);}
    SDL_Event Event;
    //SDL_Thread* Thread1;
    void Exit();
    static void CreatFramework();
    static void Init();
    static void InitFinish();
    static void Regedit(Handle<Plugin>);
    static void MainLoop();
    static void ExitFunction(void (*K)(void)){ExitList.push_back(K);}
    static void SetWindow(int W,int H){Creat();POPoint->POMain::WindowW=W;POPoint->POMain::WindowH=H;}
    static void SetTitle(std::string L){Creat();POPoint->POMain::Title=L;}
    static Handle<Plugin> GetPlugin(Handle<Plugin> P){Creat();return P;}
};

std::list<void(*)(void)> PO::ExitList;
Handle<PO> PO::POPoint;
void PO::Regedit(Handle<Plugin> K)
{
    Creat();
    if(POPoint->Define.count(K->Scription())>0)
    {
        POError::GetError("The Plugin <"+K->Scription()+"> Have Already Exist.",-1);
        POPoint->Exit();
    }else{
        POPoint->Define[K->Scription()]=K;
        POPoint->Library.PushBack(K);
        POPoint->InformationPool::Regedit(K);
    }
}

void PO::MainLoop()
{
    using namespace std;
    while(POPoint->Runing)
    {
        while( SDL_PollEvent( &POPoint->Event) )
        {
            Handle<Information> Tem=Translate(POPoint->Event);
            if(Tem->IsExit())
                POPoint->Exit();
            POPoint->GetInformation(Tem);
        }
        POPoint->MainStart();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(140,static_cast<float>(POPoint->POMain::WindowW)/POPoint->POMain::WindowH,0.05,1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        for(Tank<Handle<Plugin> >::Ladle Po=POPoint->Library.Begin();!POPoint->Library.IsEnd(Po);++Po)
        {
            if(*Po)
            {
                (*Po)->Layer3D(POPoint);
            }
        }
        for(Tank<Handle<Plugin> >::Ladle Po=POPoint->Library.Begin();!POPoint->Library.IsEnd(Po);++Po)
        {
            if(*Po)
            {
                (*Po)->LayerBland(POPoint);
            }
        }
        for(Tank<Handle<Plugin> >::Ladle Po=POPoint->Library.Begin();!POPoint->Library.IsEnd(Po);++Po)
        {
            if(*Po)
            {
                (*Po)->LayerSpecial(POPoint);
            }
        }
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-1.0,1.0,-1.0,1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        for(Tank<Handle<Plugin> >::Ladle Po=POPoint->Library.Begin();!POPoint->Library.IsEnd(Po);++Po)
        {
            if(*Po)
            {
                (*Po)->Layer2D(POPoint);
            }
        }
        POPoint->MainFinish();
        if(GLTexture::Change)
        {
            //Error<<"Now Changeing"<<endl;
            for(std::list<string>::iterator Po=GLTexture::DeleteList.begin();Po!=GLTexture::DeleteList.end();++Po)
            {
                std::map<std::string,Handle<GLTexture> >::iterator Pk;
                Pk=GLTexture::TextureMap.find(*Po);
                if(Pk!=GLTexture::TextureMap.end())
                {
                    //Error<<"Delete "<<*Po<<endl;
                    GLTexture::TextureMap.erase(Pk);
                }
                GLTexture::DeleteList.erase(Po--);
            }
            GLTexture::Change=false;
        }
        Thread_1_Function(POPoint);
    }
}

void PO::Exit()
{
    //Error<<"Start To Exit"<<endl;
    POMain::Exit();
    PL.Lock();
    Runing=false;
    PL.UnLock();
    int Resoult=0;
    //Error<<"Start To Exit 2"<<endl;
    //SDL_WaitThread(Thread1,&Resoult);
    for(std::list<void(*)(void)>::iterator Po=ExitList.begin();Po!=ExitList.end();++Po)
        (*(*Po))();
    POPoint.Unused();
    //Error<<"Exit Finish"<<endl;
    exit(0);
}

void PO::Creat()
{
    if(!(POPoint))
        POPoint=new PO();
}


void PO::Init()
{
    Creat();
    SDL_ClearError();
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) //SDL初始化失败
        POError::GetError("There is Something Wrong!! The SDL Can Not Init As Your Wish.Please Check your Developmental Environmrnt./n Or May Be You Can Get Something From Here <"+std::string(SDL_GetError()),-1);
    if(IMG_Init(~0)<0)
        POError::GetError(std::string("The SDL_image can not Init as your wish, Or may be you can get something from here:/n")+SDL_GetError(),-1);
    if(TTF_Init()<0)
        POError::GetError(std::string("The SDL_TTF can not Init as your wish, Or may be you can get something from here:/n")+SDL_GetError(),-1);
    ExitFunction(SDL_Quit);//注册退出函数
    ExitFunction(IMG_Quit);
    ExitFunction(TTF_Quit );
    srand(SDL_GetTicks());
}

void PO::InitFinish()
{
        Creat();
        POPoint->CreatWindow();
        POPoint->CreatFramework();
        POPoint->SetMainStart();
        POPoint->POAccessorial::WindowW=POPoint->POMain::WindowW;
        POPoint->POAccessorial::WindowH=POPoint->POMain::WindowH;
}

void PO::CreatFramework()
{
    Creat();
    for(Tank<Handle<Plugin> >::Ladle Po=POPoint->Library.Begin();!POPoint->Library.IsEnd(Po);++Po)
        (*Po)->Init(POPoint);
    POPoint->Runing=true;
    //POPoint->Thread1=SDL_CreateThread(Thread_1_Function,"Accessorial",static_cast<void*>(POPoint.Data));
}
int Thread_1_Function(PO* POM)
{
    //PO *POM=dynamic_cast<PO*>(D);
    POM->SetAccessorialStart();
    //while(POM->Runing)
    //{
        POM->SentMessage();
        POM->AccessorialStart();
        for(Tank<Handle<Plugin> >::Ladle POc=POM->Library.Begin();!POM->Library.IsEnd(POc);++POc)
        {
            if(*POc)
            {
                (*POc)->Accessorial(POM);
            }
        }
        POM->AccessorialFinish();
    //}
    return 0;
}

#endif // PO_H
