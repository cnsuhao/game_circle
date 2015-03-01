#ifndef STATEMENT_H
#define STATEMENT_H
#include "scenedata.h"
class Statement
{
    ScriptionBlock SB;
    CommentPoint CP;
public:
    Statement(FileFactorPoint S,FileFactorPoint E):SB(S,E){CP=SB.Begin();}
    Statement(){CP=SB.Begin();}
    void Set(FileFactorPoint S,FileFactorPoint E){SB.Set(S,E);}
    virtual void ScriptionCheck(){}
    virtual void CheckDetail(std::fstream & K){}
    virtual bool Run(SceneData*,SceneBase*){}
    virtual void Clid(){}
    virtual void Up(){}
    virtual void Down(){}
    virtual void Mouse(float X,float Y){}
};

class IfStatement:public Statement
{
    bool True;
    Statement Ex;
    FileFactorPoint SB;
    FileFactorPoint SE;
public:
    virtual bool Run(SceneData *,SceneBase*){}
};
class ChooseStatement:public Statement
{
    std::vector<Statement> ChooseBlock;
public:
    virtual bool Run(SceneData *,SceneBase*){}
};

#endif // STATEMENT_H
