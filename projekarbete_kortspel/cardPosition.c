#include "cardPosition.h"
#define DISTANCE_X 25
#define DISTANCE_Y 15

void initCardPosition(SDL_Rect p1[],SDL_Rect p2[], SDL_Rect p3[], SDL_Rect p4[], SDL_Rect adv[])
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
    adv[0].y=RES_Y/2-200;
    adv[0].x=RES_X+10;  //+10 för att få avstånd från högra korten till reklamen
    adv[0].h=400;
    adv[0].w=65;        //75 pixlar höger om de högra korten, 65 för reklamen.
}
