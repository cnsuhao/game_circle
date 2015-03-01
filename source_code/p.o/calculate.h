#ifndef DIY_CALCULATER_H
#define DIY_CALCULATER_H
class Calculate
{
    public:
        long NeedTime;
        long Time;
        Calculate(long T):NeedTime(T),Time(0){}
        Calculate(long T,long P):NeedTime(P),Time(T){}
        float Present(void){return (float)Time/NeedTime;}
        float operator~ (void) {return (float)Time/NeedTime;}
        bool operator+ (long T){Time+=T; return *this;}
        void operator= (long T){Time=T;}
        void operator= (int T){Time=static_cast<long>(T);}
        bool operator< (int T){if(Time<T) return true; else return false;}
        bool operator<=(int T){if(Time<=T)return true;else return false;}
        bool operator> (int T){if(Time>T) return true; else return false;}
        bool operator>=(int T){if(Time>=T)return true;else return false;}
        bool operator< (long T){if(Time<T) return true; else return false;}
        bool operator<=(long T){if(Time<=T)return true;else return false;}
        bool operator> (long T){if(Time>T) return true; else return false;}
        bool operator>=(long T){if(Time>=T)return true;else return false;}

        bool operator< (float T){if(Time<T*NeedTime) return true; else return false;}
        bool operator<=(float T){if(Time<=T*NeedTime)return true;else return false;}
        bool operator> (float T){if(Time>T*NeedTime) return true; else return false;}
        bool operator>=(float T){if(Time>=T*NeedTime)return true;else return false;}
        void operator<<(long T){NeedTime=T;}
        void operator= (float T){Time=static_cast<long>(NeedTime*T);}

        bool operator()(long T,long P){if(Time>=T&&Time<=P) return true;else return false;}
        bool operator()(float T,long P){if(Time>=T*NeedTime&&Time<=P*NeedTime) return true;else return false;}
        operator bool(){if(Time>=NeedTime) return true; else return false;}
        operator long(){return Time;}
        operator int(){return Time;}
};
#endif
