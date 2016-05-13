#include "send.h"

void sendCard(Player player_1[], int nr)
{
    char str[4];
    str[0] = '0'; //player_1[0].id;

    str[1] = player_1[0].game_hand[nr].suit + '0';

    if(player_1[0].game_hand[nr].value == 10)
        str[2] = 'A';
    else if(player_1[0].game_hand[nr].value == 11)
        str[2] = 'B';
    else if(player_1[0].game_hand[nr].value == 12)
        str[2] = 'C';
    else
        str[2] = player_1[0].game_hand[nr].value + '0';

    fprintf(stdout,"player id, Suit,value: %c%c%c \n",str[0],str[1],str[2]);
}
