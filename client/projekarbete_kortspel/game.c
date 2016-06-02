//
// Created by Johan Lipecki on 2016-05-12.
//




#include "game.h"

int calculate_trick(char* card[]){
    int score = 0;
    for(int i=0;i<4;i++){
        if (is_hearts(*card[i])) score += 1;
        else if (is_queen_of_spades(card[i])) score += 13;
    }
    return score;
}
int check_winner(char *trick[],int player_pos_of_starting_hand) {
    char hand_suit = trick[player_pos_of_starting_hand][0];
    char high_card[3] = {'\0'};
    char tmp_card[3] = {'\0'};
    int winner_pos=player_pos_of_starting_hand;
    for (int i = 0;i < 4;i++) {
        strcpy(tmp_card,trick[i]);
        if (trick[i][0] == hand_suit) if (trick[i][1] > high_card[1]) {
            strcpy(high_card,tmp_card);
            winner_pos = i;
        }
    }
    return winner_pos;
}
// adds the score "trick_score" at index "trick winner" of array hand_score
void update_hand_score(int hand_score[],int trick_score,int trick_winner){
    hand_score[trick_winner] += trick_score;
}
//Prints a list of "len" items to the stream pointed to by "FILE *fp"
//the items in "list" are split by "separators"
void print_list(FILE *fp,char *separators, int list[], int len){
    for (int i = 0; i < len;) fprintf(fp,"%d%s",list[i++],separators);
}
// Increments list0 with list1, from "index" to "len" -1,
// and puts result in list0. To add a single value to a list of items,
// match "index" with list[index] and set "len" to "index"+1.
void add_list1_to_list0(int list0[],int list1[], int index,int len) {
    for(int i=index;i<len;i++)list0[i] += list1[i];
}
// The same as add_list1_to_list0 with index=0 and len=no_of_players.
// Therefore it is not as flexible, but it is easier to use.
// To add a single value, provide a list with one non-zero value (e.g. {0,0,1337,0})
void update_round_score(int round_score[], int hand_score[], int no_of_players) {
    for(int i=0;i<no_of_players;i++) round_score[i] += hand_score[i];
}

bool is_hearts(char suit) {
    return suit == '2' ? true : false;
}
bool is_queen_of_spades(char card[]){
    return !strcmp(card, "3A") ? true : false;
}
bool is_two_of_clubs(char card[]){
    return !strcmp(card, "00") ? true : false; // 2 of Clubs
}
bool do_I_start(char* hand[]){
    for(int i = 0;i < 13;i++) if (is_two_of_clubs(hand[i])) return true;
    return false;
}
void is_twenty_six(int hand_score[]){
    for(int i=0;i<4;i++) if (hand_score[i]==26){
            hand_score[i] = 0;
            hand_score[(i+1)%4] = 26;
            hand_score[(i+2)%4] = 26;
            hand_score[(i+3)%4] = 26;
            break;
        }
}
//Checks which player holds two of clubs (i.e. has card "00")
//Returns an integer with the player position
int who_starts(char **player_hands[4]){
    for(int i=0;i<4;i++) {
        if(do_I_start(player_hands[i])) return i;
    }
    exit(EXIT_FAILURE);
}
bool is_hundred(int score[]){
    for(int i = 0;i < 4;i++) if(score[i] >= 100) return true;
    return false;
}
void separate_strings(char *inputstring, const char *separators, char *fill_this_array_of_pointers[],int size_of_array_to_fill) {
    //From strsep() manual:
    // The following uses strsep() to parse a string,
    // containing tokens delimited by *separators, into an argument vector:
    char **array_pointers;
    char* string;
    string = strdup(inputstring);

    for (array_pointers = fill_this_array_of_pointers; (*array_pointers = strsep(&string, separators)) != NULL;)
        if (**array_pointers != '\0') if (++array_pointers >= &fill_this_array_of_pointers[size_of_array_to_fill]) break;
}
void split(char input[],char *separators){
    char static *line_ref;
    line_ref =strdup(input);
    do {
        fprintf(stdout, "%s;", strsep(&line_ref, separators));
    } while (line_ref != '\0');
}



