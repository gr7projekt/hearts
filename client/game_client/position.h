#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include "includes.h"

/** \brief bes�mmer b�de den relativa, p1[].relativ_pos=0 och p1[].id=absoluta pos
 *
 * \param p1[] Player
 * \param p2[] Player
 * \param p3[] Player
 * \param p4[] Player
 * \return void
 *
 */
void position(Player p1[], Player p2[], Player p3[], Player p4[]);

/** \brief nollst�ller spelarnas po�ng n�r spelet ska b�rja, s� det visas att alla har 0 po�ng.
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
