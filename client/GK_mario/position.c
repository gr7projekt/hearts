#include "position.h"

void position(Player p1[], Player p2[], Player p3[], Player p4[])
{
    p1[0].relativ_pos = 0;
    p2[0].relativ_pos = 1;
    p3[0].relativ_pos = 2;
    p4[0].relativ_pos = 3;

    p1[0].id = 0;   // HÄR SKA DEN EXAKTA positionen för klienten in.
//    p1[0].id = 1;
//    p1[0].id = 2;
//    p1[0].id = 3;
    p2[0].id = p1[0].id + 1;
    p3[0].id = p1[0].id + 2;
    p4[0].id = p1[0].id + 3;

    if(p2[0].id > 3){
        p2[0].id = p2[0].id-4;
    }
    if(p3[0].id > 3){
        p3[0].id = p3[0].id-4;
    }
    if(p4[0].id > 3){
        p4[0].id = p4[0].id-4;
    }
}
