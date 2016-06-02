#ifndef RENDERING_H_INCLUDED
#define RENDERING_H_INCLUDED

#include "includes.h"


/** \brief
 * Funktionen tar reda på den relativa positionen till de lagda korten för varje enskilld klient.
 * Med hjälp av sitt exakta id renderas samma kort på olika platser med den relativa positionen.
 * Funktionen kollar sedan om en spelare lagt ett kort för om den inte ännu lagt ett kort så renderas inget på deras plats.
 *
 * \param gRenderer SDL_Renderer*
 * \param trick[] char*
 * \param played_pos[] SDL_Rect
 * \param whoIsPlaying int
 *
 * \param gSpriteClipsClubs[] SDL_Rect
 * \param gSpriteClipsDiamonds[] SDL_Rect
 * \param gSpriteClipsHearts[] SDL_Rect
 * \param gSpriteClipsSpades[] SDL_Rect
 *
 * \param card_club[] SDL_Texture*
 * \param card_diamond[] SDL_Texture*
 * \param card_heart[] SDL_Texture*
 * \param card_spade[] SDL_Texture*
 *
 * \param p1[] Player
 * \param p2[] Player
 * \param p3[] Player
 * \param p4[] Player
 * \return void
 *
 */
void renderPlayedCard(SDL_Renderer *gRenderer, char *trick[], SDL_Rect played_pos[], int whoIsPlaying,
                      SDL_Rect gSpriteClipsClubs[], SDL_Rect gSpriteClipsDiamonds[], SDL_Rect gSpriteClipsHearts[], SDL_Rect gSpriteClipsSpades[],
                      SDL_Texture* card_club[],SDL_Texture* card_diamond[], SDL_Texture* card_heart[], SDL_Texture* card_spade[],
                      Player p1[], Player p2[], Player p3[], Player p4[]);

#endif //RENDERING_H_INCLUDED
