#include "loadCard.h"

void loadCard(Card player_client[],Card player_2[], Card player_3[], Card player_4[])
{
    int k=0;
    for(int i=0; i<13; i++) // H�R SKA DET LADDAS IN INFORMATION FR�N SERVERN OM VILKA KORT SOM DELAS UT
    {
        player_client[i].value = i;   //om det �r en 2'a 7'a eller dam
        player_client[i].suit = k;    //vilken f�rg kortet har, 0=kl�ver 1=ruter 2=hj�rter 3=spader
        k++;
        if(k>3)
            k=0;

        player_2[i].value=0;
        player_2[i].suit=0;

        player_3[i].value=0;
        player_3[i].suit=0;

        player_4[i].value=0;
        player_4[i].suit=0;
    }
}
