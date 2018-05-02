#include "objeto.h"
#include<cmath>



void trocar(std::vector<Coord_3D*> vetor, int i, int j) {

    int N = vetor.size();

    if(i>=0 && j < N){
        Coord_3D* aux = new Coord_3D(vetor.at(i)->x,vetor.at(i)->y, vetor.at(i)->z);

        vetor.at(i)->x = vetor.at(j)->x;
        vetor.at(i)->y = vetor.at(j)->y;
        vetor.at(i)->z = vetor.at(j)->z;

        vetor.at(j)->x = aux->x;
        vetor.at(j)->y = aux->y;
        vetor.at(j)->z = aux->z;
    }

}
int Particione_X(std::vector<Coord_3D*> vetor, int p, int r) {
    float pivo = vetor.at(r)->x;
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (vetor.at(j)->x <= pivo) {
            i++;
            trocar(vetor,i,j);
        }
    }
    trocar(vetor,i+1, r);
    return i+1;
}
int Particione_Y(std::vector<Coord_3D*> vetor, int p, int r) {
    float pivo = vetor.at(r)->y;
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (vetor.at(j)->y <= pivo) {
            i++;
            trocar(vetor,i,j);
        }
    }
    trocar(vetor,i+1, r);
    return i+1;
}
int Particione_Z(std::vector<Coord_3D*> vetor, int p, int r) {
    float pivo = vetor.at(r)->z;
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (vetor.at(j)->z <= pivo) {
            i++;
            trocar(vetor,i,j);
        }
    }
    trocar(vetor,i+1, r);
    return i+1;
}
int Particione_aleat(std::vector<Coord_3D*> vetor, int p, int r, int eixo) {
    srand (time(NULL));
    int pos_pivo = p + rand()%(r-p+1);
    trocar(vetor,pos_pivo,r);

    if(eixo == 0)
        return Particione_X(vetor,p,r);
    if(eixo == 1)
        return Particione_Y(vetor,p,r);

    return Particione_Z(vetor,p,r);

}
void QuickSort(std::vector<Coord_3D*> vetor, int p, int r, int eixo) {
    if (p>=r) return;
    int q = Particione_aleat(vetor,p,r,eixo);
    QuickSort(vetor,p,q-1,eixo);
    QuickSort(vetor,q+1,r,eixo);
}

Objeto::Objeto()
{
    Coord_3D C(0,0,0);
    this->Esf.centro=C;
    this->Esf.raio=0;
}
void Objeto::addPoint(float x, float y, float z){
    Coord_3D *p = new Coord_3D(x,y,z);
    this->points.push_back(p);

}
void Objeto::addFace(int iP1, int iP2, int iP3){
    //triangulo *F = new triangulo(this->points.at(iP1),this->points.at(iP2),this->points.at(iP3));
    Face *F = new Face(iP1, iP2, iP3);
    this->faces.push_back(F);
}
void Objeto::calc_Esfera(){
    float mX=this->points.at(0)->x;
    float mY=this->points.at(0)->y;
    float mZ=this->points.at(0)->z;
    float MX=mX;float MY=mY;float MZ=mZ;
    for(std::vector<Coord_3D*>::iterator i = this->points.begin(); i!= this->points.end(); i++)
    {
        float x = (*i)->x;float y = (*i)->y;float z = (*i)->z;
        if(x<mX)
            mX = x;
        if(x>MX)
            MX = x;
        if(y<mY)
            mY = y;
        if(y>MY)
            MY = y;
        if(z<mZ)
            mZ = z;
        if(z>MZ)
            MZ = z;
    }
    Coord_3D _centro((MX+mX)/2,(MY+mY)/2,(MZ+mZ)/2);
    this->Esf.centro=_centro;
    float dx = std::abs(MX)+std::abs(mX);
    float dy = std::abs(MY)+std::abs(mY);
    float dz = std::abs(MZ)+std::abs(mZ);


    float d = 0;
    if(dx>dy && dx>dz)
            d = dx;
        else if(dy>dz)
            d = dy;
        else
            d = dz;

    this->Esf.raio=(d/2);

}
void Objeto::Ordena(int eixo){
    int N = this->points.size();
    QuickSort(this->points, 0, N-1, eixo);
}
void Objeto::ImpPoints(){
    std::cout << "\n Imprimindo Pontos do Objeto: \n";
    for(std::vector<Coord_3D*>::iterator i = this->points.begin(); i!= this->points.end(); i++)
    {
        Coord_3D *P = (*i);
        std::cout << "\nx,y,z = " << P->x << ", " << P->y << ", " << P->z <<";";

    }
    cout << endl;

}
void Objeto::ImpFaces(){
    std::cout << "\n Imprimindo "<< faces.size() << " Faces do Objeto: \n";
    for(std::vector<Face*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++)

        std::cout << "\nP1,P2,P3 = " << (*i)->P1 << ", " << (*i)->P2 << ", " << (*i)->P3 <<";";

    cout << endl;
}

