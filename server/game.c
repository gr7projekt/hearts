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
void is_twenty_six(int hand_score[],int len){
    for(int i=0;i<len;i++) if (hand_score[i]==26){
            hand_score[i] = 0;
            hand_score[(i+1)%len] = 26;
            hand_score[(i+2)%len] = 26;
            hand_score[(i+3)%len] = 26;
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
// Parses data into given list using given separator
// Returns number of items parsed into list, 20 at the most.
int split(char *str,char separator,char *list[]) {
    // http://stackoverflow.com/questions/3217629/
    // in-c-how-do-i-find-the-index-of-a-character-within-a-string
    int index,i=0;
    char *e, *string;
    char sep[] = {separator,'\0'};
    string = str;
    if (str[((int) strlen(str))-1] != separator) strcat(string,sep);

    while((e = strchr(string, separator)) && i < 20) {
        index = (int) (e - string);
        string[index] = '\0';
        list[i++] = string;
        list[i] = "";
        string = &string[index + 1];
    }
    return i;
}
//Set 'char *list[4] values to "FF"
void FF_trick(char *list[]){
    for (int k = 0; k < 4; k++) {
        list[k] = malloc(3);
        memset(list[k], 'F', 2);
    }
}
//Set 'char *hand[13] values to "FF"
void FF_hand(char *hand[]){
    int i =0;
    while(i < 3) FF_trick(&hand[(i++)*4]);
    FF_trick(&hand[9]);
}
void new_deck(Card deck[])
{
    int i=0;
    int j=0;
    int k=0;

    for(i=0;i<4;i++)
    {
        for(j=0;j<13;j++)
        {
            deck[k].suit=i;     //0 Klöver 1 Ruter 2 Hjärter 3 Spader
            deck[k].value=j;
            k++;
        }
    }
}

void shuffle_deck(Card deck[], Card shuffled[])
{
    int i=0;
    int r;

    srand(time(NULL));

    //Fisher-Yates shuffle
    for(i=0;i<51;i++)   //bara 51 ggr, 52'a kortet tilldelas sist.
    {
        r=rand();
        r=r%(51-i);

        shuffled[i].suit=deck[r].suit;
        shuffled[i].value=deck[r].value;

        deck[r].suit=deck[51-i].suit;
        deck[r].value=deck[51-i].value;
    }
    shuffled[51].suit=deck[0].suit;
    shuffled[51].value=deck[0].value;
    //shuffle klar
}

void print_deck(Card deck[])
{
    for(int i=0;i<52;i++)
    {
        if(deck[i].suit == 0)
            printf("clubs %d\n",deck[i].value+2);
        else if(deck[i].suit == 1)
            printf("diamonds %d\n",deck[i].value+2);
        else if(deck[i].suit == 2)
            printf("hearts %d\n",deck[i].value+2);
        else
            printf("spades %d\n",deck[i].value+2);
    }
    printf("\n\n");
}
void convert_card_struct(Card shuffled_deck[],char *deck[],char *string){
    for(int i=0;i<52;i++){
        deck[i] = malloc(3);
        sprintf(deck[i],"%x%x",(shuffled_deck[i].suit),(shuffled_deck[i].value));
        if (!i){
            strcpy(string,deck[i]);
            strcat(string,";");
        }
        else {
            strcat(string,deck[i]);
            strcat(string,";");
        }
    }
}
void compile_card_string(Card shuffled_deck[],char *string){
    strcpy(string,"");
    char *tmp[52];
    for(int i=0;i<52;i++){
        tmp[i] = malloc(4);
        sprintf(tmp[i],"%x%x",(shuffled_deck[i].suit),(shuffled_deck[i].value));
        strcat(string,tmp[i]);
        strcat(string,";");
    }
}
void compile_send_string(char *array[],char string[],int length){
    for(int i=0;i<length;i++){
        if (!i) strcpy(string,array[i]);
        else {
            strcat(string,";");
            strcat(string,array[i]);
        }
    } strcat(string,";");
}
int find_DD(char *str[],int len){
    for (int i = 0; i < len; i++) if(!(strcmp(str[i],"DD"))) return i;
    return -1;
}




