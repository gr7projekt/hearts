//
// Created by Johan Lipecki on 2016-05-12.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include "includes.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
void split(char [],char *);
#endif


