#include "pieces.hpp"

// Constructor
Shape :: Shape() : _center(-1,-1)
{
    _color[0]=(0);
    _color[1]=(0);
    _color[2]=(0);
    _distribution[0]=Point(-1,-1);
    _distribution[1]=Point(-1,-1);
    _distribution[2]=Point(-1,-1);
};
I::I() : _center[0](-1), _center[1](-1),_color[0](248), _color[1](248), _color[2](121), distribution[0](2), distribution[1](0), distribution[2](1) ,distribution[3](0), distribution[4](-1), distribution[5](0);
{}
I :: I() : _center(-1,-1)
{
    _color[0]=(248);
    _color[1]=(248);
    _color[2]=(121);
    _distribution[0]=Point(2,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(-1,0);
};

J:: J() : _center(-1,-1)
{
    _color[0]=(36);
    _color[1]=(201);
    _color[2]=(52);
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};

O :: O() : _center(-1,-1);
{
    _color[0]=0;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

L :: L() : _center(-1,-1)
{
    _color[0]=21;
    _color[1]=1;
    _color[2]=217;
    _distribution[0]=Point(0,2);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

S :: S() : _center(-1,-1)
{
    _color[0]=255;
    _color[1]=255;
    _color[2]=255;
    _distribution[0]=Point(1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(-1,0);
};

Z :: Z() : _center(-1,-1)
{
    _color[0]=255;
    _color[1]=0;
    _color[2]=255;
    _distribution[0]=Point(-1,1);
    _distribution[1]=Point(0,1);
    _distribution[2]=Point(1,0);
};

T :: T() : _center(-1,-1)
{
    _color[0]=0;
    _color[1]=127;
    _color[2]=255;
    _distribution[0]=Point(-1,0);
    _distribution[1]=Point(1,0);
    _distribution[2]=Point(0,1);
};
