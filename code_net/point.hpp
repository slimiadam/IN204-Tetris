#ifndef CODE__POINT__HPP
#define CODE__POINT__HPP
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

class Point {
    protected :
    int x;
    int y; 

    public:
    //Constructors 
    Point() ;
    Point(int a, int b);
    bool operator==(Point other);
    bool operator!=(Point other);
    Point operator+=(Point other) ;
    friend std::ostream& operator<<( std::ostream &flux, Point a);
    int get_x() const;
    int get_y() const;
};

Point operator+(Point first, Point second);
std::ostream& operator<<( std::ostream &flux, Point a);

#endif
