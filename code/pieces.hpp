#ifndef CODE__PIECES__HPP
#define CODE__PIECES__HPP
// #include "common.hpp"
#include "point.hpp"
#include <memory>

class Shape {
    public:
        typedef std::shared_ptr<Shape> Ptr;

    protected:
        Point _center;
        std::vector<int> _color=std::vector<int>(3);
        std::vector<Point> _distribution=std::vector<Point>(3);
        bool _can_move;

    public:
        Shape();
        
        bool get_can_move() const;
        void change_center(int x, int y);
        void change_status();
        void move_right();
        void move_left();
        void move_down();
        Point get_center() const;
        void operator=(Shape::Ptr other) ;
        std::vector<Point> get_distribution() const;
        std::vector<int> get_color() const;
        Point  get_distribution_i(int i) const;
        void rotate_left();
        void rotate_right();
        int get_height();
        virtual ~Shape() {}

};

class I : public Shape {

    public :
        I();

    
};

class J : public Shape {

    public :
        J();

    
};

class O : public Shape {

    public :
        O();

};

class L : public Shape {

    public :
        L();
};

class T : public Shape {

    public :
        T();

};

class Z : public Shape {

    public :
        Z();

};

class S : public Shape {
    public :
        S();
};

Shape::Ptr new_piece();



#endif