//
// Created by Johan Lipecki on 2016-05-12.
//



#include "game.h"
void separate_strings(char *, const char *, char *[],int);
int calculate_trick(char* card[]){
    int score = 0;
    for(int i=0;i<4;i++){
        if (is_hearts(*card[i])) score += 1;
        else if (is_queen_of_spades(card[i])) score += 13;
    }
    return score;
}
void update_round_score(int *round_score[],char *card[]){
    for(int i=0;i<4;i++) *round_score[i] += *card[i];
}

int check_winner(char *card[],int player_pos_of_starting_hand) {
    char hand_suit = card[player_pos_of_starting_hand][0];
    char high_card[3] = {'\0'};
    char tmp_card[3] = {'\0'};
    int winner_pos=player_pos_of_starting_hand;
    for (int i = 0;i < 4;i++) {
        strcpy(tmp_card,card[i]);
        if (card[i][0] == hand_suit) if (card[i][1] > high_card[1]) {
            strcpy(high_card,tmp_card);
            winner_pos = i;
        }
    }
    return winner_pos;
}
bool is_hearts(char suit) {
    if (suit == '2') return true;
    else return false;
}
bool is_queen_of_spades(char card[]){
    if(!strcmp(card,"3A")) return true;
    else return false;
}
bool is_two_of_clubs(char card[]){
    if(!strcmp(card,"00")) return true; // 2 of Clubs
    else return false;
}
void search_hand(char* hand[], int *next_player, int my_pos){
    for(int i = 0;i < 13;i++){
        if (is_two_of_clubs(hand[i])){
		*next_player = my_pos;
    		return;
	}
    }
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
    string = (char*) strdup(inputstring);

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
