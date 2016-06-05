#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "game.h"
#include <SDL2/SDL_net.h>
#include <SDL2/SDL.h>

#define PORT 1337
#define MAXLEN 1024
#define IP_ADDRESS "130.237.84.89"
#define GAME_CLIENT "game_client "
#define LOGIN_LOG "/var/tmp/login_log"
#define EXPECTED_RESPONSE "diamonds"
#define USER_DATA "Grupp7;password"
#define SERVER_REPLY "41337;1"

void login(char [],char []);
int main(void)
{
    IPaddress ip;
    TCPsocket sd;
    char server_ip[25] = "", newport[MAXLEN], SYN0[MAXLEN] = "hearts", SYN1[MAXLEN] = "port", log_string[40], pid[7];

    int result, len, len2;
    uint16_t port;
    FILE *fd;
    
    sprintf(pid,".%d",getpid());
    strcpy(log_string, LOGIN_LOG);
    //strcat(log_string, pid);
    fd = fopen(log_string,"w+");
    fprintf(fd,"open for business!\n");
    fclose(fd);
    fd = fopen(log_string,"a+");

    strcpy(server_ip, IP_ADDRESS);
    port = PORT;
    
    if (SDLNet_ResolveHost(&ip, server_ip, port) < 0)
    {
        fprintf(fd, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    
    if (!(sd = SDLNet_TCP_Open(&ip)))
    {
        fprintf(fd, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    fd = fopen(log_string,"a");
    fprintf(fd,"socket open\n");
    printf("open\n");
    
    
    len = (int) strlen(SYN0)+1;
    
    if (SDLNet_TCP_Send(sd, SYN0,len) < len)
    {
        fprintf(fd, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    printf("hearts sent\n");
    
    memset(SYN0, '\0', sizeof(SYN0));
    
    result=SDLNet_TCP_Recv(sd,SYN0,MAXLEN);
    printf("Recv: %d\n",result);

    fprintf(fd,"%s\n",SYN0);

    if(strcmp(SYN0, EXPECTED_RESPONSE) == 0) {
        len2 = (int) strlen(SYN1) + 1;
        if (SDLNet_TCP_Send(sd, SYN1, len2) < len2) {
            printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
        printf("SDLNet_TCP_Sent: %s\n", SYN1);

        memset(SYN1, '\0', sizeof(SYN1));
        // Servern skickar "ENDOFTRANS" efter varje ACK
        // Klienten väntar på ett portnummer(40-50 k) och spelarposition[0:3]
        do {
            result = SDLNet_TCP_Recv(sd, SYN1, MAXLEN);
            printf("Recv: %s \n", SYN1);
            sleep(2);
        } while (!strcmp(SYN1, "ENDOFTRANS"));  // så länge inget nytt skickas tar vi en tupplur på 2 s i taget

        char user_name[100] = {'0'};
        char password[30] = {'0'};
        char tmp[100];
        char *array_of_pointers[4];

        if (!strcmp(SYN1, "account")) {
            while (!strcmp(SYN1, "account")) {
                login(user_name, password);
                len2 = (int) sizeof(user_name + 1);
                if (SDLNet_TCP_Send(sd, user_name, len2) < len2) printf("%s*", strerror(errno));
                printf("Sent: %s\n", user_name);
                sleep(1);
                printf("Characters received: %d\n", SDLNet_TCP_Recv(sd, SYN1, MAXLEN));
            }
            strcpy(tmp,SYN1);
            separate_strings(tmp,";",array_of_pointers, sizeof((array_of_pointers)));
        }
        else separate_strings(SERVER_REPLY,";",array_of_pointers, sizeof((array_of_pointers)));
        //sammanfoga strängen som startar spelklienten
        strcpy(newport, "./");
        strcat(newport, GAME_CLIENT);

        //lägg till portnumret och starta en ny spelprocess
        strcat(newport, SYN1);
        printf("commandline argument: %s %s \n", array_of_pointers[0],array_of_pointers[1]);
        system(newport);
        fprintf(fd, "%s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    else fprintf(fd, "Returned error string: %s\n", SYN0);
    fclose(fd);
    return -1;
}
void login(char user_name[],char password[]){
    printf("Ange användarnamn: \n");
    fgets(user_name, sizeof(user_name)+1,stdin);
    user_name[strlen(user_name)-1]=';';
    printf("Ange lösenord: \n");
    fgets(password, sizeof(password)+1,stdin);
    password[strlen(password)-1]='\0';
    strcat(user_name,password);
}

