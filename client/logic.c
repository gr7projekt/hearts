//
// Created by Niclas Ragnar on 2016-05-18.
//

#include "logic.h"
#include "game.h"

bool is_first_trick(bool played[]) { // Check if it is first trick of round.
    for (int i = 0; i < 13; i++) {
        if (played[i] == true) return false;
    }
    return true;
}
bool start_trick(char* table[],int player_pos) { // Check player pos for EE.
    if(strcmp("EE",table[player_pos]) == 0) return true;
    return false;
}
bool do_i_start(bool played[], char **table, int player_pos) { // Check if player starts.
    if(is_first_trick(played)) if (start_trick(table,player_pos)) return true;
    return false;
}
bool play_first_trick(bool played[], char* table[], int player_pos, char played_card[], char* hand[], char lead_suit) {
    if (do_i_start(played, table, player_pos)) { // Robert? Uneccessary?
        printf("First player.\n"); // Debug.
        // First player. Only play "00".
        if (is_two_of_clubs(played_card)) return true; // Play 00
    }   // NOT first player. Play suit if possible.
        // Only play hearts if entire hand is hearts "2x".
    else {
        printf("NOT first player.\n");
        if(only_score_cards(hand) && is_hearts(played_card[0])) { // If only scoring cards on hand & played card is hearts.
            printf("Entire hand is hearts\n"); // Debug.
            return true; // Allowed to play hearts if above conditions are met.
        }
        else {
            if (correct_suit(played_card, lead_suit)) { // If correct suit is played.
                printf("Right suit.\n"); // Debug
                return true;
            }
            else { // If NOT correct suit is played.    // Maybe remove this?
                printf("WRONG suit.\n"); // Debug.      // And this?
                return false; // Unneccessary?          // This too?
            }
        }
    }
    return false;
}
bool suit_on_hand(char* table[], char* hand[], int first_card) { // Check if the player has lead suit on hand.
    for(int i = 0; i < 13; i++) if (hand[i][0] == table[first_card][0]) return true;
    return false;
}
bool only_score_cards(char* hand[]) { // Check if player only have scoring cards on hand.
    int score = 0;
    for (int i = 0; i < 13; i++) if (hand[i][0] == '2') score +=1; // Any hearts.
    for (int i = 0; i < 13; i++) if (strcmp(hand[i],"3A") == 0) score +=1; // Queen of spades.
    if (score >= 13) return true; // Player has total score of 13 on hand.
    return false; // Player does NOT.
}
bool entire_hand_is_hearts(char* hand[]) { // Check if player hand is only hearts.
    for (int i = 0; i < 13; i++) if (hand[i][0] != '2') return false; // If suit is anything but hearts.
    return true; // ALL suits is hearts.
}

int find_lead_card_pos(char* table[]) { // Only run ONCE when recieving "empty" string. FF/EE
    for (int i = 0; i < 4; i++) {
        if (table[i][0] != 'F' && table[i+1][0] == 'F') return i;
        if (i == 3 && table[i][0] != 'F' && table[0][0] == 'F') return i;
    }
    printf("Failed to find lead card position.\n");
    return -1; //Failed to find lea card player position.
}
bool correct_suit(char played_card[], char lead_suit) { // If played card is following suit.
    if (played_card[0] == lead_suit) return true;
    return false;
}
char find_lead_suit(char* table[], int first_card) { // Find lead suit.
    char lead_suit;
    lead_suit = table[first_card][0]; // Suit value of first card played.
    return lead_suit;
}
bool play_trick(bool played[], char* table[], int player_pos, char played_card[], char* hand[], char lead_suit, bool broken_heart,int lead_card_pos) {
    if (start_trick(table, player_pos)) { // First player.
        if (broken_heart) return true; // Allowed to lead ANY suit (including hearts).
        if (!is_hearts(played_card[0])) { // Heart not broken. Trying to play hearts.
                printf("Heart NOT broken. Trying to play hearts, NOT allowed.\n"); // Debug.
                return false; // Not allowed.
            }
            else { // Heart NOT broken. Not playing hearts.
                printf("Heart NOT broken. NOT playing hearts.\n"); // Debug.
                return true; // Leading with correct suit (NOT HEARTS).
            }
        }
    else { // NOT first player.
        printf("NOT first player.\n"); // Debug
        if (suit_on_hand(table,hand,lead_card_pos)) { // Have CORRECT suit on hand.
            if(correct_suit(played_card,lead_suit)) { // Played suit is RIGHT.
                printf("Right suit.\n"); // Debug.
                return true;
            }
            else { // Have CORRECT suit on hand, trying to play WRONG.
                printf("Wrong suit. Have right on hand, try again!\n"); // Unneccessary? For "debug".
            }
        }
        else {
            if(broken_heart) { // Hearts is broken, discard any card.
                printf("Play any card.\n"); // Debug.
                return true;
            }
            else {
                if(discard_card(played_card)) { // Discard any card but hearts.
                    printf("Play any card BUT hearts.\n"); // Debug.
                    return true;
                }
                else { // Trying to discard hearts when hearts NOT broken.
                    printf("Heart not broken, try something else.\n");
                    return false; // Unnesseary? For "debug".
                }
            }
        }

    }
    return false;
}
bool discard_card(char played_card[]) { // Checks if discarded card is hearts.
    if(is_hearts(played_card[0]))return false; // Can't discard if hearts not broken.
    return true;
}