//
//  players.h
//  Test
//
//  Created by Johan Lipecki and Viggo Lundén on 2016-05-03.
//  Copyright © 2016 Johan Lipecki. All rights reserved.
//

#ifndef players_h
#define players_h

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
#include <errno.h>
#include "game.h"
#define BUFLEN 512

void *player_waits_or_plays (void *);
struct game_struct;
typedef struct game_struct{

    char *trick[4];
    char *hand[13];
    char *hands[4][13];
    char *deck[52];
    char buffer[4][40];
    int trick_score[4];
    int hand_scores[4];
    int round_score[4];


}Game;
struct player_parms;
typedef struct player_parms{
    int pos;
    int *sockfd;
    Game *game;
    struct sockaddr_in *si_me;
    struct sockaddr_in *si_other;
}Player;



#endif /* players_h */
