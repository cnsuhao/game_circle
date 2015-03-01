#ifndef PUBLICVALUE_H
#define PUBLICVALUE_H
#include <SDL2/SDL_mutex.h>
class PublicLock
{
public:
    //SDL_semaphore *LockSem;
    void Lock(){/*SDL_SemWait(LockSem);*/}
    void UnLock(){/*SDL_SemPost(LockSem);*/}
    ~PublicLock(){/*SDL_DestroySemaphore(LockSem);*/}
    PublicLock(){/*LockSem=SDL_CreateSemaphore(1);*/}
    //PublicLock(const PublicLock&){LockSem=SDL_CreateSemaphore(1);}
    PublicLock& operator=(PublicLock& K){}
};



/*template <class T>
        class PublicValue:public T
{
public:
    PublicLock Read;
    void Wait(){}
    void Lock(){Read.Lock();}
    void UnLock(){Read.UnLock();}
    PublicValue()
    {
    }
    ~PublicValue()
    {
    }
};

template <class T>
        class PublicBaseValue
{
        void Lock(){SDL_SemWait(Using);}
    void UnLock(){SDL_SemPost(Using);}
public:
    T Data;
    SDL_semaphore *Using;
    void Wait(){}

    PublicBaseValue()
    {
        Using=SDL_CreateSemaphore(1);
    }
    ~PublicBaseValue()
    {
        SDL_DestroySemaphore(Using);
    }
    bool operator!=(T C){Lock();bool Tc=(Data!=C);UnLock();return Tc;}
    T operator+(T C){Lock();T Tc=(Data+C);UnLock();return Tc;}
    T operator-(T C){Lock();T Tc=(Data-C);UnLock();return Tc;}
    bool operator-=(T C){Lock();Data-=C;T Tc=Data;UnLock();return Tc;}
    bool operator+=(T C){Lock();Data+=C;T Tc=Data;UnLock();return Tc;}
    bool operator>(T C){Lock();bool Tc=(Data>C);UnLock();return Tc;}
    bool operator>=(T C){Lock();bool Tc=(Data>=C);UnLock();return Tc;}
    bool operator<=(T C){Lock();bool Tc=(Data<=C);UnLock();return Tc;}
    bool operator==(T C){Lock();bool Tc=(Data==C);UnLock();return Tc;}
    bool operator<(T P){Lock();bool Tc=(Data<P);UnLock();return Tc;}
    operator T(){Lock();T Y=Data;UnLock();return Y;}
    T operator=(T t){Lock();Data=t;UnLock();return t;}
    T* operator&(){Lock();T* J=&Data;UnLock();return J;}
    //PublicBaseValue(const PublicBaseValue&){}
    //PublicBaseValue& operator=(PublicBaseValue& K){}
};
class ReadWriteLock
{
    PublicBaseValue<int> Reading;
    PublicBaseValue<bool> WriteT;
public:
    void Read(){while(1){if(!WriteT){Reading+=1;break;}}}
    void ReadingFinish(){Reading-=1;}
    void Write(){while(1){if(!WriteT){WriteT=true;break;}}while(1){if(Reading==0){break;}}}
    void WriteFinish(){WriteT=false;}
    ReadWriteLock()
    {
        Reading=0;
        WriteT=false;
    }
    ReadWriteLock(const ReadWriteLock&){Reading=0;WriteT=false;}
    ReadWriteLock& operator=(ReadWriteLock& K){}
};



class PublicKey
{
public:
    SDL_semaphore *Using;
    void Wait(){}
    void Lock(){SDL_SemWait(Using);}
    void UnLock(){SDL_SemPost(Using);}
    PublicKey()
    {
        Using=SDL_CreateSemaphore(1);
    }
    ~PublicKey()
    {
        SDL_DestroySemaphore(Using);
    }
};*/
#endif // PUBLICVALUE_H
