#ifndef  DIY_INFORMATION_H 
#define  DIY_INFORMATION_H 
#include <list>
#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL_events.h>
/*
ע��
#defind ��ʾЯ��������Ϣ����Ϣ��CATEGORY1������е�ֵ 
  #define ���������������£�CATEGORY2������е�ֵ 
    #define  CATEGORY3
*/ 
#include "handle.h"
#include "baseclass.h"
#define INFNULL 0
#define INFEXIT -11 //�˳� 
  #define MOUSEMOTION -2 //����ƶ�
  #define MOUSEBUTTONDOWN -1 //��꽡����
  #define MOUSEBUTTONUP 0 //����ɿ�
    #define MOUSEWHEEL SDL_MOUSEWHEEL//��껬�����ϻ�
    #define LEFT SDL_BUTTON_LEFT //������
    #define MIDDLE SDL_BUTTON_MIDDLE //����м�
    #define RIGHT SDL_BUTTON_RIGHT //����Ҽ�
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
    void* v;//����ʱ�������DELETE 
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
    DataForInformation Data1;//����Ϣ���������� 
    DataForInformation Data2;//ͬ�� 
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
