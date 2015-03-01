#ifndef STATE_H
#define STATE_H
class State
{
public:
    long RealJieCao;
    long JieCao;
    float RealSpeed;
    float Speed;
    long RealDamage;
    float Damage;
    State(long RJ=80000,long J=40000,float S=2.0,long D=100):RealJieCao(RJ),JieCao(J),RealSpeed(S),Speed(S),RealDamage(D){}
};

#endif // STATE_H
