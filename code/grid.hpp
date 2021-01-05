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
    bool is_occupied();
    std::vector<int> get_color() const;
    void change_status(bool occ, std::vector<int> col);

};

class Grid {
    public : 
    int _height;
    int _width ;
    std::vector<std::vector<Box>> _grid = std::vector<std::vector<Box>>(HEIGHT);

    public :
    Grid();
    void delete_piece(Shape::Ptr piece); // Supprime la pièce dans la grille 
    void add_piece(Shape::Ptr piece); // Ajoute une pièce dans la grille
    bool is_in_grid(int x, int y); // renvoie si x et y sont dans la grille 
    void move_right(Shape::Ptr piece);
    void move_left(Shape::Ptr piece);
    void move_down(Shape::Ptr piece);
    void rotate_right(Shape::Ptr piece);
    void rotate_left(Shape::Ptr piece);
    bool check_line(int y); // true si remplie faux si reste de la place
    void delete_line(int y); // Verifie si la ligne est complèe et si c'est le cas la détruit, et descend les lignes supérieurs)
};
/*
template<typename function_move>
void Grid :: rotate_left(Shape& piece, void Shape :: *function_move()){
    delete_piece(piece);
    Shape* new_piece(piece);
    *new_piece.function_move();
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
*/
#endif