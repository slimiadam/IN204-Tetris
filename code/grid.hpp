#ifndef __GRID__
#define __GRID__
#include <vector>
#include  "pieces.hpp"
#define HEIGHT 22
#define WIDTH  10

class Box {
    private:
    bool _occupied ; //false if empty
    std::vector<int> _color =std::vector<int>(3);

    public:
    Box();
    bool is_occupied() const;
    std::vector<int> get_color() const;
    void change_status(bool occ, std::vector<int> col);

};
class Grid {
    public : 
    int _height;
    int _width ;
    std::vector<std::vector<Box>> _grid = std::vector<std::vector<Box>>(WIDTH);

    public :
    Grid();
    void delete_piece(Shape* piece);
};

#endif