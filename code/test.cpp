#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "grid.hpp"
#include "pieces.hpp"
#include "point.hpp"

void affichage(Grid plateau)
{	
	int a,k;
	a=1;
	for (int i=0;i<22;i++) 
	{
		for (int j=0;j<10;j++) {
			if (!(plateau._grid[i][j].is_occupied())){
				std::cout << " |" ;
			}
			else {
					std::cout << "#|" ;
				}
		}

	std::cout << std::endl;
	}
	std::cout << std::endl;
}


int main(){
    Grid grid_game;
    Shape::Ptr piece=new_piece();
	grid_game.add_piece(piece);
    affichage(grid_game);
    return 0;

} 