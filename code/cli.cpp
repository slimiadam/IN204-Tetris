#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>

#include "SDL/SDL_net.h"

int main(int argc, char **argv) { 
    IPaddress ip; /* Server address */ 
    TCPsocket client; /* Socket descriptor */ 
    int quit, len; 
    char buffer[512];

    /* Simple parameter checking  
    if (argc < 3)
    { 
        fprintf(stderr, "Usage: %s host port\n", argv[0]); 
        exit(EXIT_FAILURE); 
    }
    */

    if (SDLNet_Init() < 0) 
    { 
        std::cout << "SDLNet_Init: \n"<< SDLNet_GetError(); 
        exit(EXIT_FAILURE); 
    }

    /* Resolve the host we are connecting to */ 
    if ( SDLNet_ResolveHost(&ip, "147.250.225.50", 1234) <0 )
    { 
        std::cout << "SDLNet_ResolveHost: \n"<< SDLNet_GetError(); 
        exit(EXIT_FAILURE); 
        }

    /* Open a connection with the IP provided (listen on the host's port) */ 
    if (!(client = SDLNet_TCP_Open(&ip))) 
    { 
        std::cout << "SDLNet_TCP_Open:\n" << SDLNet_GetError(); 
        exit(EXIT_FAILURE); 
    }

    /* Send messages */ 
    quit = 0; 
    while (!quit) 
    { 
        char text[100];
        SDLNet_TCP_Recv(client, text, 100);
        std::cout << text << std::endl;
        std::cout << "Write something:\n>"<< std::endl; 
        scanf("%s", buffer);

        len = strlen(buffer) + 1; 
        if (SDLNet_TCP_Send(client, (void *)buffer, len) < len) {
             std::cout << "SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl; 
             exit(EXIT_FAILURE); }

        if(strcmp(buffer, "exit") == 0)
        {
            quit = 1;
        } 
        if(strcmp(buffer, "quit") == 0) 
        { 
            quit = 1; 
        }
    }

    SDLNet_TCP_Close(client); SDLNet_Quit(); 

    return EXIT_SUCCESS ;
}
