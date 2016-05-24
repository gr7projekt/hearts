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
    IPaddress ipv4;
    ipv4 = args->address;
    // Bind address to the first free channel
    // UDPsocket udpsock;
    // IPaddress *address;
    int chanL, mottagna_paket;
    uint8_t speila = 1;
    uint8_t hand_data;
    char *str;
    sprintf(str,"%x;%x;%x;%x;",*args->trick[0],*args->trick[1],*args->trick[2],
            *args->trick[3]);
    hand_data = atoi(str);



    // create a UDPsocket on port 6666 (server)
    UDPsocket udPsocket;

    udPsocket=SDLNet_UDP_Open(ipv4.port);
    if(!udPsocket) {
        printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(2);
    }


    UDPpacket spela = createPacket(chanL, &speila, 1, 100, 0, ipv4);
    UDPpacket skicka_hand = createPacket(chanL,&hand_data,sizeof(hand_data),100,0,ipv4);
    UDPpacket mottaget_paket;

    if ((chanL = SDLNet_UDP_Bind(udPsocket, -1, &ipv4)) < 0) {
        syslog(LOG_ERR, "SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
        // do something because we failed to bind
    }

    else {
        while (1) {
            int my_turn=1;
            if (my_turn) {
                if (!(SDLNet_UDP_Send(udPsocket, (&spela)->channel, &spela))) {
                    syslog(LOG_ERR, "%s", strerror(errno));
                    my_turn=0;
                }
                else {
                    sleep(15);
                }
                mottagna_paket = SDLNet_UDP_Recv(udPsocket, &mottaget_paket);
                if(mottagna_paket) {
                    //klientens angivna position uppdaterar handen med kortet som skickats
                    sprintf(args->trick[mottaget_paket.data[0]],"%x%x",mottaget_paket.data[1],mottaget_paket.data[2]);
                }

            }
            else {
                if (!(SDLNet_UDP_Send(udPsocket, (&skicka_hand)->channel, &skicka_hand))) {
                    syslog(LOG_ERR, "%s", strerror(errno));
                    break;
                }
                else {
                    sleep(1);
                }
            }
        }
    }
    return 0;
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



