#include "grid.hpp"
#include <vector>

std::vector <int> score_vect{0,40,100,300,1200};

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

Grid :: Grid(): _height(HEIGHT), _width(WIDTH), _score(0) {
    for (int i=0; i<_height; i++){
        _grid[i].resize(_width);
        for (int k =0; k< _width; k++){
            _grid[i][k].change_status();
        }
    }
}

Grid:: Grid(int height, int width) :_height(height), _width(width), _score(0) {
    _grid.resize(_height);
    for (int i=0; i<_height; i++){
        _grid[i].resize(_width);
        for (int k =0; k< _width; k++){
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
        _score += HEIGHT-1-piece->get_height();
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
        piece->rotate_left(); 
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
bool Grid :: add_piece(Shape::Ptr piece){
    if ((piece->get_center().get_x()==-1) && (piece->get_center().get_y()==-1))
    {   
        piece->change_center(_height-2,_width/2-1);
        bool ok = true;
        if (not(_grid[piece->get_center().get_x()][piece->get_center().get_y()].is_occupied())){
            int i = 0;
        
        while ( ok && i<3){
            int x_tmp = piece->get_center().get_x() + piece->get_distribution_i(i).get_x();
            int y_tmp = piece->get_center().get_y()+ piece->get_distribution_i(i).get_y();
            if (_grid[x_tmp][y_tmp].is_occupied()){
                ok =false;
            }
            i++;
        }
        }
        else {ok = false;};
        if (not(ok)){
            piece->change_center(-1,-1);
        }
    }
    if (not(piece->get_center().get_x() == -1)){
    _grid[piece->get_center().get_x()][piece->get_center().get_y()].change_status(true,piece->get_color());
    int i = 0;
    while ( i<3){
    int x_tmp = piece->get_center().get_x() + piece->get_distribution_i(i).get_x();
    int y_tmp = piece->get_center().get_y()+ piece->get_distribution_i(i).get_y();
    _grid[x_tmp][y_tmp].change_status(true, piece->get_color());
    i++;
    }
    return true;
    }
    else {return false;}
};

bool Grid :: is_in_grid(int x, int y){
    return (x>=0 && x<HEIGHT && y >=0 && y<WIDTH);
};

bool Grid :: check_line(int x) {
    int y = 0 ;
    int full_line = 1;
    while (y<WIDTH && full_line){
        if (not(_grid[x][y].is_occupied())){
            full_line = 0;
        }
        y ++ ;
    }
    return full_line ;
};

void Grid :: delete_line(){
    int c=0;
    int x=0;
    while (x<HEIGHT)
    {
        if (check_line(x)) {
            c++;
            for (int k = x ; k < (HEIGHT-1); k++){
                for (int i = 0 ; i<WIDTH; i++){
                    _grid[k][i]=_grid[k+1][i];
                }
            }
            for (int i = 0; i < WIDTH; i++)
            {
                _grid[HEIGHT-1][i].change_status();
            }
        }
        else
        {
            x++;
        }
    }
    _score+=score_vect[c];
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