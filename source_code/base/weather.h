#ifndef DIY_WEATHER_H
#define DIY_WEATHER_H
#include "../p.o/calculate.h"
#include "../p.o/sgprint.h"
#define Wea_Spr 1
#define Wea_Aut 3
#define Wea_Sum 2
#define Wea_Win 4
#define Tim_Mor 5
#define Tim_Aft 6
#define Tim_Nig 7
class Weather
{
    Sentence Season;
    Sentence Time;
    public:
        int WS;//To store Weather now
        int TS;//To store Time now, after the time become moring again, the weather will become the next;
        int WF;
        int TF;
        int LT;
        int LS;
        bool WeatherFroceChange;
        Calculate FT;
        Calculate H;//How long that the time change
        Weather(long T=2000,int W=Wea_Spr,int TP=Tim_Mor):H(T),WS(W),TS(TP),LT(-999),LS(-9999),WeatherFroceChange(false),FT(0){WF=WS;TF=TS;}
        bool Analyze(long T);
        int FinalSeason(){return WF;}
        int FinalTime(){return TF;}
        int RealSeason(){return WF;}
        int RealTIme(){return WS;}
        XYF ShowSeason(float X,float Y,float R=1.0,float B=1.0,float G=1.0,float Size=0.1,float A=1.0);
        XYF ShowSeason(XYF L,float R=1.0,float B=1.0,float G=1.0,float Size=0.1,float A=1.0){return ShowSeason(L.X,L.Y,R,G,B,Size,A);}
        XYF ShowTime(float X,float Y,float R=1.0,float B=1.0,float G=1.0,float Size=0.1,float A=1.0);
        XYF ShowTime(XYF L,float R=1.0,float B=1.0,float G=1.0,float Size=0.1,float A=1.0){return ShowTime(L.X,L.Y,R,G,B,Size,A);}
        bool IsFroceChange(){return WeatherFroceChange;}
};
XYF Weather::ShowSeason(float X,float Y,float R,float B,float G,float Size,float A)
{
    if(LS!=WF)
    {
        switch(WF)
        {
        case Wea_Win:
            Season.Add("Winter");
            break;
        case Wea_Spr:
            Season.Add("Spring");
            break;
        case Wea_Sum:
            Season.Add("Summer");
            break;
        case Wea_Aut:
            Season.Add("Autumn");
        }
        LS=WF;
    }
    return Season.Show(X,Y,R,B,G,Size);
}

XYF Weather::ShowTime(float X,float Y,float R,float B,float G,float Size,float A)
{
    if(LT!=TF)
    {
        switch(TF)
        {
        case Tim_Mor:
            Time.Add("Moring");
            break;
        case Tim_Aft:
            Time.Add("Afternoon");
            break;
        case Tim_Nig:
            Time.Add("Night");
            break;
        }
        LT=TF;
    }
    return Time.Show(X,Y,R,B,G,Size);
}

bool Weather::Analyze(long T)
{
    if(WeatherFroceChange)
    {
        FT+T;
        if(FT)
        {
            WeatherFroceChange=false;
            FT=0;
            WF=WS;
            TF=TS;
            return true;
        }
    }
    H+T;
    if(H)
    {
        if(TS==Tim_Nig)
        {
            TS=Tim_Mor;
            if(WS==Wea_Win)
            {
                WS=Wea_Spr;
            }else{
                WS=WS+1;
            }
        }else{
            TS=TS+1;
        }
        H=0;
        if(!WeatherFroceChange)
        {
            WF=WS;
            TF=TS;
            return true;
        }
    }
    return false;
}
#endif
