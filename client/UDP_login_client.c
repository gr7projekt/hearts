#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>
#include <SDL_net.h>

#define MESSAGE "# This is the gamelog for the card game Hearts, \n# developed for the network communications course at KTH Haninge, spring term 2016"
#define PORT 41337
#define MAXLEN 1024
#define IP_ADDRESS "130.237.84.89"
#define GAME_CLIENT "game_client "
#define LOGIN_LOG "/var/tmp/udp_log"
#define EXPECTED_RESPONSE "diamonds"
#define USER_DATA "Grupp7;password"
#define SERVER_REPLY "41337;1"

int main(int argc,char *argv[]) {
    IPaddress ip;
    UDPsocket sd;
    UDPpacket udPpacket;
    char server_ip[25] = "", log_string[40], pid[7];
    udPpacket.data = (Uint8 *) strdup("0");
    printf("packet: %s\n", udPpacket.data);
    udPpacket.len = 512;
    int result, len, len2;
    uint16_t port;
    char *numbers= "You what?!";
    FILE *fd;

    sprintf(pid, ".%d", getpid());
    strcpy(log_string, LOGIN_LOG);
    strcat(log_string, pid);
    fd = fopen(log_string, "w+");
    fprintf(fd, "%s\n",MESSAGE);
    fclose(fd);
    strcpy(server_ip, IP_ADDRESS);
    //port = (uint16_t) atoi(argv[1]);
    port = PORT;
    if (SDLNet_ResolveHost(&ip, server_ip, port) < 0) {
        fprintf(fd, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(sd = SDLNet_UDP_Open(0))) {
        fprintf(fd, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    fd = fopen(log_string, "a+");
    printf("UDPsocket open\n");

    //IPaddress *address;
    int channel, chanL;
    channel = SDLNet_UDP_Bind(sd, -1, &ip);

    if (channel == -1) {
        fd = fopen(log_string,"a+");
        fprintf(fd,"SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
        fclose(fd);
        // do something because we failed to bind
    }
    else    printf("bound to channel %d\n",channel);
    int i = 0;
    while ((len=SDLNet_UDP_Send(sd, channel, &udPpacket))){
        if (len< 0) {
            if (i++ > 1) break;
            printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
            chanL = (udPpacket.channel);
            channel = chanL;
            // do something because we failed to send
            // this may just be because no addresses are bound to the channel...
        }
        // create a new UDPpacket to hold 1024 bytes of data
        UDPpacket *packet;
        packet=SDLNet_AllocPacket(1024);
        char *array_of_pointers[20];
        char *tmp="01;15;26;32;";
        if(!packet) {
            printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
            sleep(2);
            continue;

        }
        else {
            // do stuff with this new packet
            result=SDLNet_UDP_Recv(sd, packet);
            if(result) {
                printf("Received packet data: %s\n", (char *) packet->data);

                strcpy(tmp,(char *) packet->data);

                split((char *) packet->data, ';', array_of_pointers);
                printf("Split data: ");
                while (i < 4) printf("%s ", array_of_pointers[i++]);
                printf("\n");
                i = 0;
                fd = fopen(log_string, "a+");
                fprintf(fd, "Emottaget: %s\n", packet->data);
                fclose(fd);
                sleep(2);
                // SDLNet_FreePacket this packet when finished with it
                SDLNet_FreePacket(packet);
            }
        }numbers = strdup(tmp);

        udPpacket.data = (Uint8 *) (numbers);
        sleep(2);

    }

    return 0;
}

