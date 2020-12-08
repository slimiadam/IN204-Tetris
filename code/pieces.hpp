#ifndef __PIECES__
#define __PIECES__

#include <vector>


class Shape {
    protected:
        std::vector<int> _center(2);
        std::vector<int> _color(3);
        std::vector<int> _distribution(6);

    public:
        Shape();
        void move_right();
        void move_left();
        void move_down();
        virtual void rotate_left() = 0;
        virtual void rotate_right() = 0;

};

class I : public Shape {
    public :
        I();
        virtual void rotate_left();
        virtual void rotate_right();
    
}

class J : public Shape {
    public :
        J();
        virtual void rotate_left();
        virtual void rotate_right();
    
}

class O : public Shape {
    public :
        O();
        virtual void rotate_left();
        virtual void rotate_right();
    
}

class L : public Shape {
    public :
        L();
        virtual void rotate_left();
        virtual void rotate_right();
    
}

class T : public Shape {
    public :
        T();
        virtual void rotate_left();
        virtual void rotate_right();
    
}

class Z : public Shape {
    public :
        Z();
        virtual void rotate_left();
        virtual void rotate_right();
    
}

class S : public Shape {
    public :
        S();
        virtual void rotate_left();
        virtual void rotate_right();
    
}





#endif