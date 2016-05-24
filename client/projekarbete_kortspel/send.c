#include "send.h"

#define IPC "137.237.84.89"

void sendCard(Player player_1[], int nr, char* trick[], char recieved_trick[], Uint16 *port)
{
    char str[4];

    /*  Check for parameters
         if (argc < 3)
         {
         fprintf(stderr, "Usage: %s host port\n", argv[0]);
         exit(EXIT_FAILURE);
         }
         */
    /* Initialize SDL_net */
    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    /* Open a socket on random port */
    if (!(sd = SDLNet_UDP_Open(0)))
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

    p->address.host = srvadd.host;	/* Set the destination host */
    p->address.port = srvadd.port;	/* And destination port */

    str[0] = (char) player_1[0].game_hand[nr].suit + '0';

    if(player_1[0].game_hand[nr].value == 10)
        str[1] = 'A';
    else if(player_1[0].game_hand[nr].value == 11)
        str[1] = 'B';
    else if(player_1[0].game_hand[nr].value == 12)
        str[1] = 'C';
    else
        str[1] = (char) player_1[0].game_hand[nr].value + '0';
    str[2]=';';
    str[3]='\0';
    printf("str[0]: %c\n",str[0]);
    printf("str[1]: %c\n",str[1]);

    recieved_trick[player_1[0].id*3] = str[0]; //*3 d� varje enskilld plats har XX; dvs 3 tecken.. pid*3 f�r startplatsen
    recieved_trick[player_1[0].id*3+1]=str[1];

    trick[player_1[0].id] = strdup(str);

        printf("send recieved_trick: %s\n",recieved_trick); //de här ska skickas

    printf("Send me some\n");
    strcpy((char *)p->data, recieved_trick);
    p->len = strlen((char*)p->data);
    printf("%s\n", (char*)p->data);
    SDLNet_UDP_Send(sd, -1, p);
    /*if (!strcmp((char *)p->data, "quit")) {
        quit = 1;
    }*/

    for(int i=0;i<4;i++)
    {
        printf("%s",trick[i]);
    }
    printf("\n");

    //fprintf(stdout,"player id, SuitValue: %i%s \n",player_1[0].id,trick[player_1[0].id]);
}
