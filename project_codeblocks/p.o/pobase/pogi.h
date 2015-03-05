#ifndef POGI_H
#define POGI_H
#include "../handle.h"
#include "../informationviewer.h"
#include "poplugin.h"
#include "pogidata.h"
#include <set>
//need to delete block picture
class PO;
enum WindowMode
{
    Windows,
    Full
};

class POGI:virtual public HandleSeed,public InformationViewer
{
protected:
    POGI(void):WindowH(480),WindowW(640){}
    std::list<Handle<POPlugin> > PluginLibrary;
    static std::map<std::string,Handle<POGIData> > AdressToHandle;
    static std::map<std::string,int > AdressCalculate;
public:
    virtual Handle<POPlugin> GetPlugin(Handle<POPlugin> K){PluginLibrary.push_back(K);return K;}
    int WindowH;
    int WindowW;
    WindowMode WM;
    Uint32 SDL_Flag;
    virtual void Init(PO*){InitPlugin();}
    void InitPlugin();
    virtual void CreatWindow(PO*)=0;
    virtual void DisplayManage(PO*)=0;
    bool Window(){return true;}
    void SetWindow(int W,int H,WindowMode K);
    SDL_Window* Surface(){return MainSurface;}


    static SDL_Texture* (* CreatPictureFunction)(std::string);
    static SDL_Surface* (* CreatTTFFunction)(std::string);
    Handle<POGIData> CreatPicture(std::string);
    void DelatePicture(std::string);


    virtual Handle<POGIData> CreatPictureDetail(std::string)=0;
    virtual Handle<POGIData> CreatTTF(std::string)=0;
};
std::map<std::string,Handle<POGIData> > POGI::AdressToHandle;
std::map<std::string,int > POGI::AdressCalculate;
SDL_Texture* (* POGI::CreatPictureFunction)(std::string);
SDL_Surface* (* POGI::CreatTTFFunction)(std::string);

void POGI::DelatePicture(std::string P)
{
    if(AdressToHandle.count(P)>0)
    {
        AdressCalculate[P]-=1;
        if(AdressCalculate[P]<=0)
        {
            AdressToHandle.erase(AdressToHandle.find(P));
            AdressCalculate.erase(AdressCalculate.find(P));
        }
    }
}

Handle<POGIData> POGI::CreatPicture(std::string P)
{
    Error<<"Using POGI Creat Picture :"<<P<<endl;
    if(AdressToHandle.count(P)==0)
    {
        Error<<"Creat New One"<<endl;
        Handle<POGIData> Tem=CreatPictureDetail(P);
        AdressToHandle[P]=Tem;
        AdressCalculate[P]=1;
        Error<<"Finish"<<endl;
        return Tem;
    }else{
        Error<<"Fin Old one"<<endl;
        AdressCalculate[P]+=1;
        Error<<"Finish"<<endl;
        return AdressToHandle[P];
    }
}

void POGI::SetWindow(int W, int H, WindowMode K)
{
    WindowW=W;
    WindowH=H;
    WM=K;
    /*if(K==Full)
        SDL_Flag=SDL_Flag|SDL_FULLSCREEN;*/
}

void POGI::InitPlugin()
{
    for(std::list<Handle<POPlugin> >::iterator Poc=PluginLibrary.begin();Poc!=PluginLibrary.end();++Poc)
    {
        if(*Poc)
        (*Poc)->Init(this);
    }
}

#endif // POGI_H
