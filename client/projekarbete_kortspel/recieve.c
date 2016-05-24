#include "recieve.h"

void seperate(char *trick[],char recieved_trick[],char tmp[])
{
    for(int i = 0;i <4; i++) {
        tmp[0] = recieved_trick[i * 3];
        tmp[1] = recieved_trick[i * 3 + 1];
        tmp[2] = recieved_trick[i * 3 + 2];
        tmp[3] = '\0';

        trick[i] = strdup(tmp);
    }
}

void recieve(char recieved_trick[])
{
    Uint16 port = 1337;

    /* Initialize SDL_net */
    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }


    if (!(sd = SDLNet_UDP_Open(0)))
    {
        fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }


    if (!(pOUT = SDLNet_AllocPacket(512)))
    {

        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

        /* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
        if (SDLNet_UDP_Recv(sd, pOUT)) {
            printf("UDP Packet incoming\n");
            printf("\tData:    %s\n", (char *) pOUT->data);
            printf("\tLen:     %d\n", pOUT->len);
            printf("\thex:     %x\n", pOUT->address.host);
    }
    /* Clean and exit */
    SDLNet_FreePacket(pOUT);
    //SDLNet_FreePacket(pOUT);
    SDLNet_Quit();
}
