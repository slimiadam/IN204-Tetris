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
        Shape (Shape const& piece) = default ; 

    public:
        Shape();
        
        bool get_can_move() const;
        void change_center(int x, int y);
        void change_status();
        void move_right();
        void move_left();
        void move_down();
        Point get_center() const;
        std::vector<Point> get_distribution() const;
        std::vector<int> get_color() const;
        Point  get_distribution_i(int i) const;
        void rotate_left();
        void rotate_right();
        virtual Shape* cloner() const = 0 ;
        virtual ~Shape() {}

};

class I : public Shape {
    public :
        I();
       // void rotate_left();
       // void rotate_right();
    
};

class J : public Shape {
    public :
        J();
       // void rotate_left();
        //void rotate_right();
    
};

class O : public Shape {
    public :
        O();
        //void rotate_left();
        //void rotate_right();
};

class L : public Shape {
    protected:
        L(const L&) = default;
    public :
        L();
        //void rotate_left();
        //void rotate_right();
        L* cloner() const {
      return new L{*this};
   }
};

class T : public Shape {
    public :
        T();
        //void rotate_left();
        //void rotate_right();
};

class Z : public Shape {
    public :
        Z();
       // void rotate_left();
        //void rotate_right();
};

class S : public Shape {
    public :
        S();
       // void rotate_left();
         //void rotate_right();
};

Shape::Ptr new_piece();



#endif