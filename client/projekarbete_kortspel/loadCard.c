#include "loadCard.h"

void loadCard(Player player_client[],Player player_2[], Player player_3[], Player player_4[])
{
    int k=0;
    for(int i=0; i<13; i++) // H�R SKA DET LADDAS IN INFORMATION FR�N SERVERN OM VILKA KORT SOM DELAS UT
    {
        player_client[0].game_hand[i].suit = k;     //vilken f�rg kortet har, 0=kl�ver 1=ruter 2=hj�rter 3=spader
        player_client[0].game_hand[i].value = i;    //om det �r t.ex. en 2'a 7'a eller dam

        player_2[0].game_hand[i].suit = 0;
        player_2[0].game_hand[i].value = 0;

        player_3[0].game_hand[i].suit = 0;
        player_3[0].game_hand[i].value = 0;

        player_4[0].game_hand[i].suit = 0;
        player_4[0].game_hand[i].value = 0;

        k++;
        if(k>3)
            k=0;
    }
}
