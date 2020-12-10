#include "point.hpp"


//Constructeur 
Point :: Point() : x(0), y(0) {}; 
Point :: Point(int x, int y) : x(x), y(y) {};

//Operator
bool Point:: operator==(Point other){
    return (x==other.x && y==other.y);
};
bool Point :: operator!=(Point other){
    return !(*this==other);
};
Point Point :: operator+=(Point other){
    x += other.x;
    y += other.y;
    return *this;
};

Point operator+(Point first, Point second){
    return first+=second;
};
std::ostream& operator<<( std::ostream &flux, Point a){
    flux<< "(" << a.x << " , " << a.y << ")";
    return flux;
}
