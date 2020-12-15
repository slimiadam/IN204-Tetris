#ifndef __PIECES__
#define __PIECES__
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "point.hpp"


class Shape {
    protected:
        Point _center;
        std::vector<int> _color=std::vector<int>(3);
        std::vector<Point> _distribution=std::vector<Point>(3);

    public:
        Shape();
        
        void move_right();
        void move_left();
        void move_down();
        Point get_center();
        virtual void rotate_left() = 0;
        virtual void rotate_right() = 0;
        virtual ~Shape() {}

};

class I : public Shape {
    public :
        I();
        void rotate_left() {}
        void rotate_right() {}
    
};

class J : public Shape {
    public :
        J();
        virtual void rotate_left() {}
        virtual void rotate_right(){}
    
};

class O : public Shape {
    public :
        O();
        virtual void rotate_left() {}
        virtual void rotate_right(){}
    
};

class L : public Shape {
    public :
        L();
        virtual void rotate_left(){}
        virtual void rotate_right(){}
    
};

class T : public Shape {
    public :
        T();
        virtual void rotate_left() {}
        virtual void rotate_right(){}
    
};

class Z : public Shape {
    public :
        Z();
        virtual void rotate_left(){}
        virtual void rotate_right(){}
    
};

class S : public Shape {
    public :
        S();
        virtual void rotate_left(){}
        virtual void rotate_right(){}
    
};



#endif