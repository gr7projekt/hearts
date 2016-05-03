/*
funktion och struct för att skapa spelare!
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BORD 4 //max antalet spelar pÂ ett bord

struct player {
    int player;
    int score;
    int trickwin;
}; typedef struct play Play;

Play makePlayer(int player) //ger varje spelare sin plats (0,1,2,3) och sina poäng och antalet vunna händer på en omgång
{
    Play p;

    p.player = player;
    p.score = 0;
    p.trickwin = 0; //detta för att ta reda på vem som börjar kasta nästa runda

    return p;
}

int playmaker(Play whichPlayer[]) //skapar 4 olika spelare
{
    int i;

    for(i = 0; i < BORD; i++)
    {
        whichPlayer[i] = makePlayer(i);
    }
}

int main(void)
{
    int i;
    Play whichPlayer[BORD];
    playmaker(whichPlayer);

    for(i = 0; i < BORD; i++)
    {
        printf("%d %d %d \n", whichPlayer[i].player, whichPlayer[i].score, whichPlayer[i].trickwin); //visar att structen fungerar genom att skriva ut spelare 0-3.
    }
    }

    return 0;
}
