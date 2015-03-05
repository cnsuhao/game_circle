#ifndef  DIY_INFORMATION_H 
#define  DIY_INFORMATION_H 
#include <list>
#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL_events.h>
/*
注：
#defind 表示携带该种信息的信息类CATEGORY1所因具有的值 
  #define 当以上满足的情况下，CATEGORY2所因具有的值 
    #define  CATEGORY3
*/ 
#include "handle.h"
#include "baseclass.h"
#define INFNULL 0
#define INFEXIT -11 //退出 
  #define MOUSEMOTION -2 //鼠标移动
  #define MOUSEBUTTONDOWN -1 //鼠标健按下
  #define MOUSEBUTTONUP 0 //鼠标松开
    #define MOUSEWHEEL SDL_MOUSEWHEEL//鼠标滑轮往上滑
    #define LEFT SDL_BUTTON_LEFT //鼠标左键
    #define MIDDLE SDL_BUTTON_MIDDLE //鼠标中键
    #define RIGHT SDL_BUTTON_RIGHT //鼠标右键
#define INFMOUSELOCK 79856
#define INFMOUSEUNLOCK 75932

  #define INFKEYDOWN -98
  #define INFKEYUP -77
#define INFWINDOWACTIVE -76
#define INFWINDOWDISACTIVE -67

#define SPECIALINFORMATION -78954
class BaseInformation
{
    public:

};
union DataForInformation
{
    unsigned int ui;
    bool b;
    unsigned char uc;
    char c;
    int i;
    float f;
    double d;
    void* v;//析构时不会调用DELETE 
    operator int(){return i;}
    operator bool(){return b;}
    operator char(){return c;}
    operator float(){return f;}
    operator double(){return d;}
    operator void*(){return v;}
    operator unsigned int(){return ui;}
    operator unsigned char(){return uc;}
    void operator= (unsigned char Tem){uc=Tem;}
    void operator= (char Tem){c=Tem;}
    void operator= (unsigned int Tem){ui=Tem;}
    void operator= (int Tem){i=Tem;}
    void operator= (float Tem){f=Tem;}
    void operator= (bool Tem){b=Tem;}
    void operator= (double Tem){d=Tem;}
    void operator= (void* Tem){v=Tem;}
    //void operator= (const DataForInformation& Tc){this->d=Tc.d;}
};
class Information:public HandleSeed
{
    public:
    int Category;
    DataForInformation Data1;//随信息附带的数据 
    DataForInformation Data2;//同上 
    DataForInformation Data3;
    DataForInformation Data4;
    ~Information(){}
    Information():Category(0){}
    void operator= (const Information& Tec)
    {
        Category=Tec.Category;
        Data1=Tec.Data1;
        Data2=Tec.Data2;
        Data3=Tec.Data3;
        Data4=Tec.Data4;
    }
    Information(const Information& P):Category(P.Category),Data1(P.Data1),Data2(P.Data2),Data3(P.Data3),Data4(P.Data4){}

    bool IsMouse(){return IsMouseMotion()||IsMouseButtonDown()||IsMouseButtonUp();}
    bool IsWindow(){return IsWindowActive()||IsWindowDisActive()||IsExit();}
    bool IsWindowActive(){return Category==INFWINDOWACTIVE;}
    bool IsWindowDisActive(){return Category==INFWINDOWDISACTIVE;}
    bool IsKey(unsigned char k){return Data1.uc==k;}
    bool IsMouseWheel(){return Category==MOUSEWHEEL;}
    bool IsCustom(){return Category==SPECIALINFORMATION;}
    int MouseMotionX(){return Data3.i;}
    int MouseMotionY(){return Data4.i;}
    void GetMouse(int &K,int &P){K=Data1.i;P=Data2.i;}

    bool IsExit(){return Category==INFEXIT;}
    bool IsKeyDown(){return Category==INFKEYDOWN;}
    bool IsKeyUp(){return Category==INFKEYUP;}
    bool IsMouseMotion(){return Category==MOUSEMOTION;}
    bool IsMouseButtonDown(){return Category==MOUSEBUTTONDOWN;}
    bool IsMouseButtonUp(){return Category==MOUSEBUTTONUP;}
    bool IsMouseButtonLeft(){return Data3.i==LEFT;}
    bool IsMouseButtonMiddle(){return Data3.i==MIDDLE;}
    bool IsMouseButtonRight(){return Data3.i==RIGHT;}
};
#endif
