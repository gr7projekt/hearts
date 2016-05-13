#include "cardPosition.h"

void initSpritePosition(SDL_Rect p1[],SDL_Rect p2[], SDL_Rect p3[], SDL_Rect p4[], SDL_Rect adv[], SDL_Rect drop[], SDL_Rect played_pos[])
{
    for(int i=0 ; i<13; i++)
    {
        p1[i].y = RES_Y-HEIGHT;
        p1[i].x = (RES_X-(12*DISTANCE_X+70))/2+i*DISTANCE_X;       // (640-(12*35+70))/2=75, för att centrera
        p1[i].h = HEIGHT;
        p1[i].w = WIDTH;

        p2[i].y = (RES_Y-(12*DISTANCE_Y+105))/2+i*DISTANCE_Y;             //(480-(12*20+105))/2
        p2[i].x = 0;
        p2[i].h = HEIGHT;
        p2[i].w = WIDTH;

        p3[i].y = 0;
        p3[i].x = (RES_X-(12*DISTANCE_X+70))/2+i*DISTANCE_X;
        p3[i].h = HEIGHT;
        p3[i].w = WIDTH;

        p4[i].y = (RES_Y-(12*DISTANCE_Y+105))/2+i*DISTANCE_Y;
        p4[i].x = RES_X-70;
        p4[i].h = HEIGHT;
        p4[i].w = WIDTH;
    }

    played_pos[0].y = RES_Y/2;
    played_pos[0].x = RES_X/2 - WIDTH/2;
    played_pos[0].h = HEIGHT;
    played_pos[0].w = WIDTH;

    played_pos[1].y = RES_Y/2 - HEIGHT/2;
    played_pos[1].x = RES_X/2 - 3*WIDTH/2;
    played_pos[1].h = HEIGHT;
    played_pos[1].w = WIDTH;

    played_pos[2].y = RES_Y/2 - HEIGHT;
    played_pos[2].x = RES_X/2 - WIDTH/2;
    played_pos[2].h = HEIGHT;
    played_pos[2].w = WIDTH;

    played_pos[3].y = RES_Y/2 - HEIGHT/2;
    played_pos[3].x = RES_X/2 + WIDTH/2;
    played_pos[3].h = HEIGHT;
    played_pos[3].w = WIDTH;

    adv[0].y = RES_Y/2-200;
    adv[0].x = RES_X+10;  //+10 för att få avstånd från högra korten till reklamen
    adv[0].h = 400;
    adv[0].w = 65;        //75 pixlar höger om de högra korten, 65 för reklamen.

    drop[0].y = RES_Y/2-DROP_Y/2;
    drop[0].x = RES_X/2-DROP_X/2;
    drop[0].h = DROP_Y;
    drop[0].w = DROP_X;
}
