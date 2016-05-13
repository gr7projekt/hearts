#ifndef LOADMEDIA_H_INCLUDED
#define LOADMEDIA_H_INCLUDED

#include "includes.h"

/** \brief
 *
 * \param dropzone[] SDL_Texture*
 * \param gRenderer SDL_Renderer*
 * \param gSpriteClipsDropzone[] SDL_Rect
 * \return void
 *
 */
void loadMediaDropzone(SDL_Texture *dropzone[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsDropzone[]);

/** \brief
 *
 * \param advertisment[] SDL_Texture*
 * \param gRenderer SDL_Renderer*
 * \param gSpriteClipsAdvertisment[] SDL_Rect
 * \return void
 *
 */
void loadMediaAdvertisment(SDL_Texture *advertisment[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsAdvertisment[]);


/** \brief
 *
 * \param i int
 * \param card[] SDL_Texture*
 * \param gRenderer SDL_Renderer*
 * \param gSpriteClipsClubs[] SDL_Rect
 * \return void
 *
 */
void loadMediaClubs(int i, SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsClubs[]);


/** \brief
 *
 * \param i int
 * \param card[] SDL_Texture*
 * \param gRenderer SDL_Renderer*
 * \param gSpriteClipsDiamonds[] SDL_Rect
 * \return void
 *
 */
void loadMediaDiamonds(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsDiamonds[]);


/** \brief
 *
 * \param i int
 * \param card[] SDL_Texture*
 * \param gRenderer SDL_Renderer*
 * \param gSpriteClipsHearts[] SDL_Rect
 * \return void
 *
 */
void loadMediaHearts(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsHearts[]);


/** \brief
 *
 * \param i int
 * \param card[] SDL_Texture*
 * \param gRenderer SDL_Renderer*
 * \param gSpriteClipsSpades[] SDL_Rect
 * \return void
 *
 */
void loadMediaSpades(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsSpades[]);


/** \brief
 *
 * \param i int
 * \param card_2[] SDL_Texture*
 * \param card_3[] SDL_Texture*
 * \param card_4[] SDL_Texture*
 * \param gRenderer SDL_Renderer*
 * \param gSpriteClipsBack[] SDL_Rect
 * \return void
 *
 */
void loadMediaBack(int i, SDL_Texture *card_2[], SDL_Texture *card_3[], SDL_Texture *card_4[],SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsBack[]);


#endif // LOADMEDIA_H_INCLUDED
