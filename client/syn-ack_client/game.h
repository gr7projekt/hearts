//
// Created by Johan Lipecki on 2016-05-12.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL_quit.h>
#include "players.h"

struct card_struct{
    int suit;
    int value;
};
typedef struct card_struct Card;
void new_deck(Card []);
void convert_card_struct(Card shuffled_deck[],char *deck[]);
//Takes an array of four cards and returns the score
int calculate_trick(char* []);
//does the char passed represent hearts?
bool is_hearts(char);
//does the passed string represent the queen of spades?
bool is_queen_of_spades(char[]);
// given the complete trick and the starting player position
// check winner returns the position of the player who should
// be assigned the score
int check_winner(char* [],int);
//does the passed string represent the two of clubs?
bool is_two_of_clubs(char []);
// does the passed hand contain the two of clubs
bool do_I_start(char* []);
// given a list of four hands, who_starts returns the player position
// of the hand with the two of clubs
int who_starts(char **[4]);
// given the trick winner(arg 1) and the trick score (arg 2)
// the array of scores for the hand (arg 0)
// is updated with the trick score. (pos 0 = player 0 score).
void update_hand_score(int [],int,int);
// Increments list0 with list1, from "index"(arg 2) to "len"(arg 3) -1,
// and puts result in list0. To add a single value to a list of items,
// match "index" with list[index] and set "len" to "index"+1.
void add_list1_to_list0(int [],int [],int,int);
// The same as add_list1_to_list0 with index=0 and len=no_of_players.
// Therefore it is not as flexible, but it is easier to use.
// To add a single value, provide a list with one non-zero value (e.g. {0,0,1337,0})
void update_round_score(int [], int[], int);
//Prints a list of (arg 3) number of items to the stream pointed to by "FILE *fp"
//the items in the array are split by the character given
void print_list(FILE *,char *,int[],int);
// given list with (arg 1) number of items,
// the list is checked for 26 and returns the hand score
// use this at the end of a hand to determine how to assign the hand score
void is_twenty_six(int []);
//is any of the items in the list greater than 100?
bool is_hundred (int []);

void separate_strings(char *, const char *, char *[],int);
int split(char *,char,char *[]);
void FF_trick(char *[]);
void EE_trick(char *[],int);
void DD_trick(char *[],int);
void FF_hand(char *[]);
void print_deck(Card []);
void shuffle_deck(Card [],Card []);
void Compare(Uint8* , Uint8* , int ,char* [13]);
#endif


