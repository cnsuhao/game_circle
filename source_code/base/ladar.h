#ifndef DIY_LADAR_H
#define DIY_LADAR_H
#include "../p.o/controlcenter.h"
#include "../p.o/baseclass.h"
#include "../p.o/handle.h"
#include "../p.o/calculate.h"
#include "object.h"
#include "../p.o/controlcenter.h"
#include "../realm/realm.h"
#include "view.h"
#include <list>
#include <map>
class Connection_Object;
class ObjectSpace;
class Ladar
{
    Calculate Interval;
	Calculate LockTime;
    float Range;


	void ChangeTargetDetail(Object*,Realm*);
	std::list<Handle<Object> >BulletList;
    public:
        Handle<Object> Target;
        bool LockReady;
        bool Lock;
        void FlatShow(XYZF,Object*,View*,ControlCenter*);
        Ladar():Range(100.0),LockTime(5000),Lock(false),Interval(200){}
        void Analyze(Object*,View*,Realm*,long);
        void Clean(void);
        void UnLock();
        void Locking(Object*,View*,Realm*,long);
        void ChangeTarget();
        bool FindFirst(Handle<Object>,Object*);
        bool FindTarget(Handle<Object>,int,int*,Object*);
        bool LockTarget(Handle<Object>,int*,Object*);
        Handle<Object> AimAt();
};
bool Ladar::FindFirst(Handle<Object> H,Object* O)
{
    if(H!=O)
    {
        if(H)
        {
            return true;
        }
    }
    return false;
}

bool Ladar::FindTarget(Handle<Object> H,int Size,int *Cal,Object* O)
{
    if(H!=O)
    {
        if(H)
        {
            (*Cal)+=1;
            if((*Cal)==Size)
                return true;
        }
    }
    return false;
}

bool Ladar::LockTarget(Handle<Object> H,int * T,Object* O)
{
    if(H!=O)
    {
        if(H==Target)
        {
            return true;
        }else{
            (*T)+=1;
        }
    }
    return false;
}

void Ladar::ChangeTarget()
{
    Lock=true;
}
void Ladar::Locking(Object* O,View* V,Realm *RB,long T)
{
    Interval+T;
    if(Target)
    {
        if((LockReady&&(Interval))||!LockReady)
        {
            XYZF Vec=Target->Location-O->Location;
            if(Vec.Long()<Range-Target->Range-O->Range)
            {
                Vec=Vec.Uint();
                if(Vec*V->Front()>=0.3)
                {
                    if(!LockReady)
                    {
                        LockTime+T;
                        //error<<"miaozhunzhong"<<endl;
                        if(LockTime)
                        {
                            LockReady=true;
                            Interval=0;
                        }
                    }else{
                        Interval=0;
                    }
                }else{
                    LockTime=0;
                    LockReady=false;
                }
            }else{
                LockTime=0;
                LockReady=false;
            }
        }
    }else{
        ChangeTargetDetail(O,RB);
    }
}
Handle<Object> Ladar::AimAt()
{
    if(LockReady)
        return Target;
    Handle<Object> Tem;
    return Tem;
}
void Ladar::UnLock()
{
    Target.Unused();
    LockReady=false;
    LockTime=0;
    Interval=0;
}
void Ladar::ChangeTargetDetail(Object *O, Realm *RB)
{
    if(Target)
    {
        int Num=0;
        Handle<Object> Tc;
        if(O->Find(Tc,OBJ_PERSONAGE,&Ladar::LockTarget,this,&Num,O))
        {
            int Tk=0;
            if(O->Find(Tc,OBJ_PERSONAGE,&Ladar::FindTarget,this,Num+1,&Tk,O))
            {
                Target=Tc;
            }else{
                if(O->Find(Tc,OBJ_PERSONAGE,&Ladar::FindFirst,this,O))
                {
                    Target=Tc;
                }
            }
        }else{
            if(O->Find(Tc,OBJ_PERSONAGE,&Ladar::FindFirst,this,O))
            {
                Target=Tc;
            }
        }
    }else{
        O->Find(Target,OBJ_PERSONAGE,&Ladar::FindFirst,this,O);
    }
}
void Ladar::FlatShow(XYZF P,Object* O,View* V,ControlCenter* CC)
{
    float Dis=0.0;
    glLineWidth(0.5);
	if(Target)
	{
            XYZF Te=Target->Location-O->Location-P.X*V->Left()-P.Y*V->Up()-P.Z*V->Front();
                XYZF Tem(Te*V->Left(),Te*V->Up(),Te*V->Front());
                //Tem=O->ToCoordinate(Tem);
		Tem.Z=-Tem.Z;
		XYF Tem2;
		if(CC->ChangeIntoFlat(Tem,Tem2))
		{
			Tem2.X=-Tem2.X;
			if(!LockReady)
			{
				glColor3f(0.0,0.0,1.0);
				glBegin(GL_LINE_LOOP);
				glVertex(Tem2+XYF(-0.1*(2.0-~LockTime),0.1*(2.0-~LockTime)));
				glVertex(Tem2+XYF(-0.1*(2.0-~LockTime),-0.1*(2.0-~LockTime)));
				glVertex(Tem2+XYF(0.1*(2.0-~LockTime),-0.1*(2.0-~LockTime)));
				glVertex(Tem2+XYF(0.1*(2.0-~LockTime),0.1*(2.0-~LockTime)));
				glEnd();
			}else{
				glColor3f(1.0,1.0,0.0);
				glBegin(GL_LINE_LOOP);
				glVertex(Tem2+XYF(-0.1,0.1));
				glVertex(Tem2+XYF(-0.1,-0.1));
				glVertex(Tem2+XYF(0.1,-0.1));
				glVertex(Tem2+XYF(0.1,0.1));
				glEnd();
			}
		}
	}
}
void Ladar::Analyze(Object *O, View* V,Realm *RB,long T)
{
    Locking(O,V,RB,T);
    if(Lock)
    {
        ChangeTargetDetail(O,RB);
        Lock=false;
    }
}
void Ladar::Clean()
{
    UnLock();
}


#endif
