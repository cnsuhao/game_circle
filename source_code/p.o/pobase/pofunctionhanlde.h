#ifndef POFUNCTIONHANLDE_H
#define POFUNCTIONHANLDE_H
class POFunctionHandle
{
    bool Using;
    void (*Point)(void);
public:
    operator bool(){return Using;}
    void operator =(void (*K)(void)){Point=K;Using=true;}
    void Run(){(*Point)();}
    POFunctionHandle():Using(false){}
    POFunctionHandle(POFunctionHandle& K):Using(K.Using),Point(K.Point){}
};
#endif // POFUNCTIONHANLDE_H
