#ifndef RENDERING_H_INCLUDED
#define RENDERING_H_INCLUDED

#include "includes.h"


/** \brief
 * Funktionen tar reda p� den relativa positionen till de lagda korten f�r varje enskilld klient.
 * Med hj�lp av sitt exakta id renderas samma kort p� olika platser med den relativa positionen.
 * Funktionen kollar sedan om en spelare lagt ett kort f�r om den inte �nnu lagt ett kort s� renderas inget p� deras plats.
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
 * \param card1[] SDL_Texture*
 * \param card2[] SDL_Texture*
 * \param card3[] SDL_Texture*
 * \param card4[] SDL_Texture*
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
                      SDL_Texture* card1[], SDL_Texture* card2[], SDL_Texture* card3[], SDL_Texture* card4[],
                      Player p1[], Player p2[], Player p3[], Player p4[]);

#endif //RENDERING_H_INCLUDED
