#ifndef DIY_PERSONAGE_CPP
#define DIY_PERSONAGE_CPP
#include "personage.h"
void Personage::SetPlayer()
{
    FirstPersonal=true;
}
/*void Personage::Change(ChangeStyle CS,void * P)
{
    switch(CS)
    {
        case Cha_Wea:
            {
                Realm* C=static_cast<Realm*>(P);
                WeatherDifferent=true;
            }
            break;
        case Cha_Eff:
            break;
    }
}*/
void Personage::ChangePlace(void* S)
{
    Realm* RB=static_cast<Realm*>(S);
    LiveAt=RB;
    ReSet();
    Interrupt(RB);
    //Change(Cha_Wea,S);
}
void Personage::Interrupt()
{
    //SC.Interrupt();
    //SP.Interrupt();
}
void Personage::Interrupt(Realm *RB)
{
    //SC.Interrupt(this,RB);
    //SP.Interrupt(this,RB);
}
void Personage::ReSet()
{
    L.Clean();
    A.ResetMove();
    A.ResetView(); 
}
void Personage::FlatShow(ControlCenter* CC)
{
    L.FlatShow(ViewShift,this,&V,CC);
    SP.FlatShow(XYF(-0.4,-0.8));
    glColor3f(1.0,0.8,0.3);
    glBegin(GL_LINES);
    glVertex(-0.6,0.9);
    glVertex(-0.6,0.85);
    glVertex(0.6,0.85);
    glVertex(0.6,0.9);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex(-0.6,0.9);
    glVertex(-0.6,0.85);
    glVertex(-0.6+1.2*((float)S.JieCao/S.RealJieCao),0.85);
    glVertex(-0.6+1.2*((float)S.JieCao/S.RealJieCao),0.9);
    glEnd();
}
void Personage::SetAI(Handle<AI> A)
{
    if(A)
    {
        Ai=A;
        UsingAI=true;
    }
}

void Personage::Accessorial(Realm* RB,long Time)
{
    //error<<"PAS"<<endl;
    if(!NormalShootReady)
    {
        NormalRechard+Time;
        if(NormalRechard)
        {
            NormalShootReady=true;
        }
    }else{
        if(Shoot)
        {
            NormalShoot(RB);
            NormalShootReady=false;
            NormalRechard=0;
        }
    }
    if(UsingAI)
    {
        Ai->Accessorial(this,RB,Time);
    }
    //SC.Analyze(RB,this,Time);
    SP.Analyze(RB,this,Time);
    A.Run(this,&V,RB,Time);
    L.Analyze(this,&V,RB,Time);
    V.Run(Time,RB->Horizontal());
    //error<<"PAE"<<endl;
}
void Personage::SetView()
{
    XYZF Pian=ViewShift.X*V.Left()+ViewShift.Y*V.Up()+ViewShift.Z*V.Front();
    gluLookAt(Location+Pian,Location+V.Front()+Pian,V.Up());
    //gluLookAt(XYZF(0.0,4.0,-2.0),XYZF(0.0,4.0,-2.0)+V.Front(),V.Up());
}
void Personage::BaseControl(Handle<Information>& Inf,long T)
{
    float Time=T/1000.0;
    static std::map<unsigned char , bool > Key;
    if(Inf->IsKeyDown())
    {
        if(Key.count(Inf->Data1)>0)
        {
            Key[Inf->Data1]=true;
        }else{
            if(Inf->Data1.uc==' ')
            {
                A.StartJump();
            }
        }
    }else if(Inf->IsKeyUp())
    {
        if(Key.count(Inf->Data1)>0)
        {
            Key[Inf->Data1]=false;
        }else{
            if(Inf->Data1.uc==' ')
            {
                A.EndJump();
            }
        }
    }else if(Inf->IsMouseMotion())
    {
        if(Inf->Data1.f<0)
        {
            V.TakeControl(Vie_Lef);
        }else if(Inf->Data1.f>0)
        {
            V.TakeControl(Vie_Rig);
        }
        if(Inf->Data2.f<0)
        {
            V.TakeControl(Vie_Dow);
        }else if(Inf->Data2.f>0)
        {
            V.TakeControl(Vie_Up);
        }
    }else if(Inf->IsMouseButtonDown())
    {
        if(Inf->IsMouseButtonLeft())
            Shoot=true;
    }else if(Inf->IsMouseButtonUp())
    {
        if(Inf->IsMouseButtonLeft())
            Shoot=false;
    }
    //SC.Control(Inf);
    SP.Control(Inf);
    if(Key['w']){A.Front();}else if(Key['s']){A.Back();}else A.StopFAD();
    if(Key['a']){A.Left();}else if(Key['d']){A.Right();}else A.StopLAR();
    //if(Key['q']){A.VRAN=1;}else A.VRAN=0;
        //if(Key['e']){H->Aviate::VRAN=-1;}else H->Aviate::VRAN=0;
        //if(Key['z']){H->Aviate::Urgency=true;}else H->Aviate::Urgency=false;
        //if(Key['p']){H->ViewStyle();Key['p']=false;}
        //if(Key['t']){H->Ladar::Target();Key['t']=false;}
    //if(Key['o']){A.ChangeToWalk();Key['o']=false;}
    //if(Key['p']){A.ChangeToFly();Key['p']=false;}
    if(Key['l']){L.ChangeTarget();Key['l']=false;}
    //if(Key['`']){if(!SP.UsingSpell)SpellMode=!SpellMode;Key['`']=false;}
        //if(Key['c']){H->Shoot=true;Key['c']=false;}
	if(Key['v'])
	{
		Key['v']=false;
		ViewMode=!ViewMode;
		if(ViewMode)
		{
                        ViewShift.Set(0.0,0.5,0.5);
		}else{
			ViewShift.Set(-1.0,1.0,-4.0);
		}
	}
}
#endif
