#include "poligono.h"


void Poligono::trocar(int i, int j) {

    int N = this->points.size();
    if(i>=0 && j < N){
        Coord_2D* z = new Coord_2D(this->points.at(i)->x,this->points.at(i)->y);
        this->points.at(i)->x = this->points.at(j)->x;
        this->points.at(i)->y = this->points.at(j)->y;
        this->points.at(j)->x = z->x;
        this->points.at(j)->y = z->y;
       }

}
int Poligono::Particione_X(int p, int r) {
    float pivo = this->points.at(r)->x;
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (this->points.at(j)->x <= pivo) {
            i++;
            this->trocar(i,j);
        }
    }
    this->trocar(i+1, r);
    return i+1;
}
int Poligono::Particione_Y(int p, int r) {
    float pivo = this->points.at(r)->y;
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (this->points.at(j)->y <= pivo) {
            i++;
            this->trocar(i,j);
        }
    }
    this->trocar(i+1, r);
    return i+1;
}
int Poligono::Particione_aleat(int p, int r, bool eixo) {
    srand (time(NULL));
    int pos_pivo = p + rand()%(r-p+1);
    this->trocar(pos_pivo,r);
    if(eixo)
        return Particione_Y(p,r);
    else
        return Particione_X(p,r);
}
void Poligono::QuickSort(int p, int r, bool eixo) {
    if (p>=r) return;
    int q = Particione_aleat(p,r,eixo);
    QuickSort(p,q-1,eixo);
    QuickSort(q+1,r,eixo);
}


Poligono::Poligono()
{

}

void Poligono::addPoint(float x, float y){
    Coord_2D* novo = new Coord_2D(x,y);
    this->points.push_back(novo);
}


Coord_2D Poligono::Centro(){

    float mX, mY, MX, MY;
    mX = MX = this->points.at(0)->x;
    mY = MY = this->points.at(0)->y;

    for(std::vector<Coord_2D*>::iterator i = this->points.begin(); i!= this->points.end(); i++){
        float x,y;
        x = (*i)->x; y = (*i)->y;

        if(x<mX)
            mX = x;
        if(x>MX)
            MX = x;
        if(y<mY)
            mY = y;
        if(y>MY)
            MY = y;
    }
    Coord_2D c(((mX+MX)/2),((mY+MY)/2));
    return c;

}
int Poligono::MaiorX(){
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
int Poligono::MenorX(){
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
int Poligono::MaiorY(){
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
int Poligono::MenorY(){
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


void Poligono::Imp(){
    for(std::vector<Coord_2D*>::iterator i = this->points.begin(); i!= this->points.end(); i++)
        (*i)->ImpCoord_2D();
}


void Poligono::Ordena(bool eixo){
    int N = this->points.size();
    QuickSort(0, (N-1),eixo);
}


