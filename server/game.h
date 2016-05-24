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

struct card_struct{
    int suit;
    int value;
};
typedef struct card_struct Card;
//Takes an array of four cards and returns the score
int calculate_trick(char* []);
bool is_hearts(char);
bool is_queen_of_spades(char[]);
int check_winner(char* [],int);
bool is_two_of_clubs(char []);
bool do_I_start(char* []);
int who_starts(char **[4]);
void update_hand_score(int [],int,int);
void add_list1_to_list0(int [],int [],int,int);
void print_list(FILE *,char *,int[],int);
void is_twenty_six(int[]);
bool is_hundred (int []);
void update_round_score(int [], int[], int);
void separate_strings(char *, const char *, char *[],int);
int split(char *,char,char *[]);
void FF_trick(char *[]);
void FF_hand(char *[]);
void print_deck(Card []);
void shuffle_deck(Card[],Card[]);
void new_deck(Card []);
#endif


