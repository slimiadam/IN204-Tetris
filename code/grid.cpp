#include "grid.hpp"

Box :: Box()  : _occupied(true)  {
    _color[0]=(0);
    _color[1]=(0);
    _color[2]=(0);
};

std::vector<int> Box::get_color()const {
    return _color;
};
bool Box::is_occupied()const {
    return _occupied;
};

void Box:: change_status(bool occ=false, std::vector<int> col=std::vector<int>(3,0)){
    _color= col;
    _occupied =occ;
};

Grid :: Grid(): _height(HEIGHT), _width(WIDTH){
    for (int i=0; i<WIDTH; i++){
        _grid[i].resize(HEIGHT);
        for (int k =0; k< HEIGHT; k++){
            _grid[i][k].change_status();
        }
    }
    
}