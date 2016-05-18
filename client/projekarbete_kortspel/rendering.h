#ifndef RENDERING_H_INCLUDED
#define RENDERING_H_INCLUDED

#include "includes.h"

void renderPlayedCard(SDL_Renderer *gRenderer, char *on_table[], SDL_Rect played_pos[], int whoIsPlaying, SDL_Rect gSpriteClipsClubs[], SDL_Rect gSpriteClipsDiamonds[], SDL_Rect gSpriteClipsHearts[], SDL_Rect gSpriteClipsSpades[]);

#endif //RENDERING_H_INCLUDED
