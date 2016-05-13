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
#include "card.h"
#include "SDL2/SDL_net.h"
#include "SDL2/SDL.h"


typedef struct {
    int pos;
    IPaddress address;
    char *trick[4];

}Args;

void* player_waits_or_plays (void *);
// Pekare eftersom pthread_create() tar en pekare
UDPpacket createPacket(int, uint8_t, int, int, int, IPaddress );

struct player_parms;
typedef struct player_parms{
    int pos;
    int id;
    int score;
    Card game_hand[13];
    Card won_hand[52];
}Player;

#endif /* players_h */
