#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "SDL/SDL_net.h"
#include "grid.hpp"
#include "pieces.hpp"




int main(int argc, char **argv) 
{ 
    TCPsocket serveur, client; /* Socket descriptor, Client socket descriptor */ 
    IPaddress ip, *remoteIP; 
    int quit, quit2=0; 
    char buffer[512];

    if (SDLNet_Init() < 0) 
    { 
        std ::cout <<  "SDLNet_Init:" << SDLNet_GetError() << std::endl; 
        exit(EXIT_FAILURE);
    }

    /* Resolving the host using NULL make network interface to listen */
    if (SDLNet_ResolveHost(&ip, NULL, 1234) < 0) 
    { 
        std::cout <<  "SDLNet_ResolveHost:" << SDLNet_GetError() << std::endl; 
        exit(EXIT_FAILURE); 
    }
    /* Open a connection with the IP provided (listen on the host's port) */ 
    if (!(serveur = SDLNet_TCP_Open(&ip))) 
    { 
        std::cout <<  "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl; 
        exit(EXIT_FAILURE); 
    }

    /* Wait for a connection, send data and term */ 
    quit = 0; 
    char piece[] = { 'I', 'T', 'Z', 'S', 'J', 'O','L'};
    while (!quit) 
    { /* This check the sd if there is a pending connection. * If there is one, accept that, and open a new socket for communicating */ 
        if ((client = SDLNet_TCP_Accept(serveur))) { 
        /* Now we can communicate with the client using csd socket * sd will remain opened waiting other connections */

        /* Get the remote address */ 
        if ((remoteIP = SDLNet_TCP_GetPeerAddress(client)))
        {
        /* Print the address, converting in the host format */ 
        std::cout << "Host connected:  " << SDLNet_Read32(&remoteIP->host) << " "<< SDLNet_Read16(&remoteIP->port) << std::endl;
        }
        else 
        { 
            std::cout << "SDLNet_TCP_GetPeerAddress: " <<  SDLNet_GetError() << std::endl;
        }
        int score_p1, score_p2 = 0;
        while (!quit2) 
        {     
            if (SDLNet_TCP_Recv(client, buffer, 512)>0)
            {   
                if (strcmp(buffer, "cant") == 0){
                    int randNum = rand()%(7);
                    buffer[0] = piece[randNum];
                    SDLNet_TCP_Send(client, buffer, strlen(buffer) + 1);
                     //Reception score
                SDLNet_TCP_Recv(client, &score_p1, sizeof(int));
                std::cout << "Le score est de : " << score_p1 << std::endl;
                //Envoie score p2
                SDLNet_TCP_Send(client, &score_p2, sizeof(int));
            
                }
                else if(strcmp(buffer, "quit") == 0) /* Quit the program */ 
                { 
                    quit2 = 1;
                    quit = 1; 
                    std::cout << "Quit program\n" << std::endl; 
                }
                else {
                }
                } 
           
           
            
        }

        /* Close the client socket */ 
        SDLNet_TCP_Close(client);
        } 
    }

    SDLNet_TCP_Close(serveur); 
    SDLNet_Quit();

    return EXIT_SUCCESS; 
    } 