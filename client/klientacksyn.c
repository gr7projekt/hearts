#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>

#define PORT 1337
#define MAXLEN 1024

int main(void)
{
    IPaddress ip;
    TCPsocket sd;
    char server[25] = "", newport[MAXLEN], SYN0[MAXLEN] = "hearts", SYN1[MAXLEN] = "port";
    int port, result, len, len2;
    
    strcpy(server, "192.168.56.101");
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
    printf("socket open\n");
    
    
    len = (int) strlen(SYN0)+1;
    
    if (SDLNet_TCP_Send(sd, SYN0,len) < len)
    {
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    printf("hearts sent\n");
    
    memset(SYN0, '\0', sizeof(SYN0));
    
    result=SDLNet_TCP_Recv(sd,SYN0,MAXLEN);
    printf("%d\n",result);

    printf("%s\n",SYN0);

    if(strcmp(SYN0, "diamonds") == 0)
    {
        len2 = (int) strlen(SYN1)+1;
        if (SDLNet_TCP_Send(sd, SYN1,len) < len)
        {
            fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
        
        memset(SYN1, '\0', sizeof(SYN1));
        do {
            result=SDLNet_TCP_Recv(sd,SYN1,MAXLEN);
        } while (!strcmp(SYN1, "ENDOFTRANS"));
        strcpy(newport, "./game_client ");
        strcat(newport, SYN1);
        printf("commandline argument: %s \n", newport);
        execlp("/bin/sh","sh","-c",newport,NULL);
    }
    
    return 0;
}