int Objeto::MaiorX(){
    float MX = this->points.at(0)->x;
    int ind = 0;
    int N = points.size();
    for(int i=1; i < N;i++){
        float x = this->points.at(i)->x;
        if(x>MX){
            MX = x;
            ind=i;
        }
    }
    return ind;
}
int Objeto::MenorX(){
    float MX = this->points.at(0)->x;
    int ind = 0;
    int N = points.size();
    for(int i=1; i < N;i++){
        float x = this->points.at(i)->x;
        if(x<MX){
            MX = x;
            ind=i;
        }
    }
    return ind;
}
int Objeto::MaiorY(){
    float MY = this->points.at(0)->y;
    int ind = 0;
    int N = points.size();
    for(int i=1; i < N;i++){
        float y = this->points.at(i)->y;
        if(y>MY){
            MY = y;
            ind=i;
        }
    }
    return ind;
}
int Objeto::MenorY(){
    float MY = this->points.at(0)->y;
    int ind = 0;
    int N = points.size();
    for(int i=1; i < N;i++){
        float y = this->points.at(i)->y;
        if(y<MY){
            MY = y;
            ind=i;
        }
    }
    return ind;
}
int Objeto::MaiorZ(){
    float MZ = this->points.at(0)->z;
    int ind = 0;
    int N = points.size();
    for(int i=1; i < N;i++){
        float z = this->points.at(i)->z;
        if(z>MZ){
            MZ = z;
            ind=i;
        }
    }
    return ind;
}
int Objeto::MenorZ(){
    float MZ = this->points.at(0)->z;
    int ind = 0;
    int N = points.size();
    for(int i=1; i < N;i++){
        float z = this->points.at(i)->z;
        if(z<MZ){
            MZ = z;
            ind=i;
        }
    }
    return ind;
}

void Objeto::CopiaPontos(Objeto *O){

    for(std::vector<Coord_3D*>::iterator i = O->points.begin(); i!= O->points.end(); i++)
    {
        addPoint((*i)->x,(*i)->y,(*i)->z);
    }
}

Coord_3D Objeto::Centro(){
    int N = points.size();
    float dX=0, dY=0, dZ=0;
    for(int i=0; i<N;i++){
        dX+=points.at(i)->x;
        dY+=points.at(i)->y;
        dZ+=points.at(i)->z;
    }
    dX/=N;
    dY/=N;
    dZ/=N;

    Coord_3D C(dX,dY,dZ);
    return C;

}

bool Objeto::Pertence(int iP1, int iP2, int iP3){

        Coord_3D* a = this->points.at(iP1);
        Coord_3D* b = this->points.at(iP2);
        Coord_3D* c = this->points.at(iP3);

        Coord_3D nF = Normal(a,b,c);

        int Ind = -1;
        int N = this->points.size();
        for(int i=0; i < N;i++){
                Coord_3D temp = *(this->points.at(i));
                temp.operator -=(a);
                float pE = ProdutoEscalar3D(temp, nF);

                if(pE>0){
                    Ind = i;
                    break;
                }
            }
        if(Ind == -1)
            return true;
        return false;

    }


    //    //bool aux = false;

