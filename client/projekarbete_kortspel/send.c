#include "send.h"

void sendCard(Player player_1[], int nr, char *on_table[])
{
    char str[4];

    str[0] = player_1[0].game_hand[nr].suit + '0';

    if(player_1[0].game_hand[nr].value == 10)
        str[1] = 'A';
    else if(player_1[0].game_hand[nr].value == 11)
        str[1] = 'B';
    else if(player_1[0].game_hand[nr].value == 12)
        str[1] = 'C';
    else
        str[1] = player_1[0].game_hand[nr].value + '0';
    str[2]=';';
    str[3]='\0';

    on_table[player_1[0].id] = str; //char to str http://stackoverflow.com/questions/14344130/convert-char-array-to-string-use-c

    for(int i=0;i<4;i++)
    {
        printf("%s",on_table[i]);
    }
    printf("\n");

    fprintf(stdout,"player id, SuitValue: %i%s \n",player_1[0].id,on_table[player_1[0].id]);
}
