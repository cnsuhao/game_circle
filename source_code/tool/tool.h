#ifndef DIY_TOOL_H
#define DIY_TOOL_H
#include "../base/object.h"
#include "../p.o/controlcenter.h"
#include "../p.o/glsimplify.h"
#include "../p.o/calculate.h"
#include "../base/drawaquare.h"
#include "../realm/realm.h"
#define TOOL_CHECK_RANGE Range*1.5+0.5
enum ToolStyle
{
    TOOL_JIECAO
};
class Tool:public Object
{
    Handle<Object> Resource;
    Handle<Object> Target;
    Calculate Reflesh;
    Calculate Exist;
    public:
        virtual void Action(Handle<Object> T){}
        virtual void Destory(Realm* R){HandleSeed::Destory();}
        ToolStyle TS;
        Tool(ToolStyle S,Handle<Object> H,Coordinate& C,long E,float R=0.5):Object(OBJ_TOOL,R),TS(S),Resource(H),Exist(E),Coordinate(C),Reflesh(200){}
        void Show(void *Data, long T);
        void Analyze(void *Data, long T);
};
void Tool::Show(void *Data, long T)
{
    glPushMatrix();
    AddMatrix(this);
    glColor3f(0.0,0.5,1.0);
    DrawAquare(XYZF(0.0,0.0,0.0),Range/2,Range,Range/2);
    glPopMatrix();
}
void Tool::Analyze(void *Data, long T)
{
    Realm *R=static_cast<Realm*>(Data);
    Reflesh+T;
    if(Reflesh)
    {
        Target.Unused();
        float Distance=99999.0;
        Realm *R=static_cast<Realm*>(Data);
        if(R->Find(OBJ_PERSONAGE))
        {
            std::list<Handle<Object> >& Tem=R->ObjectList[OBJ_PERSONAGE];
            std::list<Handle<Object> >::iterator PO=Tem.begin();
            for(;PO!=Tem.end();++PO)
            {
                if(*PO)
                {
                    float Dis=(*PO)->Location.Distance(this->Location);
                    if(Dis<Distance)
                    {
                        if(Dis<(*PO)->Range+TOOL_CHECK_RANGE)
                        {
                            Distance=Dis;
                            Target=*PO;
                        }
                    }
                }
            }
        }
        Reflesh=0;
    }
    Exist+T;
    if(Exist)
    {
        Destory(R);
    }
}
#endif // TOOL_H