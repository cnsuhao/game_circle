#ifndef LISTDATA_H
#define LISTDATA_H
#define POINT_V 1
#define POINT_VT 2
#define POINT_VTN 3
#define POINT_VC 4
#define POINT_VCN 5
#include "../p.o/scription/scriptionanalyze.h"
#include "../p.o/pobase/pomain.h"
class PointData
{
    int PointOrder;//1 means v, 2 means vt ,3 means vtn ,4 means vc, 5means vcn
    int VN;//Vector data number
    int CN;//Color Number
    int DN2;//DataNumber;
public:
    int DataNumber(){return DN2;}
    void CountDataNumber();
    int Order(){return PointOrder;}
    void SetOrder(const int& O){PointOrder=O;CountDataNumber();}
    void SetVector(const int &U){VN=U;CountDataNumber();}
    void SetColor(const int &U){CN=U;CountDataNumber();}
    bool HaveT(){return Order()==POINT_VT||Order()==POINT_VTN;}
    bool HaveC(){return Order()==POINT_VC||Order()==POINT_VCN;}
    bool HaveN(){return Order()==POINT_VCN||Order()==POINT_VTN;}
    int Texture(){return 2;}
    int Normal(){return 3;}
    int Vector(){return VN;}
    int Color(){return CN;}
    void SetDefault(){PointOrder=1;VN=2;CN=3;DN2=2;}
    PointData(){SetDefault();}
    PointData(const PointData& PD):PointOrder(PD.PointOrder),VN(PD.VN),CN(PD.CN),DN2(PD.DN2){}
    void CheckDetail(fstream& I);
};

class ListData:public PointData,public HandleSeed
{
    std::list<float> PD;
    std::list<unsigned int> OD;
    std::string PictureA;
public:
    Handle<GLTexture> PictureS;
    unsigned int PN;
    unsigned int DN;
    unsigned int Max;
    bool AddPoint(float*,const int& N);
    bool AddPoint(const unsigned int& T);
    bool CreatArray(float*& D);
    void Draw();
    void SetEnvironment();
    void RestoreEnvironment();
    void SetArray(float*);
    void Clean(){PD.clear();PN=0;}
    void Picture(const std::string& K){PictureA=K;}
    ListData():PN(0),DN(0),Max(0){SetDefault();}
    void CheckDetail(fstream &I);
    void Init(POMain*);
    void CleanUnused(){PD.clear();OD.clear();}
    ~ListData(){Error<<"Delete ListData "<<endl;}
};

void ListData::Init(POMain * P)
{
    if(HaveT())
    {
        PictureS=P->CreatPicture(PictureA);
        Error<<"Finish"<<endl;
    }
}


void ListData::Draw()
{
    if(Max<=PN-1&&PN>0)
    {
        float* VT,* CT,*TT,*NT;
        VT=new float[PN*Vector()];
        if(HaveC())
            CT=new float[PN*Color()];
        if(HaveT())
            TT=new float[PN*Texture()];
        if(HaveN())
            NT=new float[PN*Normal()];
        float* PVT=VT,* PCT=CT,*PTT=TT,*PNT=NT;
        int M=0,i=0;
        for(std::list<float>::iterator Po=PD.begin();Po!=PD.end();++Po)
        {
            if(M==0)
            {
                *PVT=*Po;++i;++PVT;
                if(i>=Vector())
                {
                    if(HaveC()||HaveT())++M;else{M=0;}i=0;
                }
            }else if(M==1)
            {
                if(HaveT())
                {
                    *PTT=*Po;++i;++PTT;
                    if(i>=Texture())
                    {
                        if(HaveN())++M;else{M=0;} i=0;
                    }
                }else if(HaveC()){
                    *PCT=*Po;++i;++PCT;
                    if(i>=Color())
                    {
                        if(HaveN())++M;else{M=0;}i=0;
                    }
                }
            }else if(M==2)
            {
                *PNT=*Po;++i;++PNT;
                if(i>=Normal()){M=0;i=0; }
            }
        }
        unsigned int* Order=new unsigned int[DN];
        i=0;
        for(std::list<unsigned int>::iterator Po=OD.begin();Po!=OD.end();++Po,++i)
        {
            Order[i]=*Po;
        }
        glVertexPointer(Vector(),GL_FLOAT,0,VT);

        if(HaveT())
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(Texture(),GL_FLOAT,0,TT);
            if(PictureS)
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,PictureS->Point);
            }
        }else if(HaveC())
        {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(Color(),GL_FLOAT,0,CT);
        }
        if(HaveN())
        {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT,0,NT);
        }
        glEnableClientState(GL_VERTEX_ARRAY);


        glDrawElements(GL_TRIANGLES,DN, GL_UNSIGNED_INT,Order);

        glDisableClientState(GL_VERTEX_ARRAY);
        if(HaveT())
        {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            if(PictureS)
                glDisable(GL_TEXTURE_2D);
        }
        if(HaveC()) glDisableClientState(GL_COLOR_ARRAY);
        if(HaveN()) glDisableClientState(GL_NORMAL_ARRAY);

        delete[] VT;
        if(HaveT()) delete[] TT;
        if(HaveC()) delete[] CT;
        if(HaveN()) delete[] NT;
        delete[] Order;
    }
}


