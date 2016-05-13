#include "logik.h"

bool checkCard(Player p1[], int nr, int leadCard, int brokenHeart, bool picked[])
{
    int count_card = 0;
    int count_picked = 0;

    //LOGIK 1 - samma f�rg: OK
    if(p1[0].game_hand[nr].suit == leadCard)
    {
        printf("following suit, ok \n");
        return true;
    }

    //LOGIK 2 - om hj�rter inte brutits, kolla att vi inte l�gger ett hj�rter
    //SKA ENDAST SKE OM JAG B�RJAR
//    if(brokenHeart == false)
//    {
//        if(p1[0].game_hand[nr].suit == 2)
//        {
//            printf("can't play heart, heart not broken\n");
//            return false;
//        }
//        if(p1[0].game_hand[nr].suit == 3 && p1[0].game_hand[nr].value == 10)
//        {
//            printf("cant play queen of spade, heart not broken\n");
//            return false;
//        }
//    }

    for(int i=0; i<13; i++)
    {
        if(picked[i])
        {
            count_picked++;
            printf("i: %i\n",i);
        }
        if(p1[0].game_hand[i].suit != leadCard && !picked[i])
        {
            count_card++;
        }
    }
    printf("count_card: %i\n",count_card);
    printf("count_picked: %i\n",count_picked);

    if(count_card == 13 - count_picked)
    {
        printf("play anything\n");
        return true;
    }
    else
    {
        printf("must follow suit.\n");
        return false;
    }
    printf("ingen logik\n");
    return true;
}
