//
//  players.h
//  Test
//
//  Created by Johan Lipecki and Viggo Lundén on 2016-05-03.
//  Copyright © 2016 Johan Lipecki. All rights reserved.
//

#ifndef players_h
#define players_h

#include <stdio.h>
#include "card.h"

void* player_waits_or_plays (char *[]);
// Pekare eftersom pthread_create() tar en pekare
void *play_hand(void *parameters);

struct player_parms;
typedef struct player_parms{
    char guid[33];
    int pos;
    int id;
    int score;
    Card game_hand[13];
    Card won_hand[52];
}Player;

#endif /* players_h */
