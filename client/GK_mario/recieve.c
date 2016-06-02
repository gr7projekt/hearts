#include <SDL_net.h>
#include "recieve.h"
#include "game.h"
//#include "cardStruct.h"

void seperate(char *trick[],char recieved_trick[],char tmp[],int *starting_player)
{
    for(int i = 0;i <4; i++) {
        printf("i: %d\n",i);
        tmp[0] = recieved_trick[i * 3];
        tmp[1] = recieved_trick[i * 3 + 1];
        tmp[2] = recieved_trick[i * 3 + 2];
        tmp[3] = '\0';

        trick[i] = strdup(tmp);

        if(strcmp(trick[i],"EE;")==0)
        {
            *starting_player = i;
        }
    }
}

void recievehand(char recieved_trick[])
{
    //int my_pos= (int) argv[2];
    int my_pos=0;
    char *trick[4];
    DD_trick(trick,my_pos);

    //DD_trick(trick,my_pos);
    printf("trick: ");
    for(int i=0;i<4;i++) printf(" %s",trick[i]);
    char server_ip[25] = "", log_string[40], pid[7];
    udPpacket.data = (Uint8 *) strdup("");
    for(int i=0;i<4;i++) {
        strcat(udPpacket.data, (Uint8 *) trick[i]);
        strcat(udPpacket.data,";");
    }
    printf("\npacket: %s\n", udPpacket.data);
    udPpacket.len = 13;
    int result, len, len2;
    uint16_t port;
    FILE *fd;

    sprintf(pid, ".%d", getpid());
    strcpy(log_string, LOGIN_LOG);
    strcat(log_string, pid);
//    fd = fopen(log_string, "w+");
//    fprintf(fd, "%s\n",MESSAGE);
//    fclose(fd);
    strcpy(server_ip, IP_ADDRESS);
    //port = (uint16_t) atoi(argv[1]);
    port = PORT;

    if (SDLNet_ResolveHost(&ip, server_ip, port) < 0) {
        fprintf(stdout, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(sd = SDLNet_UDP_Open(0))) {
        fprintf(stdout, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

//    fd = fopen(log_string, "a+");
    printf("UDPsocket open\n");
//    fclose(fd);

    // värdet

    //IPaddress *address;
    int channel, chanL;
    channel = SDLNet_UDP_Bind(sd, -1, &ip);

    if (channel == -1) {
        //fd = fopen(log_string,"a+");
        printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
        //fclose(fd);
        // do something because we failed to bind
    }
    else    printf("bound to channel %d\n",channel);
    int i = 0;
    while ((len=SDLNet_UDP_Send(sd, channel, &udPpacket))) {
        if (len < 0) {
            if (i++ > 1) break;
            printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
            chanL = (udPpacket.channel);
            channel = chanL;
            // do something because we failed to send
            // this may just be because no addresses are bound to the channel...
        }
        break;
    }
        // create a new UDPpacket to hold 1024 bytes of data
    UDPpacket *packet;
    packet=SDLNet_AllocPacket(1024);
    if(!packet) {
        printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
    }
        //else
    {
        int quit = 0;
        while (quit == 0) {
                // do stuff with this new packet
            result = SDLNet_UDP_Recv(sd, packet);
            if (result) {

                printf("Received packet data: %s\n", (char *) packet->data);

//                fd = fopen(log_string, "a+");
                printf("Emottaget: %s\n", packet->data);
                strcpy(recieved_trick, packet->data);
//                fclose(fd);
                // SDLNet_FreePacket this packet when finished with it
                SDLNet_FreePacket(packet);
                quit = 1;
            }
        }
    }
}

void receiveontable(char recievetable[])
{
     //int my_pos= (int) argv[2];
     int my_pos=3;
     char *trick[4];
     DD_trick(trick,my_pos);

     //DD_trick(trick,my_pos);
     printf("trick: ");
     for(int i=0;i<4;i++) printf(" %s",trick[i]);
     char server_ip[25] = "", log_string[40], pid[7];
     udPpacket.data = (Uint8 *) strdup("");

    for(int i=0;i<4;i++) {
          strcat(udPpacket.data, (Uint8 *) trick[i]);
          strcat(udPpacket.data,";");
    }

     printf("\npacket: %s\n", udPpacket.data);
     udPpacket.len = 13;
     int result, len, len2;
     uint16_t port;
     FILE *fd;

     sprintf(pid, ".%d", getpid());
     strcpy(log_string, LOGIN_LOG);
     strcat(log_string, pid);
     //fd = fopen(log_string, "w+");
     //fprintf(fd, "%s\n",MESSAGE);
     //fclose(fd);
     strcpy(server_ip, IP_ADDRESS);
     //port = (uint16_t) atoi(argv[1]);
     port = PORT;
     if (SDLNet_ResolveHost(&ip, server_ip, port) < 0) {
         fprintf(stdout, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
         exit(EXIT_FAILURE);
     }

     if (!(sd = SDLNet_UDP_Open(0))) {
         fprintf(stdout, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
         exit(EXIT_FAILURE);
     }
     //fd = fopen(log_string, "a+");
     printf("UDPsocket open\n");
     //fclose(fd);

     // värdet

     //IPaddress *address;
     int channel, chanL;
     channel = SDLNet_UDP_Bind(sd, -1, &ip);

     if (channel == -1) {
         //fd = fopen(log_string,"a+");
         printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
         //fclose(fd);
         // do something because we failed to bind
     }
     else    printf("bound to channel %d\n",channel);
     int i = 0;
     while ((len=SDLNet_UDP_Send(sd, channel, &udPpacket))) {
         if (len < 0) {
             if (i++ > 1) break;
             printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
             chanL = (udPpacket.channel);
             channel = chanL;
             // do something because we failed to send
             // this may just be because no addresses are bound to the channel...
         }
         break;
     }
         // create a new UDPpacket to hold 1024 bytes of data
         UDPpacket *upacket;
         upacket=SDLNet_AllocPacket(1024);
         if(!upacket) {
             printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
         }
         //else
         {
        int quit = 0;
        while (quit == 0) {
                 // do stuff with this new packet
            result = SDLNet_UDP_Recv(sd, upacket);
            if (result) {

                printf("Received packet data: %s\n", (char *) upacket->data);

//                fd = fopen(log_string, "a+");
                printf("Emottaget: %s\n", upacket->data);
                strcpy(recievetable, upacket->data);
//                fclose(fd);
                     // SDLNet_FreePacket this packet when finished with it
                SDLNet_FreePacket(upacket);
                quit = 1;
            }
        }
    }
}
