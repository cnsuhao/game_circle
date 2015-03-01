#ifndef DIY_JIECAO_H
#define DIY_JIECAO_H
#include "tool.h"
class JieCao:public Tool
{
    long JC;

    public:
        void Analyze(void *,long);
};
void JieCao::Analyze(void *V,long T)
{
}
#endif // JIECAO_H
