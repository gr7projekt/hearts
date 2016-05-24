/*
Funktion f�r att ta reda p� n�sta spelare via stick vinst, b�r mergas med andra funktioner
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BORD 4

struct play {
    int player;
    int score;
    int trickwin;
}; typedef struct play Play;

Play makePlayer(int player)
{
    Play p;

    p.player = player;
    p.score = 0;
    p.trickwin = 0;

    return p;
}

int playMaker(Play whichPlayer[])
{
    int i;

    for(i = 0; i < BORD; i++)
    {
        whichPlayer[i] = makePlayer(i);
    }
}

int nextPlayer(Play whichPlayer[]) //Tittar �ver allas h�nder, "vunna" f�r att avg�ra vem som har mest, f�r att sedan g�ra den playern till den f�rsta att kasta n�sta tur.
{
    int winner = 0, begin, i;

    for( i=0; i < BORD; i++)
    {
        if(whichPlayer[i].trickwin > winner)
        {
            winner = whichPlayer[i].trickwin;
            begin = whichPlayer[i].player;
        }
    }
}

int main(void)
{
    int i;
    Play whichPlayer[BORD];
    playMaker(whichPlayer);

    for(i = 0; i < BORD; i++)
    {
        printf("\n Player: %d Score: %d wins on hand: %d \n", whichPlayer[i].player, whichPlayer[i].score, whichPlayer[i].trickwin);

    return 0;
}
