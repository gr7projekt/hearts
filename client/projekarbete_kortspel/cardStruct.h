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
    int relativ_pos;    //klienten ska alltid harelativ_pos 0
    int id;     //identifierar 1 2 3 el 4, kortet placeras relativt till spelarens position
    int score;
    int turn;
    Card game_hand[13];
    Card won_hand[52];
}Player;

#endif // CARDSTRUCT_H_INCLUDED
