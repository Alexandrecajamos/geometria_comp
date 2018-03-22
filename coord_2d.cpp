#include "coord_2d.h"

Coord_2D::Coord_2D()
{

}
Coord_2D::Coord_2D(float _x, float _y) {
    this->x = _x;
    this->y = _y;
}

float Coord_2D::Produto_Escalar_Vetor(Coord_2D *C){
    float x= (this->x*C->x)+(this->y*C->y);
    return x;
}
void Coord_2D::ImpCoord_2D(){
    std::cout << "\nCoor.: " << this->x <<", "<< this->y<<"; "<< endl;
}

float Coord_2D::Distancia_Vetor(Coord_2D *B){
    Coord_2D C(this->x,this->y);
    C.operator -=(B);
    float Dis = C.norma_Vetor();;
    return Dis;
}

float Coord_2D::Angulo_Vetor(Coord_2D *C2){
    float PE = this->Produto_Escalar_Vetor(C2);
    float n1 = this->norma_Vetor();
    float n2 = C2->norma_Vetor();
    return acos(PE/(n1*n2))* 180.0 / PI;
}

float Coord_2D::Angulo_Orientado_Vetor(){
    Coord_2D U(1,0);
    float ang = this->Angulo_Vetor(&U);

    if(this->y>=0)
        return ang;
    else
        return (360-ang);

}

float Coord_2D::Pseudo_Ang_Quad(){
    if(y >=0){
        if(x >=0){
            if(x>=y)
                return y/x;
            return (2 - (x/y));
        }
        if(-x <= y)
            return (2 + ((-x)/y));
        return (4-(y/(-x)));
    }
    if(x<=0){
        if(-x>=-y)
            return (4+ ((-y)/(-x)));
        return (6- ((-x)/(-y)));
    }
    if(x<=-y)
        return (6+ (x/(-y)));
    return (8 - ((-y)/x));


}






/*Coord_2D* Coord_2D::Produto_Vetorial(Coord_2D *B){

    float x=0,y=0;
    Coord_2D *PV = new Coord_2D(x,y);
    return PV;
}

*/

