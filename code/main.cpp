#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <SDL/SDL_ttf.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "grid.hpp"
#include "pieces.hpp"
#include "point.hpp"


//Compilation : g++ -Wall main.c -lSDL -lSDL_image -lSDL_ttf -o ./tetris.x


#define FIELD_HEIGHT (1080)  // on enlève le contour du terrain
#define FIELD_WIDTH (FIELD_HEIGHT*12/24)
#define CELL_SIZE (FIELD_HEIGHT/24)

void Reset_Time(int* Time, int* Delay)  // met à jour l'heure du dernier coup d'horloge et du délai associé.
{   
    *Time=SDL_GetTicks();
    *Delay=0;
}

int main(int argc, char** argv){
<<<<
    int keep = 1;

//Déclaration des variables d'affichage, des événements, et du temps
    SDL_Surface *screen = NULL, *left_side = NULL, *right_side = NULL, *upper_side = NULL, *bottom_side = NULL;
    SDL_Surface *tetris_menu = NULL;
    std::vector <SDL_Surface*> cell_tab(220, NULL);
    SDL_Event event;                                                                             //variable event qui gere les evenements
    SDL_Rect position_left_side, position_right_side, position_upper_side, position_bottom_side;
    SDL_Rect position_tetris;
    std::vector <SDL_Rect> cell_position(220);
    TTF_Font *police_menu = NULL;
    SDL_Color text_color = { 50, 255, 250 };
    int time=100;

//Déclaration des variables
    Grid game_grid;
    Shape::Ptr piece = new_piece();
    game_grid.add_piece(piece);

//Declaration temps
    Uint32 last_clock_tick_t=0;
    Uint32 clock_tick_delay=0;


//Démarrage de la SDL et test d'erreur :
    if (SDL_Init(SDL_INIT_VIDEO) == -1) 
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

//Démarrage TTF et test d'erreur
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

//creation fenêtre
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); 
    if (screen == NULL) // Si l'ouverture a échoué, on le note et on arrête
        {
            fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    
    police_menu = TTF_OpenFont("retro_font.ttf", 120);
    tetris_menu = TTF_RenderText_Blended(police_menu,"TETRIS",text_color);
    position_tetris.x=50;
    position_tetris.y=50;
    

    //Mise en place terrain
    left_side = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, FIELD_HEIGHT-2*CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(left_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_left_side.x=1920/2-FIELD_WIDTH/2;
    position_left_side.y=CELL_SIZE;

    right_side = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, FIELD_HEIGHT-2*CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(right_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_right_side.x=1920/2+FIELD_WIDTH/2-CELL_SIZE;
    position_right_side.y=CELL_SIZE;

    upper_side = SDL_CreateRGBSurface(SDL_HWSURFACE, FIELD_WIDTH, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(upper_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_upper_side.x=1920/2-FIELD_WIDTH/2;
    position_upper_side.y=0;

    bottom_side = SDL_CreateRGBSurface(SDL_HWSURFACE, FIELD_WIDTH, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(bottom_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_bottom_side.x=1920/2-FIELD_WIDTH/2;
    position_bottom_side.y=FIELD_HEIGHT-CELL_SIZE;

// Creation des cellules
    for (int i = 0; i < 220; i++)
    {
        cell_tab[i]=SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, CELL_SIZE, 32, 0, 0, 0, 0);
        cell_position[i].x=position_left_side.x+CELL_SIZE+(i%10)*CELL_SIZE;
        cell_position[i].y=CELL_SIZE+(i/10)*CELL_SIZE;
        // SDL_FillRect(cell_tab[i], NULL, SDL_MapRGB(screen->format, (i*20)%255, (i*16)%255, (i*8)%255));
    }
    

    while(keep)
    {

        Uint8 *key = SDL_GetKeyState(NULL);
        SDL_PollEvent(&event);

        if (!(piece->get_can_move()))
        {
            piece = new_piece();
            game_grid.add_piece(piece);
        }
        

    //Quitter la fenetre
        switch(event.type)
        {   
            case SDL_QUIT: 
                keep = 0;
                break;
        }
        if (key[SDLK_ESCAPE])  
            {
                keep = 0;
            }

    //mise a jour delay
        clock_tick_delay = SDL_GetTicks() - last_clock_tick_t;

    //actions
        if (key[SDLK_LEFT])    
        {
            game_grid.move_left(piece);
        }

        if (key[SDLK_RIGHT])    
        {
            game_grid.move_right(piece);
        }

        if (key[SDLK_DOWN])    
        {
            game_grid.move_down(piece);
        }

        if (key[SDLK_s])    
        {
            game_grid.rotate_right(piece);
        }

        for(int i=0; i<22; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                SDL_FillRect(cell_tab[(21-i)*10+j], NULL, SDL_MapRGB(screen->format, game_grid._grid[i][j].get_color()[0], game_grid._grid[i][j].get_color()[1], game_grid._grid[i][j].get_color()[2]));
            }
            
        }



        SDL_BlitSurface(left_side, NULL, screen, &position_left_side);
        SDL_BlitSurface(right_side, NULL, screen, &position_right_side);
        SDL_BlitSurface(upper_side, NULL, screen, &position_upper_side);
        SDL_BlitSurface(bottom_side, NULL, screen, &position_bottom_side);
        SDL_BlitSurface(tetris_menu, NULL, screen, &position_tetris);
        for (int i = 0; i < 220; i++)
        {
            SDL_BlitSurface(cell_tab[i], NULL, screen, &cell_position[i]);
        }
        


        SDL_Flip(screen);                
        SDL_Delay(50);
    }

    SDL_FreeSurface(left_side);
    SDL_FreeSurface(right_side);
    SDL_FreeSurface(upper_side);
    SDL_FreeSurface(bottom_side);
    SDL_FreeSurface(tetris_menu);
    for (int i = 0; i < 220; i++)
        {
            SDL_FreeSurface(cell_tab[i]);
        }

    TTF_Quit();
    SDL_Quit();


    return 0;

}