#include "loadCard.h"

void loadCard(Player player_client[],Player player_2[], Player player_3[], Player player_4[], char recieved_str[])
{
    int k=0;
    for(int i=0; i<13; i++) // H�R SKA DET LADDAS IN INFORMATION FR�N SERVERN OM VILKA KORT SOM DELAS UT
    {
        //tilldelar char till handen.
        player_client[0].game_hand[i].char_suit = recieved_str[i*3];
        player_client[0].game_hand[i].char_value = recieved_str[i*3+1];

        //omvandlar chars till ints.
        player_client[0].game_hand[i].suit = player_client[0].game_hand[i].char_suit - '0';

        if(player_client[0].game_hand[i].char_value == 'c')
          player_client[0].game_hand[i].value = 12;
        else if(player_client[0].game_hand[i].char_value == 'b')
          player_client[0].game_hand[i].value = 11;
        else if(player_client[0].game_hand[i].char_value == 'a')
          player_client[0].game_hand[i].value = 10;
        else
          player_client[0].game_hand[i].value = player_client[0].game_hand[i].char_value - '0';

//        h�rdkordat f�r tester
//
//        player_client[0].game_hand[i].suit = 3-k;     //vilken f�rg kortet har, 0=kl�ver 1=ruter 2=hj�rter 3=spader
//        player_client[0].game_hand[i].value = i;    //om det �r t.ex. en 2'a 7'a eller dam
//
//        k++;
//        if(k>3)
//            k=0;

        player_2[0].game_hand[i].suit = 0;
        player_2[0].game_hand[i].value = 0;

        player_3[0].game_hand[i].suit = 0;
        player_3[0].game_hand[i].value = 0;

        player_4[0].game_hand[i].suit = 0;
        player_4[0].game_hand[i].value = 0;
    }

    sortHand(player_client);
}

void sortHand(Player player_client[])
{
    int tmp_suit;
    int tmp_value;

    for(int j = 0 ; j < 12 ; j++)
    {
        for(int i = 0 ; i < 12 - j ; i++)
        {
            if(player_client[0].game_hand[i].suit > player_client[0].game_hand[i+1].suit)
            {
                tmp_suit = player_client[0].game_hand[i].suit;
                tmp_value = player_client[0].game_hand[i].value;

                player_client[0].game_hand[i].suit = player_client[0].game_hand[i+1].suit;
                player_client[0].game_hand[i].value = player_client[0].game_hand[i+1].value;

                player_client[0].game_hand[i+1].suit = tmp_suit;
                player_client[0].game_hand[i+1].value = tmp_value;
            }
        }
    }
}
