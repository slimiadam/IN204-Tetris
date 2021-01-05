#include "grid.hpp"

Box :: Box()  : _occupied(true)  {
    _color[0]=(0);
    _color[1]=(0);
    _color[2]=(0);
};

std::vector<int> Box::get_color()const {
    return _color;
};
bool Box::is_occupied() {
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


void Grid :: move_right(Shape* piece){
    delete_piece(piece);
    int ok = 1;
    if ((piece->get_center().get_x()+ 1)>WIDTH || _grid[piece->get_center().get_x()+ 1][piece->get_center().get_y()].is_occupied()){
        ok = 0;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x()+ 1;
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
        if (x_tmp > WIDTH || _grid[x_tmp][y_tmp].is_occupied()){
            ok = 0;
        }
        i++;
        }
    }
    if (ok) {
        piece->move_right();
        add_piece(piece);
    }
    else {
        add_piece(piece);
        std::cout << "Error" << std::endl;
    }
};
void Grid :: move_left(Shape* piece){
    delete_piece(piece);
    int ok = 1;
    if ((piece->get_center().get_x()- 1)<0 || _grid[piece->get_center().get_x()- 1][piece->get_center().get_y()].is_occupied()){
        ok = 0;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x()- 1;
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
        if (x_tmp < 0  || _grid[x_tmp][y_tmp].is_occupied()){
            ok = 0;
        }
        i++;
        }
    }
    if (ok) {
        piece->move_left();
        add_piece(piece);
    }
    else {
        add_piece(piece);
        std::cout << "Error" << std::endl;
    }
};
void Grid :: move_down(Shape* piece){
    delete_piece(piece);
    int ok = 1;
    if ((piece->get_center().get_y()-1)<0  || _grid[piece->get_center().get_x()][piece->get_center().get_y()-1].is_occupied()){
        ok = 0;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x();
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y() -1;
        if (y_tmp < 0 || _grid[x_tmp][y_tmp].is_occupied()){
            ok = 0;
        }
        i++;
        }
    }
    if (ok) {
        piece->move_down();
        add_piece(piece);
    }
    else {
        add_piece(piece);
        piece->change_status();
        std::cout << "Error" << std::endl;
    }
};

void Grid :: rotate_right(Shape * piece){
    delete_piece(piece);
    Shape* new_piece(piece);
    new_piece->rotate_right();
    int ok =1;
    if (new_piece->get_center().get_x()>WIDTH ||new_piece->get_center().get_x() <0 ||  _grid[piece->get_center().get_x()][piece->get_center().get_y()-1].is_occupied()){
        ok = 0;
    }
    else{
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x();
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
        if (not(is_in_grid(x_tmp,y_tmp)) || _grid[x_tmp][y_tmp].is_occupied()){
            ok = 0;
        }
        i++;
        }
    }
    if (ok){
        add_piece(new_piece);
    }
    else{
        add_piece(piece);
        std::cout<< "Error" << std::endl;
    }

}

void Grid :: delete_piece(Shape* piece){
    _grid[piece->get_center().get_x()][piece->get_center().get_y()].change_status(false);
    int i = 0;
    while ( i<3){
    int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x();
    int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
    _grid[x_tmp][y_tmp].change_status(false);
    i++;
    }
};
void Grid :: add_piece(Shape* piece){
    _grid[piece->get_center().get_x()][piece->get_center().get_y()].change_status(true,piece->get_color());
    int i = 0;
    while ( i<3){
    int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x();
    int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
    _grid[x_tmp][y_tmp].change_status(true, piece->get_color());
    i++;
    }
};

bool Grid :: is_in_grid(int x, int y){
    return (x>=0 && x<WIDTH && y >=0 && y<HEIGHT);
};

bool Grid :: check_line(int y) {
    int x = 0 ;
    int full_line = 0;
    while (x<WIDTH && not(full_line)){
        if (_grid[x][y].is_occupied()){
            full_line = 1;
        }
        y ++ ;
    }
    return full_line ;
};

void Grid :: delete_line(int y){
    if (check_line(y)) {
        for (int k = y+1 ; k<(HEIGHT-1); k++){
            for (int i = 0 ; i<WIDTH; i++){
                _grid[i][k]=_grid[i][k+1];
            }
        }
    }
}