#ifndef CARDPOSITION_H_INCLUDED
#define CARDPOSITION_H_INCLUDED

#include <SDL_image.h>
#include "resolution.h"

#define DISTANCE_X 35
#define DISTANCE_Y 15

/** \brief
 *
 *
 *card position initierar kortens plats, allts� rutorna som de placeras i, p� spelbordet
 */

void initCardPosition(SDL_Rect p1[],SDL_Rect p2[], SDL_Rect p3[], SDL_Rect p4[],SDL_Rect adv[], SDL_Rect drop[]);

#endif // CARDPOSITION_H_INCLUDED
