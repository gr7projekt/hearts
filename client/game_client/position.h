#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include "includes.h"

/** \brief besämmer både den relativa, p1[].relativ_pos=0 och p1[].id=absoluta pos
 *
 * \param p1[] Player
 * \param p2[] Player
 * \param p3[] Player
 * \param p4[] Player
 * \return void
 *
 */
void position(Player p1[], Player p2[], Player p3[], Player p4[]);

/** \brief nollställer spelarnas poäng när spelet ska börja, så det visas att alla har 0 poäng.
 *
 * \param p1[] Player
 * \param p2[] Player
 * \param p3[] Player
 * \param p4[] Player
 * \return void
 *
 */
void zeropoint(Player p1[], Player p2[], Player p3[], Player p4[]);

#endif  //POSITION_H_INCLUDED
