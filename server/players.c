//
//  players.c
//  Test
//
//  Created by Johan Lipecki on 2016-04-15.
//  Copyright © 2016 Johan Lipecki. All rights reserved.
//

#include "players.h"




void* player_waits_or_plays (void *arguments) {
    Args *args = (Args*) arguments;
    Player me;
    me.pos = args->pos;
    IPaddress ipv4 = args->address;
    // Bind address to the first free channel
    // UDPsocket udpsock;
    // IPaddress *address;
    int chanL;
    uint8_t speila = 1;
    uint8_t hand_data;
    char *str;
    sprintf(str,"%x%x%x%x%x%x%x%x",*args->hand[0],*args->hand[1],*args->hand[2],
            *args->hand[3],*args->hand[4],*args->hand[5],*args->hand[6],*args->hand[7]);
    hand_data = atoi(str);

    UDPpacket spela = createPacket(chanL, &(speila), 1, 100, 0, ipv4);
    UDPpacket skicka_hand = createPacket(chanL,hand_data,sizeof(*args->hand),100,0,ipv4);

    if ((chanL = SDLNet_UDP_Bind(udpSocket, -1, ipv4)) < 0) {
        syslog(LOG_ERR, "SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
        // do something because we failed to bind
    }
    else {
        while (1) {
            if (my_turn()) {
                if (!(SDLNet_UDP_Send(udpSocket, (&spela)->channel, &spela)))
                    syslog(LOG_ERR, "%s", SDLNET_GetError());
                else {
                    sleep(15);

                    // lägg till spelade kort
                }
            }
            else {
                if (!(SDLNet_UDP_Send(udpSocket, (&skicka_hand)->channel, &skicka_hand)))
                    syslog(LOG_ERR, "%s", SDLNET_GetError());
                else {
                    sleep(1);
                }
            }
        }
    }
}
UDPpacket createPacket(int cnl, uint8_t *data, int len, int maxlen, int status, IPaddress adr){
        UDPpacket pkt;
        pkt.channel = cnl;
        pkt.data = data;
        pkt.len = len;
        pkt.maxlen = maxlen;
        pkt.status = status;
        pkt.address = adr;
        return pkt;
}
/*
int main(){

    pthread_t player[4]; //Some sort of array of players is needed
    Player control_player[4];
    int i=0;
    int lock;
    int round = 0;

     2. Start simulation by starting the phil-threads and let the main program
     print out the contents of the string table declared above. No thread is going
     to communicate with the user but through the string table, it is the main
     program that prints out the contents of the string table. This means that
     we are separating the task of computation/simulation from the task of
     presentation of the results*/
/*

    for(;i<4;i++) pthread_create(&player[i],NULL,player_waits_or_plays,control_player);
    while(round<13)
    {
        printf("Round %2d: %s\n", round+1, hand);
        sleep(1);
        round++;
    }
    /* The above loop runs in parallel to the threads/phils that affect the
     common resource table.
     IMPORTANT: The synchronization must not be through one mutex! We must have
     one mutex per chopstick, that means an array of mutexes is also needed!
     IMPORTANT: Remember that the program should also make deadlock possible
     through commandline arguments, there must be a way to force a deadlock to
     occur. Remember in this context that all thread-functions are to be based on
     one function, philosophize(), and that this function is the same for all
     threads.
     Of course it can behave differently for different philosopher-id's, but
     it must be one function which needs to be written to enable a forced deadlock
     so we can compare and understand why it normally avoids deadlock.
     3. When the loop has finished, all the threads are joined to the main program
     and then the main program exits.
     return 0;
}
*/



