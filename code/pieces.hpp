#ifndef __PIECES__
#define __PIECES__
// #include "common.hpp"
#include "point.hpp"


class Shape {
    protected:
        Point _center;
        std::vector<int> _color=std::vector<int>(3);
        std::vector<Point> _distribution=std::vector<Point>(3);
        bool _can_move;

    public:
        Shape();
        bool get_can_move() const;
        void change_status();
        void move_right();
        void move_left();
        void move_down();
        Point get_center() const;
        std::vector<Point> get_distribution() const;
        std::vector<int> get_color() const;
        Point  get_distribution_i(int i) const;
        virtual void rotate_left() = 0;
        virtual void rotate_right() = 0;
        virtual ~Shape() {}

};

class I : public Shape {
    public :
        I();
        void rotate_left();
        void rotate_right();
    
};

class J : public Shape {
    public :
        J();
        void rotate_left();
        void rotate_right();
    
};

class O : public Shape {
    public :
        O();
        void rotate_left();
        void rotate_right();
};

class L : public Shape {
    public :
        L();
        void rotate_left();
        void rotate_right();
};

class T : public Shape {
    public :
        T();
        void rotate_left();
        void rotate_right();
};

class Z : public Shape {
    public :
        Z();
        void rotate_left();
        void rotate_right();
};

class S : public Shape {
    public :
        S();
        void rotate_left();
        void rotate_right();
};

Shape new_piece();



#endif