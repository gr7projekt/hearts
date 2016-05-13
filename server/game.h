//
// Created by Johan Lipecki on 2016-05-12.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

//Takes an array of four cards and returns the score
int calculate_trick(char* []);
bool is_hearts(char);
bool is_queen_of_spades(char[]);
int check_winner(char* [],int);
bool is_two_of_clubs(char []);
void search_hand(char* [], int*, int);
bool is_hunded (int []);
void update_round_score(int *[],char *[]);

#endif SERVER_GAME_H


