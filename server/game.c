//
// Created by Johan Lipecki on 2016-05-12.
//



#include "game.h"

int calculate_trick(char* card[]){
    int score = 0;
    for(int i=0;i<4;i++){
        if (is_hearts(*card[i])) score += 1;
        else if (is_queen_of_spades(*card)) score += 13;
    }
    return score;
}
void update_round_score(int *round_score[],char *card[]){
    for(int i=0;i<4;i++) *round_score[i] += *card[i];
}

int check_winner(char *card[],int player_pos_of_starting_hand) {
    char hand_suit = card[player_pos_of_starting_hand][0];
    char high_card[] = {NULL, NULL,'\0'};
    char tmp_card[3];
    int winner_pos=player_pos_of_starting_hand;
    for (int i = 0;i < 4;i++) {
        strcpy(tmp_card,*card[i]);
        if (card[i][0] == hand_suit) if (card[i][1] > high_card[1]) {
            strcpy(high_card,tmp_card);
            winner_pos = i;
        }
    }
    return winner_pos;
}
bool is_hearts(char suit) {
    if ((suit == '2')) return true;
    else return false;
}
bool is_queen_of_spades(char card[]){
    if(strcmp(card,"0A")) return true;
    else return false;
}
bool is_two_of_clubs(char card[]){
    if(strcmp(card,"00")) return true; // 2 of Clubs
    else return false;
}
void search_hand(char* hand[],int *has_00, int my_pos){
    for(int i = 0;i < 13;i++){
        if (has_00(card[i])) *next_player = my_pos;
    }
}
bool is_hundred(char score[]){
    for(int i = 0;i < 4;i++) if(score[i] >= 100) return true;
    return false;
}