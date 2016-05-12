//
// Created by Johan Lipecki on 2016-05-12.
//

#include "game.h"

int calculate_hand(char* card[]){
    int i=0, score = 0;
    for(;i<4;i++){
        if (is_hearts(card[i])) score += 1;
        else if (is_queen_of_diamonds(card)) score += 13;
    }
    return score;
}
