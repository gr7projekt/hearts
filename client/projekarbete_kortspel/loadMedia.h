#ifndef LOADMEDIA_H_INCLUDED
#define LOADMEDIA_H_INCLUDED

#include <SDL_image.h>
#include "resolution.h"

/** \brief
 *
 * \return void
 *
 */
void loadMediaAdvertisment(SDL_Texture *advertisment[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsAdvertisment[]);

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void loadMediaClubs(int i, SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsClubs[]);

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void loadMediaDiamonds(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsDiamonds[]);

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void loadMediaHearts(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsHearts[]);

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void loadMediaSpades(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsSpades[]);

/** \brief
 *
 * \param i int
 * \return void
 *
 */
void loadMediaBack(int i, SDL_Texture *card_2[], SDL_Texture *card_3[], SDL_Texture *card_4[],SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsBack[]);


#endif // LOADMEDIA_H_INCLUDED
