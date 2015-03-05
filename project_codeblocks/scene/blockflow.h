#ifndef BLOCKFLOW_H
#define BLOCKFLOW_H
class JumpLock
{
public:
    int Start;
    int End;
    int To;
    JumpLock(const JumpLock& J):Start(J.Start),End(J.End),To(J.To){}
    JumpLock(JumpLock& J):Start(J.Start),End(J.End),To(J.To){}
    JumpLock(int S,int E,int T):Start(S),End(E),To(T){}
    JumpLock():Start(0),End(0),To(0){}
};

class BlockFlow
{
public:
    std::map<int,JumpLock> JumpDefine;
    std::map<int,int> NormalJumpDefine;
    bool AddNormaJump(int K,int T);
    bool AddJumpLock(int A,int B,int C,int D);
    bool FindJumpLock(int& S,JumpLock& P);
    bool FindJump(int &S);
    void Clean(){NormalJumpDefine.clear();JumpDefine.clear();}
};

bool BlockFlow::AddJumpLock(int A, int B, int C, int D)
{
    if(JumpDefine.count(A)==0)
    {
        JumpDefine[A]=JumpLock(B,C,D);
        return true;
    }else{
        return false;
    }
}

bool BlockFlow::AddNormaJump(int K,int T)
{
    if(NormalJumpDefine.count(K)==0)
    {
        NormalJumpDefine[K]=T;
        return true;
    }else{
        return false;
    }
}

bool BlockFlow::FindJump(int &S)
{
    if(NormalJumpDefine.count(S)==0)
        return false;
    else{
        S=NormalJumpDefine[S];
        return true;
    }
}

bool BlockFlow::FindJumpLock(int &S, JumpLock &P)
{
    if(JumpDefine.count(S)==0)
        return false;
    else{
        P=JumpDefine[S];
        return true;
    }
}

#endif // BLOCKFLOW_H
