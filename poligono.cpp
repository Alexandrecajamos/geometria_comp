#include "poligono.h"

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


