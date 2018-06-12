#include "objeto.h"

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
void Objeto::addSimplex(int A, int B, int C, int D){
    Simplex *S = new Simplex(A,B,C,D);
    this->simplex.push_back(S);
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
float Objeto::Area_Externa(){
    float area = 0;


    for(std::vector<Face*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++){
        Face *F = *i;
        Coord_3D NF = Normal(this->points.at(F->P1),this->points.at(F->P2),this->points.at(F->P3));
        float aT = NormaVetor3D(NF)/2;
        area+=aT;
     }
    return area;

}
float Objeto::Volume(){
    float Vol = 0;

    for(std::vector<Face*>::iterator i = this->faces.begin(); i!= this->faces.end(); i++){
        Face *F = *i;
        Coord_3D NF = Normal(this->points.at(F->P1),this->points.at(F->P2),this->points.at(F->P3));
        float T = ProdutoEscalar3D(NF,*(this->points.at(F->P1)));
        Vol+=T;
     }
    Vol/=3;
    return Vol;

}

