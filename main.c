#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>

#define PORT 1337
#define MAXLEN 1024

int main(void)
{
    IPaddress ip;
    TCPsocket sd;
    char server[25] = "", newport[MAXLEN], SYN0[MAXLEN] = "hearts", SYN1[MAXLEN] = "port";
    int port, result;
    
    strcpy(server, "130.237.84.89");
    port = PORT;
    
    if (SDLNet_ResolveHost(&ip, server, port) < 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    
        if (!(sd = SDLNet_TCP_Open(&ip)))
        {
            fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
    
        int len;
    
        len = (int) strlen(SYN0)+1;
    
        if (SDLNet_TCP_Send(sd, SYN0,len) < len)
        {
            fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
    
        result=SDLNet_TCP_Recv(sd,SYN0,MAXLEN);
        if(result<=0) {
        }
        printf("Received: \"%s\"\n",SYN0);
    
        if(strcmp(SYN0, "diamonds") == 0)
        {
            if (SDLNet_TCP_Send(sd, SYN1,len) < len)
            {
                fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                exit(EXIT_FAILURE);
            }
            
            result=SDLNet_TCP_Recv(sd,SYN1,MAXLEN);
            if(result<=0) {
            }
            printf("Received: \"%s\"\n",SYN1);
            strcpy(newport, SYN1);
        }
    
        return 0;
}
