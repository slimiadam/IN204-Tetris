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
    for (int i=0; i<HEIGHT; i++){
        _grid[i].resize(WIDTH);
        for (int k =0; k< WIDTH; k++){
            _grid[i][k].change_status();
        }
    }
    
}


void Grid :: move_right(Shape::Ptr piece){
    delete_piece(piece);
    int ok = 1;
    if ((piece->get_center().get_y()+ 1) >= WIDTH || _grid[piece->get_center().get_x()][piece->get_center().get_y()+1].is_occupied()){
        ok = 0;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x();
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y()+1;
        if (y_tmp >= WIDTH || _grid[x_tmp][y_tmp].is_occupied()){
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
void Grid :: move_left(Shape::Ptr piece){
    delete_piece(piece);
    int ok = 1;
    if ((piece->get_center().get_y()- 1)<0 || _grid[piece->get_center().get_x()][piece->get_center().get_y()-1].is_occupied()){
        ok = 0;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() + piece->get_distribution_i(i).get_x();
        int y_tmp = piece->get_center().get_y() + piece->get_distribution_i(i).get_y()-1;
        if (y_tmp < 0  || _grid[x_tmp][y_tmp].is_occupied()){
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
void Grid :: move_down(Shape::Ptr piece){
    delete_piece(piece);
    int ok = 1;
    if ((piece->get_center().get_x()-1)<0  || _grid[piece->get_center().get_x()-1][piece->get_center().get_y()].is_occupied()){
        ok = 0;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x()-1;
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
        if (x_tmp < 0 || _grid[x_tmp][y_tmp].is_occupied()){
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

void Grid :: rotate_right(Shape::Ptr piece){
    delete_piece(piece);
    Shape::Ptr piece2(piece);  
    piece2->rotate_right();
    int ok =1;
    if ((not(is_in_grid(piece2->get_center().get_x(),piece2->get_center().get_y()))) ||  _grid[piece2->get_center().get_x()][piece2->get_center().get_y()].is_occupied()){
        ok = 0;
        std::cout << " coucou du centre" << std::endl ;
    }
    else{
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece2->get_center().get_x() +piece2->get_distribution_i(i).get_x();
        int y_tmp = piece2->get_center().get_y()+piece2->get_distribution_i(i).get_y();
        
        if (not(is_in_grid(x_tmp,y_tmp)) || _grid[x_tmp][y_tmp].is_occupied()){
            ok = 0;
            std::cout << " coucou "  << i << std::endl ;
        }
        i++;
        }
    }
    if (ok){
        piece = piece2;
        add_piece(piece);
    }
    else{
        add_piece(piece);
        std::cout<< "Error" << std::endl;
    }

}

void Grid :: delete_piece(Shape::Ptr piece){
    _grid[piece->get_center().get_x()][piece->get_center().get_y()].change_status(false);
    int i = 0;
    while ( i<3){
    int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x();
    int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
    _grid[x_tmp][y_tmp].change_status(false);
    i++;
    }
};
void Grid :: add_piece(Shape::Ptr piece){
    if ((piece->get_center().get_x()==-1) && (piece->get_center().get_y()==-1))
    {
        piece->change_center(20,4);
    }
    _grid[piece->get_center().get_x()][piece->get_center().get_y()].change_status(true,piece->get_color());
    int i = 0;
    while ( i<3){
    int x_tmp = piece->get_center().get_x() + piece->get_distribution_i(i).get_x();
    int y_tmp = piece->get_center().get_y()+ piece->get_distribution_i(i).get_y();
    _grid[x_tmp][y_tmp].change_status(true, piece->get_color());
    i++;
    }
};

bool Grid :: is_in_grid(int x, int y){
    return (x>=0 && x<HEIGHT && y >=0 && y<WIDTH);
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

bool Grid :: ok_down(Shape::Ptr piece, int nb){
    int ok = true;
    if ((piece->get_center().get_x()-nb)<0  || _grid[piece->get_center().get_x()-nb][piece->get_center().get_y()].is_occupied()){
        ok = false;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x()-nb;
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
        if (x_tmp < 0 || _grid[x_tmp][y_tmp].is_occupied()){
            ok = false;
        }
        i++;
        }
    }
    return(ok);
}

bool Grid :: ok_up(Shape::Ptr piece, int nb){
    int ok = true;
    if ((piece->get_center().get_x()+nb)<0  || _grid[piece->get_center().get_x()+nb][piece->get_center().get_y()].is_occupied()){
        ok = false;
    }
    else {
        int i = 0;
        while ( i<3 && ok){
        int x_tmp = piece->get_center().get_x() +piece->get_distribution_i(i).get_x()+nb;
        int y_tmp = piece->get_center().get_y()+piece->get_distribution_i(i).get_y();
        if (x_tmp < 0 || _grid[x_tmp][y_tmp].is_occupied()){
            ok = false;
        }
        i++;
        }
    }
    return(ok);
}