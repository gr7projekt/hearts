#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
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

#define IPC "130.237.84.89"

UDPsocket sd;
IPaddress srvadd;
UDPpacket *p;
UDPpacket *pOUT;

#endif // INCLUDES_H_INCLUDED