//    int AB=0, AC=0, BC=0;

//    for(std::vector<Face*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++){
//        int tP1, tP2, tP3;
//        tP1 = (*i)->P1;
//        tP2 = (*i)->P2;
//        tP3 = (*i)->P3;

//        bool C1 = (iP1 == tP1 || iP1 == tP2 || iP1 == tP3);
//        bool C2 = (iP2 == tP1 || iP2 == tP2 || iP2 == tP3);
//        bool C3 = (iP3 == tP1 || iP3 == tP2 || iP3 == tP3);


//        if(C1 && C2 && C3)
//            pertence = true;

////        if(C1 && C2)
////            AB++;
////        if(C1 && C3)
////            AC++;
////        if(C2 && C3)
////            BC++;

////        if((AB >=  2 || AC >=2 || BC >=2)){
////            pertence = true;
//////            aux = true;
//////        cout<< endl << "Teste Correspondetes AB AC BC para os índices IA,IB,IC" << iP1 << iP2 << iP3 << endl;
//////        cout<< AB << AC << BC <<endl;
//////        cout<< pertence<< endl;
////        }

//    }


/*
float Objeto::Ray_intersept(Coord_3D Po, Coord_3D Dir, int *iFace){

    float t = -1;
    float Menor_T=9999;
    int cont=0;

    if(this->Esf.Interseccao(Dir)){
        for(std::vector<triangulo*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++){
            float x = (*i)->Ray_intersept(Po, Dir);
            if(x != -1 && x<Menor_T){
                Menor_T = x;
                (*iFace) = cont;
            }
            cont++;
        }
        if(Menor_T != 999)
            t=Menor_T;
    }

    return t;
}

bool Objeto::Tiro(Coord_3D Ponto){

    bool Interno = false;
    int cont=0;

        for(std::vector<triangulo*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++){


            float u=0; float v=0; float w=0;
            (*i)->Barycentric(&Ponto, u, v, w);
             //cout << u << " : "<< v << " : "<< w << endl;
            if((u >=0 || u <=1)&&(v >=0 || v <=1)&&(w >=0 || w <=1)){
               cont++;
            }
        }

    //cout<<"Teste" << cont << endl;

    if(cont%2!=0)
        Interno=true;

    return Interno;
}

void Objeto::Transforoma(float A[TAM][TAM]){
    transformacoes t;
    for(std::vector<Coord_3D*>::iterator i = this->points.begin(); i!= this->points.end(); i++){
        t.MxV(A,(*i));
    }
    this->calc_Esfera();
}

void Objeto::ImpPoints(){
    std::cout << "\n Imprimindo Pontos do Objeto: \n";
    for(std::vector<Coord_3D*>::iterator i = this->points.begin(); i!= this->points.end(); i++)
    {
        Coord_3D *P = (*i);
        std::cout << "\nx,y,z = " << P->x << ", " << P->y << ", " << P->z <<";";

    }

}


bool Objeto::Obstaculo(Coord_3D Pint, Coord_3D l){

    if(this->Esf.Interseccao(Pint)){
        for(std::vector<triangulo*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++){
            float t = (*i)->Ray_intersept(Pint, l);
            if(t != -1 && t>0){
                return true;
            }
        }
    }
    return false;
}

void Objeto::Libera(){
    for(std::vector<Coord_3D*>::iterator i = this->points.begin(); i!= this->points.end(); i++)
    {
        free(*i);
        (*i)=NULL;
    }
    for(std::vector<triangulo*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++){
        (*i)->P1=NULL;
        (*i)->P2=NULL;
        (*i)->P3=NULL;
        free(*i);
        (*i)=NULL;
    }
}
*/
