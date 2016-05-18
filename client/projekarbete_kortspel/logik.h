#ifndef LOGIK_H_INCLUDED
#define LOGIK_H_INCLUDED

#include "includes.h"

int whos_turn(Player p1[], Player p2[], Player p3[], Player p4[], char* on_table[]);

/** \brief
 *
 * \param p1[] Player
 * \param nr int
 * \param leadCard int
 * \param brokenHeart int
 * \return bool
 *
 */
bool checkCard(Player p1[], int nr, int leadCard, int brokenHeart, bool picked[],int turn, char *on_table[]);


#endif //LOGIK_H_INCLUDED
