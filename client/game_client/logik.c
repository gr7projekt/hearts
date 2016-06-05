#include "logik.h"

bool myturn(char *trick[], Player player_1[])
{
    if(strcmp(trick[player_1[0].id],"EE")==0)
    {
    //    printf("myturn 1\n");
        return true;
    }
    else if(player_1[0].id == 0)
    {
        if((strcmp(trick[player_1[0].id],"FF")==0 && strcmp(trick[3],"FF")!=0) && strcmp(trick[3],"EE") !=0)
        {
     //       printf("myturn 2\n");
            return true;
        }
        else
        {
     //       printf("myturn 3\n");
            return false;
        }
    }
    else
    {
        if((strcmp(trick[player_1[0].id],"FF")==0 && strcmp(trick[player_1[0].id-1],"FF")!=0) && strcmp(trick[player_1[0].id-1],"EE")!=0){
     //       printf("myturn 4\n");
            return true;
        }
        else
        {
     //       printf("myturn 5\n");
            return false;
        }
    }
}

int whos_turn(Player p1[], Player p2[], Player p3[], Player p4[], char* trick[])
{
    int tmp;

    if((strcmp(trick[0],"EE") == 0) || (strcmp(trick[0],"FF")==0 && strcmp(trick[3],"FF") !=0)){
        tmp = 0;
    }
    else if((strcmp(trick[1],"EE") == 0) || (strcmp(trick[1],"FF")==0 && strcmp(trick[0],"FF") !=0)){
        tmp = 1;
    }
    else if((strcmp(trick[2],"EE") == 0) || (strcmp(trick[2],"FF")==0 && strcmp(trick[1],"FF") !=0)){
        tmp = 2;
    }
    else if((strcmp(trick[3],"EE") == 0) || (strcmp(trick[3],"FF")==0 && strcmp(trick[2],"FF") !=0)){
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

bool checkCard(Player p1[], int nr, bool *brokenHeart, bool picked[], int turn, char *trick[], int whoStarted )
{
    int nrOfHearts = 0;
    int nrOfQueenSpade = 0;
    char tmp_card[4];

    tmp_card[0] = p1[0].game_hand[nr].char_suit;
    tmp_card[1] = p1[0].game_hand[nr].char_value;
    tmp_card[2] = '\0';

    printf("tmp_card: %s\n",tmp_card);

    if(turn == 0){  //första rundan

        if(whoStarted == p1[0].id){ //börjar jag?
            if(tmp_card[0] == '0' && tmp_card[1] == '0')
                return true;
            else{
                printf("2 of club must start!\n");
                return false;
            }
        }


        else{ //annars när jag har 13 kort.

            if(tmp_card[0] == trick[whoStarted][0]){
                printf("following suit, good\n");   //följer jag färg? bra!
                return true;
            }

            else{
                for(int i=0;i<13;i++){
                    if((trick[whoStarted][0] == p1[0].game_hand[i].char_suit)&& !picked[i])
                    {
                        printf("must follow suit\n"); //har jag rätt färg på handen men lagt fel? dåligt!
                        return false;
                    }
                    else if(p1[0].game_hand[i].char_suit == '2' && !picked[i]){ //vilka kort är hjärter på handen?
                        nrOfHearts++;
                    }
                    else if((p1[0].game_hand[i].char_suit == '3' && p1[0].game_hand[i].char_value == 'C') && !picked[i]){
                        nrOfQueenSpade++;
                    }
                    else
                        continue;

                    if(nrOfHearts+nrOfQueenSpade == 13 - turn){ //har jag bara hjärter och spader dam? ok för hjärter, inte damen!
                        printf("Only heart or Queen of spade, play hearts\n");
                        if(strcmp(tmp_card,"3A"))
                            return false;
                        else{
                            *brokenHeart = true;
                            return true;
                        }
                    }
                    else{
                        if(tmp_card[0]== '2' || strcmp(tmp_card,"3A")==0){
                            printf("cant play heart or queen of spade first round if you have a no point card on hand\n");
                            return false;
                        }
                    }
                }
                return true; //om jag nu inte hade rätt färg eller handen inte var full av hjärter så får jag lägga det jag vill
            }
        }
    }

    else if(turn > 0 && turn < 12){
        if(whoStarted == p1[0].id){ //börjar jag?
            if(tmp_card[0] == '2' && !brokenHeart){
                printf("heart not broken!\n");
                return false;
            }
            else
                return true;
        }
        else{
            if(tmp_card[0] == trick[whoStarted][0])
                return true;
            else{
                for(int i=0;i<13;i++){
                    if((trick[whoStarted][0] == p1[0].game_hand[i].char_suit)&& !picked[i]){
                        printf("must follow suit\n"); //har jag rätt färg på handen men lagt fel? dåligt!
                            return false;
                    }
                }
            }
        }
        return true;
    }

    else
        return true;
}
