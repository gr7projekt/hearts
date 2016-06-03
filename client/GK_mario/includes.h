#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <SDL.h> //<SDL.h>
#include <SDL_image.h>  //<SDL_image.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include <unistd.h>

#include "cardStruct.h"
#include "resolution.h"
#include "loadCard.h"
#include "cardPosition.h"
#include "loadMedia.h"
#include "openWeb.h"
#include "moveCard.h"
#include "buttonStruct.h" // The header file containing the struct for buttons.
#include "window.h" // Needed for creating buttons.
#include "button.h" // Needed for creating buttons.
#include "resetTurn.h"
#include "send.h"
#include "logik.h"
#include "position.h"
#include "rendering.h"
#include "recieve.h"
#include "game.h"

#define MESSAGE "# This is the gamelog for the card game Hearts, \n# developed for the network communications course at KTH Haninge, spring term 2016"
#define PORT 41337
#define MAXLEN 1024
#define IP_ADDRESS "130.237.84.89"
//#define IP_ADDRESS "127.0.0.1"
#define GAME_CLIENT "game_client "
#define LOGIN_LOG "udp_log"
#define EXPECTED_RESPONSE "diamonds"
#define USER_DATA "Grupp7;password"
#define SERVER_REPLY "41337;1"

IPaddress ip;
UDPsocket sd;
UDPpacket udPpacket;
//UDPpacket upacket;
UDPpacket uppacket;

#endif // INCLUDES_H_INCLUDED
