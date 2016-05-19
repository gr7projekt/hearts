#include "logik.h"

bool myturn(char *trick[], Player player_1[])
{
    if(strcmp(trick[player_1[0].id],"EE;")==0)
    {
        printf("myturn 1\n");
        return true;
    }
    else if(player_1[0].id == 0)
    {
        if((strcmp(trick[player_1[0].id],"FF;")==0 && strcmp(trick[3],"FF;")!=0) && strcmp(trick[3],"EE;") !=0)
        {
            printf("myturn 2\n");
            return true;
        }
        else
        {
            printf("myturn 3\n");
            return false;
        }
    }
    else
    {
        if((strcmp(trick[player_1[0].id],"FF;")==0 && strcmp(trick[player_1[0].id-1],"FF;")!=0) && strcmp(trick[player_1[0].id-1],"EE;")!=0){
            printf("myturn 4\n");
            return true;
        }
        else
        {
            printf("myturn 5\n");
            return false;
        }
    }
}

int whos_turn(Player p1[], Player p2[], Player p3[], Player p4[], char* trick[])
{
    int tmp;

    if((strcmp(trick[0],"EE;") == 0) || (strcmp(trick[0],"FF;")==0 && strcmp(trick[3],"FF;") !=0)){
        tmp = 0;
    }
    else if((strcmp(trick[1],"EE;") == 0) || (strcmp(trick[1],"FF;")==0 && strcmp(trick[0],"FF;") !=0)){
        tmp = 1;
    }
    else if((strcmp(trick[2],"EE;") == 0) || (strcmp(trick[2],"FF;")==0 && strcmp(trick[1],"FF;") !=0)){
        tmp = 2;
    }
    else if((strcmp(trick[3],"EE;") == 0) || (strcmp(trick[3],"FF;")==0 && strcmp(trick[2],"FF;") !=0)){
        tmp = 3;
    }
    else
        tmp = 4;
//    printf("tmp: %i\n",tmp);

    if(p1[0].id == tmp)
        return p1[0].relativ_pos;
    else if(p2[0].id == tmp)
        return p2[0].relativ_pos;
    else if(p3[0].id == tmp)
        return p3[0].relativ_pos;
    else if(p4[0].id == tmp)
        return p4[0].relativ_pos;
    else
        return 4;
}

bool checkCard(Player p1[], int nr, int leadCard, int brokenHeart, bool picked[], int turn, char *trick[] )
{
    int no_played = 0;
    int i_play = 0;

    for(int i=0; i<4; i++){
        if(strcmp(trick[i],"FF;") == 0)
            no_played ++;
        else if(strcmp(trick[p1[0].id],"EE;") == 0)
            i_play ++;
    }
    printf("no_played: %i\n",no_played);
    printf("i_play: %i\n",i_play);



//
//    if(no_played == 3 && i_play == 1)    //om jag är första spelaren som ska lägga ut ett kort.
//    {
//        if(turn == 0)
//        {
//
//        }
//        else if(turn > 0 && turn < 12)
//        {
//
//        }
//        else    //turn = sista rundan
//            return true;
//    }
//
//    else    //om jag inte är första spelaren
//    {
//        if(turn == 0)
//        {
//
//        }
//        else if(turn > 0 && turn < 12)
//        {
//
//        }
//        else    //turn = sista rundan
//            return true;
//    }





    int count_card = 0;
    int count_picked = 0;

    //LOGIK 1 - samma färg: OK
    if(p1[0].game_hand[nr].suit == leadCard)
    {
        printf("following suit, ok \n");
        return true;
    }

    //LOGIK 2 - om hjärter inte brutits, kolla att vi inte lägger ett hjärter
    //SKA ENDAST SKE OM JAG BÖRJAR
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
