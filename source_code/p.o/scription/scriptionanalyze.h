#ifndef SCRIPTIONANALYZE_H
#define SCRIPTIONANALYZE_H
std::string AdressCount(std::string N,std::string T)
{
    for(std::string::reverse_iterator Po=N.rbegin();Po!=N.rend();++Po)
    {
        if(*Po=='/')
        {
            std::string C(N.begin(),++(Po.base()));
            C+=T;
            return C;
        }
    }
    return T;
}
template<class T> void Translate(const std::string& S,T& D){static std::stringstream SStream;SStream.clear();SStream<<S;SStream>>D;}
#endif // SCRIPTIONANALYZE_H
