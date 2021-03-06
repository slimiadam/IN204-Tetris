#include "pieces.hpp"
#include "point.hpp"
#include <algorithm>

void Shape::operator=(Shape::Ptr other) {
    _center = other->get_center();
    _can_move = other->get_can_move();
    _color =  other->get_color();
    _distribution = other->_distribution;
}
// Constructor
Shape :: Shape() : _center(Point(-1,-1)),_can_move(true){
    
    _color[0]=(0);
    _color[1]=(0);
    _color[2]=(0);
    _distribution[0]=Point(-1,-1);
    _distribution[1]=Point(-1,-1);
    _distribution[2]=Point(-1,-1);

}



bool Shape::get_can_move() const{
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
    _center=Point(_center.get_x(),_center.get_y()+1);
}
void Shape :: move_left(){
    _center=Point(_center.get_x(),_center.get_y()-1);
}
void Shape :: move_down() {
    _center=Point(_center.get_x()-1,_center.get_y());
}
void Shape :: change_center(int x, int y) {
    _center=Point(x,y);
}
int Shape :: get_height(){
    int h=21;
    std::vector<int> heights {_center.get_x(), _center.get_x() + _distribution[0].get_x(), _center.get_x() + _distribution[1].get_x(), _center.get_x() + _distribution[2].get_x()};
    h=*std::max_element(heights.begin(), heights.end());
    return(h);
}

void Shape ::  rotate_right(){
    int x_tmp, y_tmp;
    for (int i =0 ; i < 3; i++){
        x_tmp = _distribution[i].get_x();
        y_tmp = _distribution[i].get_y();
        if (x_tmp*y_tmp == 0){
            _distribution[i]= Point( -y_tmp, x_tmp);
        }
        else if (x_tmp*y_tmp == 1){
             _distribution[i]= Point( -x_tmp, y_tmp);
        }
        else if (x_tmp*y_tmp == -1){
             _distribution[i]= Point( x_tmp, -y_tmp);
        }
    }
}

void Shape ::  rotate_left(){
    rotate_right();
    rotate_right();
    rotate_right();
}


I :: I() : Shape(){
    _color[0]=(220);
    _color[1]=(50);
    _color[2]=(50);
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(0,-1);
};

J:: J() : Shape(){
    _color[0]=(36);
    _color[1]=(201);
    _color[2]=(52);
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};

O :: O() : Shape(){
    _color[0]=0;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

L :: L() : Shape(){
    _color[0]=21;
    _color[1]=1;
    _color[2]=217;
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
}
S :: S() : Shape(){
    _color[0]=255;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};
Z :: Z() : Shape(){
    _color[0]=255;
    _color[1]=0;
    _color[2]=255;
    _distribution[0]=Point(-1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

T :: T() : Shape(){
    _color[0]=0;
    _color[1]=127;
    _color[2]=255;
    _distribution[0]=Point(-1,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,1);
};


Shape::Ptr new_piece(char piece){
    int randNum = rand()%(7);
    switch(piece){
        case 'I' : return Shape::Ptr(new I());
        case 'J' : return Shape::Ptr(new J());
        case 'O': return Shape::Ptr(new O());
        case 'T' : return Shape::Ptr(new T());
        case 'L': return Shape::Ptr(new L());
        case 'Z' : return Shape::Ptr(new Z());
        case 'S' : return Shape::Ptr(new S());
        default : return Shape::Ptr(new I());
    }
}