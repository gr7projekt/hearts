#include "loadCard.h"

void loadCard(Player player_client[],Player player_2[], Player player_3[], Player player_4[])
{
    int k=0;
    for(int i=0; i<13; i++) // HÄR SKA DET LADDAS IN INFORMATION FRÅN SERVERN OM VILKA KORT SOM DELAS UT
    {
        player_client[0].game_hand[i].suit = k;     //vilken färg kortet har, 0=klöver 1=ruter 2=hjärter 3=spader
        player_client[0].game_hand[i].value = i;    //om det är t.ex. en 2'a 7'a eller dam

        player_2[0].game_hand[i].suit = 0;
        player_2[0].game_hand[i].value = 12-i;

        player_3[0].game_hand[i].suit = 3-k;
        player_3[0].game_hand[i].value = i;

        player_4[0].game_hand[i].suit = 3-k;
        player_4[0].game_hand[i].value = 12-i;

        k++;
        if(k>3)
            k=0;
    }
}
