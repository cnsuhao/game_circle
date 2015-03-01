#ifndef DIY_OBJECT_H
#define DIY_OBJECT_H
#include "../p.o/baseclass.h"
#include "../p.o/handle.h"
#include "objectsetting.h"
#include <map>
class Realm;
class Object:virtual public Coordinate ,virtual public HandleSeed
{
    public:
        State S;
        float Range;
        virtual void Display(Realm* Data,long T)=0;
        virtual void Accessorial(Realm* Data,long T)=0;
        float GetRange(){return Range;}
        Object(int S,float R=1.0):UnequalStaff<Realm*,long,int>(S),Range(R),BCanBeLock(true){}
};
/*class ObjectSpace:virtual public HandleSeed
{
public:
    UnequalBoss<ObjectSpace*,long,int> AllObject;
    void ChangeSpace(Handle<ObjectSpace> K,long T,int S){if(K)AllObject.JobHopping(&K->AllObject,S,K,T);}
    void ChangeSpaceAll(Handle<ObjectSpace> K,long T){if(K)AllObject.JobHopping(&K->AllObject,K,T);}
    void Accessorial(long T){AllObject.Accessorial(this,T);}
    void Main(long T){AllObject.Main(this,T);}
    virtual void GetObject(Handle<Object> C){AllObject.Employ(C);}
};*/
class Connection_Object:virtual public HandleSeed
{
    public:
        Handle<Object> First;
        Handle<Object> Second;
        Connection_Object(Handle<Object>& A,Handle<Object>& B):First(A),Second(B){}
        Connection_Object(){}
        Connection_Object(Connection_Object& L):First(L.First),Second(L.Second){}
        bool CheckExist(){First.Exist()&&Second.Exist();}
        void Connect(Handle<Object> &A, Handle<Object> &B);
};
void Connection_Object::Connect(Handle<Object> &A, Handle<Object> &B)
{
    First=A;
    Second=B;
}
/*template <class T>
class ObjectList
{
    static std::list<Handle<T> > List;
    public:
        Handle<T> Find(Handle<Object> H);
        ObjectList(Handle<T> P){ObjectList.push_back(P);}
};
template <class T>
std::list<Handle<T> > ObjectList<T>::List;
template <class T>
Handle<T> ObjectList<T>::Find(Handle<Object> H)
{
    for(std::list<Handle<T> >::iterator Po=List.begin();Po!=List.end();++Po)
    {
        if(*Po)
        {
            if(H)
            {
                if(Po->Data==H.Data)
                    return *Po;
            }
        }else{
            if((*Po)->Used)
            {
                if((*Po)->Exist)
                {
                    if((*Po)->Using==1)
                        List.erase(Po--);
                    else
                        Po->Follow();
                }else{
                    List.erase(Po--);
                }
            }
        }
    }
    Handle<T> Null;
    return Null;
}*/
#endif
