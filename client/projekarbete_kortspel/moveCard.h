#ifndef MOVECARD_H_INCLUDED
#define MOVECARD_H_INCLUDED

#include "includes.h"

/** \brief
 *
 * \param mouse_x int
 * \param mouse_y int
 * \return void
 *
 */
int liftCard(SDL_Rect initial_pos[0], SDL_Rect p1[], int mouse_x, int mouse_y, bool picked[]);

/** \brief
 *
 * \param p1[] SDL_Rect
 * \param k int
 * \param mouse_x int
 * \param mouse_y int
 * \return void
 *
 */
void moveCard(SDL_Rect p1[], int k, int mouse_x, int mouse_y);

#endif // MOVECARD_H_INCLUDED
