//
// Created by Niclas Ragnar on 2016-05-18.
//

#ifndef LOGIC_LOGIC_H
#define LOGIC_LOGIC_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_first_trick(bool played[]); // Check if it is first trick of round.
bool start_trick(char* table[], int player_pos); // Check player pos for EE on "empty"(EE,FF,FF,FF) table string.
bool do_i_start(bool played[], char **table, int player_pos); // Check if player starts.
bool play_first_trick(bool played[], char* table[], int player_pos, char player_card[], char* hand[], char lead_suit); // Play FIRST stick.
bool suit_on_hand(char* table[], char* hand[], int first_card); // Check if the player has lead suit on hand.
bool entire_hand_is_hearts(char* hand[]); // Check if player hand is only hearts.
bool only_score_cards(char* hand[]); // Check if player only have scoring cards on hand.
int find_lead_card_pos(char* []); // Find lead card position. Only run ONCE when recieving "empty" string. Return -1 on failure.
char find_lead_suit(char* table[], int first_card); // Find and return lead suit.
bool correct_suit(char played_card[], char lead_suit); // Check if played card is following suit.
bool play_trick(bool played[], char* table[],int player_pos, char played_card[], char* hand[], char lead_suit, bool broken_heart, int lead_card_pos); // Play stick.
bool discard_card(char played_card[]); // Check if discarded card is hearts.

#endif //LOGIC_LOGIC_H