void ListData::CheckDetail(fstream &I)
{
    PointData::CheckDetail(I);
    I<<"Using Picture <"<<PictureA<<">"<<endl<<"Point Data :"<<endl;
    int i=1;
    for(std::list<float>::iterator Po=PD.begin();Po!=PD.end();++Po,++i)
    {
        I<<" <"<<*Po<<"> ";
        if(i==DataNumber())
        {
            I<<endl;
            i=0;
        }
    }
    I<<endl;
    i=1;
    I<<"Draw Order :"<<endl;
    for(std::list<unsigned int >::iterator Po=OD.begin();Po!=OD.end();++Po,++i)
    {
        I<<*Po;
        if(i==3)
        {
            I<<endl;
            i=0;
        }
    }
}


void PointData::CheckDetail(fstream &I)
{
    I<<"Point Order <"<<PointOrder<<"> Color Number <"<<CN<<">"<<endl;
}


bool ListData::AddPoint(float* T,const int& P)
{
        for(int i=0;i<P;++i)
            PD.push_back(T[i]);
        PN+=1;
        return true;
}

bool ListData::AddPoint(const unsigned int& T)
{
    if(Max<T)
        Max=T;
    OD.push_back(T);
    ++DN;
    return true;
}

void ListData::SetEnvironment()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    if(HaveT())
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    /*if(!HaveC())
        glDisableClientState(GL_COLOR_ARRAY);*/
    if(HaveN())
        glEnableClientState(GL_NORMAL_ARRAY);
}

void ListData::RestoreEnvironment()
{
    glDisableClientState(GL_VERTEX_ARRAY);
    if(HaveT())
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    /*if(!HaveC())
        glEnableClientState(GL_COLOR_ARRAY);*/
    if(HaveN())
        glDisableClientState(GL_NORMAL_ARRAY);
}

void ListData::SetArray(float* K)
{
    if(Order()>=POINT_V&&PN>0)
    {
        Error<<"Size "<<sizeof(float)<<endl;
        glVertexPointer(Vector(),GL_FLOAT,12,K);
        if(HaveT())
        {
            glTexCoordPointer(Texture(),GL_FLOAT,(DataNumber()-Texture())*sizeof(GLfloat),K+Vector());
        }else if(HaveC())
        {
            glColorPointer(Color(),GL_FLOAT,12,K+Vector());
        }if(HaveN())
        {
            if(HaveT())
                glNormalPointer(GL_FLOAT,(DataNumber()-Normal())*sizeof(GLfloat),&K[Vector()+Texture()]);
            else if(HaveC())
                glNormalPointer(GL_FLOAT,(DataNumber()-Normal())*sizeof(GLfloat),&K[Vector()+Color()]);
        }
    }
}

bool ListData::CreatArray(float *&D)
{
    if(Order()>=POINT_V&&PN>0)
    {
        D=new float[PN*DataNumber()];
        int Cal=0;
        for(std::list<float>::iterator Po=PD.begin();Po!=PD.end();++Po,++Cal)
            D[Cal]=*Po;
        return true;
    }
    return false;
}

void PointData::CountDataNumber()
{
    switch(PointOrder)
    {
    case POINT_V:
        DN2=VN;
        break;
    case POINT_VT:
        DN2=VN+2;
        break;
    case POINT_VTN:
        DN2= VN+5;
        break;
    case POINT_VC:
        DN2= VN+CN;
        break;
    case POINT_VCN:
        DN2= VN+CN+3;
        break;
    default:
        DN2=0;
        break;
    }
}


#endif // LISTDATA_H
