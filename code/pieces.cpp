#include "pieces.hpp"


// Constructor
Shape :: Shape() : _center(Point(-1,-1)), _can_move(true){
    _color[0]=(0);
    _color[1]=(0);
    _color[2]=(0);
    _distribution[0]=Point(-1,-1);
    _distribution[1]=Point(-1,-1);
    _distribution[2]=Point(-1,-1);

};

bool Shape::get_can_move()const{
    return _can_move;
}
void Shape::change_status(){
    _can_move=false;
}

Point Shape:: get_center()const{
    return _center;
}
std::vector<Point> Shape:: get_distribution() const {
    return _distribution;
}
Point Shape :: get_distribution_i(int i) const {
    return _distribution[i];
}
std::vector<int> Shape :: get_color() const {
    return _color;
};

void Shape :: move_right(){
    _center=Point(_center.get_x()+1,_center.get_y());
}
void Shape :: move_left(){
    _center=Point(_center.get_x()-1,_center.get_y());
}
void Shape :: move_down() {
    _center=Point(_center.get_x(),_center.get_y()-1);
}

I :: I() : Shape(){
    _color[0]=(248);
    _color[1]=(248);
    _color[2]=(121);
    _distribution[0]=Point(2,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(-1,0);
};

void I :: rotate_right(){
    _distribution[0]=Point(0,-2);
    _distribution[1]=Point(0,-1);
    _distribution[2]=Point(0,1);
}

void I::rotate_left() {
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(0,-1);
}

J:: J() : Shape(){
    _color[0]=(36);
    _color[1]=(201);
    _color[2]=(52);
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};

void J::rotate_right(){
    _distribution[0]=Point(2,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,1);
}

void J::rotate_left(){
    _distribution[0]=Point(-2,0);
    _distribution[1]=Point(-1,0);
    _distribution[2]=Point(0,-1);
}

O :: O() : Shape(){
    _color[0]=0;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

void O::rotate_right(){
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
}
void O::rotate_left(){
    rotate_right();
}

L :: L() : Shape(){
    _color[0]=21;
    _color[1]=1;
    _color[2]=217;
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

void L :: rotate_right() {
    _distribution[0]=Point(2,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,-1);
}
void L :: rotate_left() {
    _distribution[0]=Point(-2,0);
    _distribution[1]=Point(-1,0);
    _distribution[2]=Point(0,1);
}

S :: S() : Shape(){
    _color[0]=255;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};

void S :: rotate_right() {
    _distribution[0]=Point(-1,-1);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,1);
}
void S :: rotate_left() {
    _distribution[0]=Point(-1,1);
    _distribution[1]=Point(-1,0);
    _distribution[2]=Point(0,-1);
}

Z :: Z() : Shape(){
    _color[0]=255;
    _color[1]=0;
    _color[2]=255;
    _distribution[0]=Point(-1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};
void Z :: rotate_right() {
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,-1);
}
void Z :: rotate_left() {
    _distribution[0]=Point(-1,-1);
    _distribution[1]=Point(-1,0);
    _distribution[2]=Point(0,1);
}

T :: T() : Shape(){
    _color[0]=0;
    _color[1]=127;
    _color[2]=255;
    _distribution[0]=Point(-1,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,1);
};
void T::rotate_right(){
    _distribution[0]=Point(0,1);
    _distribution[1]=Point(0,-1);
    _distribution[2]=Point(1,0); 
}
void T::rotate_left(){
    _distribution[0]=Point(0,-1);
    _distribution[1]=Point(0,11);
    _distribution[2]=Point(-1,0); 
}

Shape new_piece(){
    int randNum = rand()%(7);
    switch(randNum){
        case 0 : return I();
        case 1 : return J();
        case 2 : return O();
        case 3 : return T();
        case 4 : return L();
        case 5 : return Z();
        case 6 : return S();
    }
}