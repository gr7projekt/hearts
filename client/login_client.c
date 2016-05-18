#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>

#define PORT 1337
#define MAXLEN 1024
#define IP_ADDRESS "130.237.84.89"
#define GAME_CLIENT "game_client "
#define LOGIN_LOG "/var/tmp/login_log"
#define EXPECTED_RESPONSE "diamonds"
#define USER_DATA "Grupp7;password"

int main(void)
{
    IPaddress ip;
    TCPsocket sd;
    char server[25] = "", newport[MAXLEN], SYN0[MAXLEN] = "hearts", SYN1[MAXLEN] = "port", log_string[40], pid[7];
    int port, result, len, len2, fd;
    
    sprintf(pid,".%d",getpid());
    strcpy(log_string, LOGIN_LOG);
    strcat(log_string, pid);
    fd = open(log_string,O_RDWR|O_CREAT,0640);
    close(2);
    dup(fd);
    
    strcpy(server, IP_ADDRESS);
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
    freopen(LOGIN_LOG,"w",stderr);
    printf("Recv: %d\n",result);

    printf("%s\n",SYN0);

    if(strcmp(SYN0, EXPECTED_RESPONSE) == 0)
    {
        len2 = (int) strlen(SYN1)+1;
        if (SDLNet_TCP_Send(sd, SYN1,len2) < len2)
        {
            fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "SDLNet_TCP_Sent: %s\n",SYN1);
        
        memset(SYN1, '\0', sizeof(SYN1));
        // Servern skickar "ENDOFTRANS" efter varje ACK
        // Klienten väntar på ett portnummer(40-50 k) och spelarposition[0:3]
        do {
            result=SDLNet_TCP_Recv(sd,SYN1,MAXLEN);
            printf("Recv: %s ",SYN1);
            system("xterm");
            wait(0);
            sleep(3);
        } while (strcmp(SYN1, "account"));
        
        //sammanfoga strängen som startar spelklienten
        strcpy(newport, "./");
        strcat(newport, GAME_CLIENT);
        
        //lägg till portnumret och starta en ny spelprocess
        strcat(newport, SYN1);
        printf("commandline argument: %s \n", newport);
        execlp("/bin/sh","sh","-c",newport,NULL);
        fprintf(stderr, "%s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else fprintf(stderr, "Returned error string: %s\n", SYN0);
    return -1;
}

