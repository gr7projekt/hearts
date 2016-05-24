/*#if 0
#!/bin/sh
        gcc -Wall `sdl-config --cflags` udps.c -o udps `sdl-config --libs` -lSDL_net

exit
#endif
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPC "127.0.0.1"

#include <SDL_net.h>

        int main(int argc, char **argv)
{
    UDPsocket sd;       /* Socket descriptor */
    UDPpacket *p;
    //UDPpacket *pOUT; /* Pointer to packet memory */
    int quit;
    IPaddress srvadd;
    Uint16 port = 40000;

    /* Initialize SDL_net */
    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }


    if (!(sd = SDLNet_UDP_Open(port)))
    {
        fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    /* Resolve server name  */
    if (SDLNet_ResolveHost(&srvadd, IPC, port) == -1)
    {
        fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", IPC, port, SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(p = SDLNet_AllocPacket(512)))
    {

        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(p = SDLNet_AllocPacket(512)))
    {
        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    p->address.host = srvadd.host;	/* Set the destination host */
    p->address.port = srvadd.port;	/* And destination port */

   // pOUT->address.host = srvadd.host;	/* Set the destination host */
    //pOUT->address.port = srvadd.port;	/* And destination port */

    /*if (SDLNet_ResolveHost(&srvadd, IPC, port) == -1)
    {
        fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", IPC, port, SDLNet_GetError());
        exit(EXIT_FAILURE);
    }*/

    //p->address.host = srvadd.host;	/* Set the destination host */
    //p->address.port = srvadd.port;	/* And destination port */

    /* Main loop */
    quit = 0;
    while (!quit) {
        /* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
        if (SDLNet_UDP_Recv(sd, p)) {
            printf("UDP Packet incoming\n");
            printf("\tData:    %s\n", (char *)p->data);
            printf("\tLen:     %d\n", p->len);
            printf("\thex:     %x\n", p->address.host);

            /* Quit if packet contains "quit" */
            if (strcmp((char *) p->data, "quit") == 0) {
                quit = 1;
            }
           /* strcpy((char *) pOUT->data, "test");
            p->len = strlen((char*)p->data);
            //printf("%s\n", (char*)pOUT->data);
            SDLNet_UDP_Send(sd, -1, pOUT);
            printf("Packet sending\n");*/
        }
    }
    /* Clean and exit */
    SDLNet_FreePacket(p);
    //SDLNet_FreePacket(pOUT);
    SDLNet_Quit();

    return EXIT_SUCCESS;
    }