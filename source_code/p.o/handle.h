#ifndef DIY_HANDLE_H
#define DIY_HANDLE_H
#include <stdio.h>
class HandleSeed
{
    public:
    bool Exist;
    unsigned int Life;
    unsigned int Using;
    virtual ~HandleSeed(){}
    virtual bool CheckExist(){return Exist;}
    virtual void Destory(){Exist=false;}
    virtual void HandleUnused(){}
    virtual void GetHandle(){}
    HandleSeed():Exist(true),Using(0),Life(0){}
};


template <class T>
class Handle
{
    public:
        bool Used;
        T* Data;
        unsigned int Life;
        void operator =(T* L);
        bool operator ==(Handle&);
        void operator =(Handle&);
        //void operator =(const Handle&);
        bool operator<(Handle<T>& H){return Data<H.Data;}
        template <class G>
                void operator =(Handle<G>&);
        template <class G>
                bool operator ==(G*);
        template <class G>
                bool operator !=(G*);
        template <class G>
                bool operator !=(Handle<G>&);
        void Rebirth();
        void Follow(){if(Used) Life=Data->HandleSeed::Life;}
        void Unused();
        operator bool();
        bool Exist();
        operator T*(void){return Data;}
        T* operator->(){return Data;}
        template <class G>
                bool operator ==(Handle<G>&);
        template <class P>
                operator Handle<P>();
        Handle():Used(false),Data(0){}
        Handle(const Handle& H);
        Handle(T*);
        virtual ~Handle();
};
template <class T>
        template <class G>
        bool Handle<T>::operator !=(G* C)
{
    if(*this)
    {
        T* Tem=dynamic_cast<T*>(C);
        if(Data!=Tem)
            return true;
    }
    return false;
}
template <class T>
        template <class G>
        bool Handle<T>::operator !=(Handle<G>& C)
{
    if(*this)
    {
        if(C)
        {
            T* Tem=dynamic_cast<T*>(C.Data);
            if(Data!=Tem)
                return true;
        }
    }
    return false;
}
template <class T>
        template<class G>
bool Handle<T>::operator ==(G *C)
{
    if(Used)
    {
        if(Data==dynamic_cast<T*>(C))
            return true;
    }
}

template <class P>
        bool Handle<P>::operator == (Handle<P>& F)
{
    if(*this)
    {
        if(F)
        {
            if(Data==F.Data)
                return true;
        }
    }
    return false;
}
template <class T>
        template <class G>
        void Handle<T>::operator =(Handle<G>& D)
                                  {
    this->Unused();
    if(D)
    {
        T* P=dynamic_cast<T*>(D.Data);
        if(P)
        {
            *this=P;
        }
    }
}
template <class T>
        template <class G>
        Handle<T>::operator Handle<G>()
{
    Handle<G> Tem;
    if(*this)
    {
        G* P=dynamic_cast<G*>(Data);
        if(P)
        {
            Tem=P;
        }
    }
    return Tem;
}
template<class T>
void Handle<T>::operator =(T* L)
{
    Unused();
    if(L)
    {
        Used=true;
        Life=L->HandleSeed::Life;
        L->HandleSeed::Using+=1;
        L->GetHandle();
        Data=L;
    }
}
template<class T>
void Handle<T>::operator =(Handle<T>& H)
{
    if(this!=&H)
    {
        Unused();
        if(H)
        {
            Used=H.Used;
            Data=H.Data;
            Life=H.Life;
            if(H.Used)
            {
                Data->HandleSeed::Using+=1;
                Data->GetHandle();
            }
        }
    }
}

template<class T>
Handle<T>::Handle(const Handle &H)
{
    Used=H.Used;
    Data=H.Data;
    Life=H.Life;
    if(H.Used)
    {
        Data->HandleSeed::Using+=1;
        Data->GetHandle();
    }
}
template<class T>
Handle<T>::~Handle()
{
    Unused();
}
template<class T>
Handle<T>::Handle(T *L)
{
    Life=L->HandleSeed::Life;
    L->HandleSeed::Using+=1;
    Data=L;
    Data->GetHandle();
    Used=true;
}
template<class T>
bool Handle<T>::Exist()
{
    if(!Used)
    {
        return false;
    }else{
        if(Life!=Data->HandleSeed::Life) return false;
        else return Data->CheckExist();
    }
}
template<class T>
Handle<T>::operator bool()
{
    return Exist();
}
template<class T>
void Handle<T>::Rebirth()
{
    if(Exist())
    {
        Data->HandleSeed::Life+=1;
        Life=Data->HandleSeed::Life;
    }
}
template <class T>
        template <class G>
        bool Handle<T>::operator ==(Handle<G>& P)
{
    if(*this)
    {
        if(P)
        {
            if(Data==dynamic_cast<T*>(P.Data))
            {
                return true;
            }
        }
    }
    return false;
}
template <class T>
        void Handle<T>::Unused()
{
    if(Used)
    {
        Data->HandleSeed::Using-=1;
        Data->HandleUnused();
        if(Data->HandleSeed::Using==0)
        {
            delete Data;
        }
        Used=false;
    }
}
#endif // HANDLE_H
