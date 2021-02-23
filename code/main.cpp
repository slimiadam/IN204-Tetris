#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include "SDL/SDL.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_surface.h>
#include "grid.hpp"
#include "point.hpp"


//Compilation : g++ -Wall main.c -lSDL -lSDL_image -lSDL_ttf -o ./tetris.x


#define FIELD_HEIGHT (1080)  // on enlève le contour du terrain
#define FIELD_WIDTH (FIELD_HEIGHT*12/24)
#define CELL_SIZE (FIELD_HEIGHT/24)

void Reset_Time(Uint32* Time, Uint32* Delay)  // met à jour l'heure du dernier coup d'horloge et du délai associé.
{   
    *Time=SDL_GetTicks();
    *Delay=0;
}

int main(int argc, char** argv){
    srand(time(NULL));
    int keep = 1;

//Déclaration des variables d'affichage, des événements, et du temps
    SDL_Surface *screen = NULL, *blackscreen = NULL, *left_side = NULL, *right_side = NULL, *upper_side = NULL, *bottom_side = NULL;
    SDL_Surface *left_side_2 = NULL, *right_side_2 = NULL, *upper_side_2 = NULL, *bottom_side_2 = NULL;
    SDL_Surface *tetris_menu = NULL, *score_menu_p1 = NULL, *score_menu_p2 = NULL, *score_p1 = NULL, *score_p2 = NULL ;
    std::vector <SDL_Surface*> cell_tab(220, NULL);
    std::vector <SDL_Surface*> cell_tab_2(220, NULL);
    SDL_Event event;                                                                             //variable event qui gere les evenements
    SDL_Rect position_blackscreen;
    SDL_Rect position_left_side, position_right_side, position_upper_side, position_bottom_side;
    SDL_Rect position_left_side_2, position_right_side_2, position_upper_side_2, position_bottom_side_2;
    SDL_Rect position_tetris, position_score_menu_p1, position_score_menu_p2, position_score_p1, position_score_p2;
    std::vector <SDL_Rect> cell_position(220), cell_position_2(220);
    TTF_Font *police_tetris = NULL, *police_score_menu = NULL, *police_score = NULL;
    SDL_Color text_color = { 50, 255, 250 }, score_color = {255,0,0};
    char score_text_p1[10], score_text_p2[10];

//Déclaration des variables
    Grid game_grid;
    Grid second_grid;
    Shape::Ptr piece = new_piece();
    Shape::Ptr next_piece = new_piece();
    game_grid.add_piece(piece);

//Declaration temps
    Uint32 last_clock_tick_t=0;
    Uint32 clock_tick_delay=0;
    Uint32 time_dec=1200;

    Uint32 last_rotation_t=0;
    Uint32 rotation_delay=0;
    Uint32 time_rot=200;


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
    // screen = SDL_SetVideoMode(320, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); 
    if (screen == NULL) // Si l'ouverture a échoué, on le note et on arrête
        {
            fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    
    police_tetris = TTF_OpenFont("retro_font.ttf", 120);
    police_score_menu = TTF_OpenFont("retro_font.ttf", 60);
    police_score = TTF_OpenFont("retro_font.ttf", 40);

    tetris_menu = TTF_RenderText_Blended(police_tetris,"TETRIS",text_color);
    position_tetris.x=1920/2-tetris_menu->w/2;
    position_tetris.y=30;    

//position blackscreen

    blackscreen = SDL_CreateRGBSurface(SDL_HWSURFACE, 1920, 1080, 32, 0, 0, 0, 0);
    SDL_FillRect(blackscreen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    position_blackscreen.x=0;
    position_blackscreen.y=0;

    //Mise en place grille joueur 1
    left_side = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, FIELD_HEIGHT-2*CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(left_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_left_side.x=0;
    position_left_side.y=CELL_SIZE;

    right_side = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, FIELD_HEIGHT-2*CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(right_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_right_side.x=FIELD_WIDTH-CELL_SIZE;
    position_right_side.y=CELL_SIZE;

    upper_side = SDL_CreateRGBSurface(SDL_HWSURFACE, FIELD_WIDTH, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(upper_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_upper_side.x=0;
    position_upper_side.y=0;

    bottom_side = SDL_CreateRGBSurface(SDL_HWSURFACE, FIELD_WIDTH, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(bottom_side, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_bottom_side.x=0;
    position_bottom_side.y=FIELD_HEIGHT-CELL_SIZE;

    //Mise en place grille joueur 2
    left_side_2 = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, FIELD_HEIGHT-2*CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(left_side_2, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_left_side_2.x=1920-FIELD_WIDTH;
    position_left_side_2.y=CELL_SIZE;

    right_side_2 = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, FIELD_HEIGHT-2*CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(right_side_2, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_right_side_2.x=1920-CELL_SIZE;
    position_right_side_2.y=CELL_SIZE;

    upper_side_2 = SDL_CreateRGBSurface(SDL_HWSURFACE, FIELD_WIDTH, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(upper_side_2, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_upper_side_2.x=1920-FIELD_WIDTH;
    position_upper_side_2.y=0;

    bottom_side_2 = SDL_CreateRGBSurface(SDL_HWSURFACE, FIELD_WIDTH, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(bottom_side_2, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    position_bottom_side_2.x=1920-FIELD_WIDTH;
    position_bottom_side_2.y=FIELD_HEIGHT-CELL_SIZE;    

// Creation des cellules
    //joueur 1
    for (int i = 0; i < 220; i++)
    {
        cell_tab[i]=SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, CELL_SIZE, 32, 0, 0, 0, 0);
        cell_position[i].x=position_left_side.x+CELL_SIZE+(i%10)*CELL_SIZE;
        cell_position[i].y=CELL_SIZE+(i/10)*CELL_SIZE;
        // SDL_FillRect(cell_tab[i], NULL, SDL_MapRGB(screen->format, (i*20)%255, (i*16)%255, (i*8)%255));
    }

    //joueur 2
    for (int i = 0; i < 220; i++)
    {
        cell_tab_2[i]=SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, CELL_SIZE, 32, 0, 0, 0, 0);
        cell_position_2[i].x=position_left_side_2.x+CELL_SIZE+(i%10)*CELL_SIZE;
        cell_position_2[i].y=CELL_SIZE+(i/10)*CELL_SIZE;
        // SDL_FillRect(cell_tab[i], NULL, SDL_MapRGB(screen->format, (i*20)%255, (i*16)%255, (i*8)%255));
    }

// Affichage des scores
    score_menu_p1 = TTF_RenderText_Blended(police_score_menu,"SCORE P1",text_color);
    position_score_menu_p1.x = position_right_side.x + right_side->w + 15;
    position_score_menu_p1.y = position_tetris.y + tetris_menu->h + 15;

    score_menu_p2 = TTF_RenderText_Blended(police_score_menu,"SCORE P2",text_color);
    position_score_menu_p2.x = position_left_side_2.x - score_menu_p2->w - 15;
    position_score_menu_p2.y = position_tetris.y + tetris_menu->h + 15;

    score_p1 = TTF_RenderText_Blended(police_score,"0",score_color);
    position_score_p1.x = position_score_menu_p1.x + score_menu_p1->w /2 - score_p1->w/2;
    position_score_p1.y = position_score_menu_p1.y + score_menu_p1->h + 10;

    score_p2 = TTF_RenderText_Blended(police_score_menu,"0",score_color);
    position_score_p2.x = position_score_menu_p2.x + score_menu_p2->w /2 - score_p2->w/2;
    position_score_p2.y = position_score_menu_p2.y + score_menu_p2->h + 10;



    

    while(keep)
    {
        Uint8 *key = SDL_GetKeyState(NULL);
        SDL_PollEvent(&event);

        if (!(piece->get_can_move()))
        {
            piece = next_piece;
            next_piece = new_piece();
            game_grid.delete_line();
            bool can = game_grid.add_piece(piece);
            if (not(can)){
                std::cout << "C'est la fiiiiin " << std::endl;
                return 0;
            }
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
        rotation_delay = SDL_GetTicks() - last_rotation_t;


        if (clock_tick_delay>time_dec)
        {
            game_grid.move_down(piece);
            Reset_Time(&last_clock_tick_t, &clock_tick_delay);
        }
        

    //actions
        if (key[SDLK_LEFT])    
        {
            game_grid.move_left(piece);
            // auto lambda = [&piece](){
            //     piece->move_left();
            // };
            // game_grid.move(piece, lambda);
        }

        if (key[SDLK_RIGHT])    
        {
            game_grid.move_right(piece);
        }

        if (key[SDLK_DOWN])    
        {
            game_grid.move_down(piece);
            Reset_Time(&last_clock_tick_t, &clock_tick_delay);
        }

        if (key[SDLK_s])    
        {
            if (rotation_delay > time_rot)
            {
                game_grid.rotate_right(piece);
                Reset_Time(&last_rotation_t, &rotation_delay);
            }
        }
        // if (key[SDLK_q])    
        // {
        //     game_grid.rotate_left(piece);
        // }

        // Mise a jour cases affichee
        for(int i=0; i<22; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                SDL_FillRect(cell_tab[(21-i)*10+j], NULL, SDL_MapRGB(screen->format, game_grid._grid[i][j].get_color()[0], game_grid._grid[i][j].get_color()[1], game_grid._grid[i][j].get_color()[2]));
            }
        }

        for(int i=0; i<22; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                SDL_FillRect(cell_tab_2[(21-i)*10+j], NULL, SDL_MapRGB(screen->format, second_grid._grid[i][j].get_color()[0], second_grid._grid[i][j].get_color()[1], second_grid._grid[i][j].get_color()[2]));
            }
        }

        // Mise a jour affichage score
        sprintf(score_text_p1, "%d", game_grid._score);
        sprintf(score_text_p2, "%d", second_grid._score);

        score_p1 = TTF_RenderText_Blended(police_score, score_text_p1, score_color);
        position_score_p1.x = position_score_menu_p1.x + score_menu_p1->w /2 - score_p1->w/2;
        position_score_p1.y = position_score_menu_p1.y + score_menu_p1->h + 10;

        score_p2 = TTF_RenderText_Blended(police_score,score_text_p2,score_color);
        position_score_p2.x = position_score_menu_p2.x + score_menu_p2->w /2 - score_p2->w/2;
        position_score_p2.y = position_score_menu_p2.y + score_menu_p2->h + 10;


        SDL_BlitSurface(blackscreen, NULL, screen, &position_blackscreen);

        SDL_BlitSurface(left_side, NULL, screen, &position_left_side);
        SDL_BlitSurface(right_side, NULL, screen, &position_right_side);
        SDL_BlitSurface(upper_side, NULL, screen, &position_upper_side);
        SDL_BlitSurface(bottom_side, NULL, screen, &position_bottom_side);

        SDL_BlitSurface(left_side_2, NULL, screen, &position_left_side_2);
        SDL_BlitSurface(right_side_2, NULL, screen, &position_right_side_2);
        SDL_BlitSurface(upper_side_2, NULL, screen, &position_upper_side_2);
        SDL_BlitSurface(bottom_side_2, NULL, screen, &position_bottom_side_2);

        SDL_BlitSurface(tetris_menu, NULL, screen, &position_tetris);

        for (int i = 0; i < 220; i++)
        {
            SDL_BlitSurface(cell_tab[i], NULL, screen, &cell_position[i]);
        }

        for (int i = 0; i < 220; i++)
        {
            SDL_BlitSurface(cell_tab_2[i], NULL, screen, &cell_position_2[i]);
        }
        
        SDL_BlitSurface(score_menu_p1, NULL, screen, &position_score_menu_p1);
        SDL_BlitSurface(score_menu_p2, NULL, screen, &position_score_menu_p2);
        SDL_BlitSurface(score_p1, NULL, screen, &position_score_p1);
        SDL_BlitSurface(score_p2, NULL, screen, &position_score_p2);


        SDL_Flip(screen);                
        SDL_Delay(50);
    }

    SDL_FreeSurface(left_side);
    SDL_FreeSurface(right_side);
    SDL_FreeSurface(upper_side);
    SDL_FreeSurface(bottom_side);

    SDL_FreeSurface(left_side_2);
    SDL_FreeSurface(right_side_2);
    SDL_FreeSurface(upper_side_2);
    SDL_FreeSurface(bottom_side_2);

    SDL_FreeSurface(tetris_menu);
    SDL_FreeSurface(score_menu_p1);
    SDL_FreeSurface(score_menu_p2);
    SDL_FreeSurface(score_p1);
    SDL_FreeSurface(score_p2);

    SDL_FreeSurface(blackscreen);

    for (int i = 0; i < 220; i++)
    {
        SDL_FreeSurface(cell_tab[i]);
    }

    for (int i = 0; i < 220; i++)
    {
        SDL_FreeSurface(cell_tab_2[i]);
    }

    TTF_Quit();
    SDL_Quit();


    return 0;

}