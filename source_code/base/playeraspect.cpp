#ifndef DIY_PLAYERASPECT_H
#define DIY_PLAYERASPECT_H
#include "../p.o/plugin_base.h"
#include "../personage/personage.h"
class PlayerAspect:public Plugin_Base
{
	Handle<Personage> Player;
	std::list<Persongae> AllList;
	public:
		void FlatShow(ControlCenter *);
		void Analyze(ControlCenter *);
		void Push(Handle<Personage>);
		void ReSet(Handle<Personage> P);
		PlayerAspect(Handle<Personage> P):Player(P){}
};
void PlayerAspect::FlatShow(ControlCenter* CC)
{
	if(Player)
	{
		Player->FlatShow(CC);
	}
}
void PlayerAspect::Push(Handle<Personage> P)
{
	if(P)
	{
		if(!(P==Player))
		{
			if(AllList.empty())
			{
				AllList.push_back(P);
			}else{
				bool Exist=false;
				for(std::list<Handle<Object> >::iterator Po=AllList.begin();Po!=AllList.end();++Po)
				{
					if(P==*Po)
					{
						Exist=true;
						break;
					}
				}
				if(!Exist)
				{
					AllList.push_back(P);
				}
			}
		}
	}
}
void PlayerAspect::ReSet(Handle<Personage> P)
{
	Player=P;
}
#endif
