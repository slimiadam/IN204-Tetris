#include "pieces.hpp"
#include "point.hpp"

// Constructor
Shape :: Shape() : _center(Point(-1,-1))
{
    _color[0]=(0);
    _color[1]=(0);
    _color[2]=(0);
    _distribution[0]=Point(-1,-1);
    _distribution[1]=Point(-1,-1);
    _distribution[2]=Point(-1,-1);
};

Point Shape:: get_center(){
    return _center;
}

/*void Shape :: move_right(Grid grid){
    grid.delete_piece(*this);
    int ok = 1;
    if (grid._grid[_center.get_x()+ 1][_center.get_y()].is_occupied){
        ok = 0;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        if (grid._grid[_center.get_x() +_distribution[i].get_x()+ 1][_center.get_y()+_distribution[i].get_y()].is_occupied){
            ok = 0;
        }
        i++;
        }
    }
    if (ok) {
        _center.
        grid.add_piece(*this);

    }
};*/
void Shape :: move_right(){
    _center=Point(_center.get_x()+1,_center.get_y());
}
void Shape :: move_left(){
    _center=Point(_center.get_x()-1,_center.get_y());
}
void Shape :: move_down() {
    _center=Point(_center.get_x(),_center.get_y()-1);
}
I :: I() : Shape()
{
    _color[0]=(248);
    _color[1]=(248);
    _color[2]=(121);
    _distribution[0]=Point(2,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(-1,0);
};

J:: J() : Shape()
{
    _color[0]=(36);
    _color[1]=(201);
    _color[2]=(52);
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};

O :: O() : Shape()
{
    _color[0]=0;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

L :: L() : Shape()
{
    _color[0]=21;
    _color[1]=1;
    _color[2]=217;
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

S :: S() : Shape()
{
    _color[0]=255;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};

Z :: Z() : Shape()
{
    _color[0]=255;
    _color[1]=0;
    _color[2]=255;
    _distribution[0]=Point(-1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

T :: T() : Shape()
{
    _color[0]=0;
    _color[1]=127;
    _color[2]=255;
    _distribution[0]=Point(-1,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,1);
};
