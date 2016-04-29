//
//  players.c
//  Test
//
//  Created by Johan Lipecki on 2016-04-15.
//  Copyright © 2016 Johan Lipecki. All rights reserved.
//

#include "players.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "deck.h"

struct player_parms;
typedef struct player_parms{
    int pos;
    int id;
    int score;
    Card game_hand[13];
    Card won_hand[52];
}Player;

void *play_hand(void *parameters) {
    return NULL;
}

int player_waits_or_plays (int argc, char* argv[])
{
    pthread_t phils[4]; /*Some sort of array of phils are needed*/
    struct player_parms control_player[3];
    int i=0;
    int noPlayers, lock;
    int round = 0;
    /*Overall design of the program
     1. Take in commandline arguments to set up how many phils are going to be
     simulated and if deadlock is going occur. Commandline arguments need to
     be checked and the program needs to exit if they are not in the correct format
     see Advanced Linux Programming for excellent advice on commandline arguments.
     2. Start simulation by starting the phil-threads and let the main program
     print out the contents of the string table declared above. No thread is going
     to communicate with the user but through the string table, it is the main
     program that prints out the contents of the string table. This means that
     we are separating the task of computation/simulation from the task of
     presentation of the results*/
    while(round<48)
    {
        printf("Round %2d: %s\n", round+1, table);
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
     */
    return 0;
}



