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
    Uint16 port = 41337;
    int retval;

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

    if (SDLNet_ResolveHost(&srvadd, IPC, port) == -1) {
        fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", IPC, port, SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(pOUT = SDLNet_AllocPacket(512)))
    {
        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    if (!(p = SDLNet_AllocPacket(512))) {
        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    pOUT->address.host = srvadd.host;    /* Set the destination host */
    pOUT->address.port = srvadd.port;    /* And destination port */

    p->address.host = srvadd.host;    /* Set the destination host */
    p->address.port = srvadd.port;    /* And destination port */


    strcpy((char *)p->data, "hello!");
    p->len = strlen((char*)p->data);
    if(SDLNet_UDP_Send(sd, -1, p)) {
        //printf("Skickat\n");
    }

    //int quit = 0;
    /* Wait a packet. UDP_Recv returns 1 if a packet is coming recieved, -1 on error */
    //while(quit == 0) {
        if (retval = SDLNet_UDP_Recv(sd, pOUT)) {
            printf("UDP Packet incoming\n");
            printf("\tData:    %s\n", (char *) pOUT->data);
            printf("\tLen:     %d\n", pOUT->len);
            printf("\thex:     %x\n", pOUT->address.host);
    //        quit = 1;
        }
        printf("retval: %d\n",retval);

    //}
    /* Clean and exit */
    SDLNet_FreePacket(pOUT);
    SDLNet_FreePacket(p);
    SDLNet_Quit();
}
