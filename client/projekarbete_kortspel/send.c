#include "send.h"

void sendCard(Player player_1[], int nr, char* trick[], char recieved_trick[])
{
    char str[4];

    str[0] = (char) player_1[0].game_hand[nr].suit + '0';

    if(player_1[0].game_hand[nr].value == 10)
        str[1] = 'A';
    else if(player_1[0].game_hand[nr].value == 11)
        str[1] = 'B';
    else if(player_1[0].game_hand[nr].value == 12)
        str[1] = 'C';
    else
        str[1] = (char) player_1[0].game_hand[nr].value + '0';
    str[2]=';';
    str[3]='\0';
    printf("str[0]: %c\n",str[0]);
    printf("str[1]: %c\n",str[1]);

    recieved_trick[player_1[0].id*3] = str[0]; //*3 då varje enskilld plats har XX; dvs 3 tecken.. pid*3 för startplatsen
    recieved_trick[player_1[0].id*3+1]=str[1];

    trick[player_1[0].id] = strdup(str);


    for(int i=0;i<4;i++)
    {
        printf("%s",trick[i]);
    }
    printf("\n");

    //fprintf(stdout,"player id, SuitValue: %i%s \n",player_1[0].id,trick[player_1[0].id]);
}
