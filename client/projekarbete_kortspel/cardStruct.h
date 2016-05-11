#ifndef CARDSTRUCT_H_INCLUDED
#define CARDSTRUCT_H_INCLUDED

struct my_Card;
typedef struct my_Card
{
    int suit;
    int value;
}Card;

struct player_parms;
typedef struct player_parms{
    int pos;
    int id;
    int score;
    Card game_hand[13];
    Card won_hand[52];
}Player;

#endif // CARDSTRUCT_H_INCLUDED
