#include "objeto.h"
#include<cmath>

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
    triangulo *F = new triangulo(this->points.at(iP1),this->points.at(iP2),this->points.at(iP3));
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
