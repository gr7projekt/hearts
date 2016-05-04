#include "moveCard.h"
#include <stdio.h>

int liftCard(SDL_Rect initial_pos[0],SDL_Rect p1[], int mouse_x, int mouse_y)
{
    int k=-1;
    for(int i=0;i<13;i++)
    {
        if((mouse_x > p1[i].x && mouse_x < p1[i].x + DISTANCE_X)&&(mouse_y > p1[i].y && mouse_y < p1[i].y + p1[i].h))
        {
            initial_pos[0].x = p1[i].x;

            p1[i].x = mouse_x-35;
            p1[i].y = mouse_y-105/2;
            k=i;
        }
    }
    printf("initial x pos: %d\n",initial_pos[0].x);
    return k;
}

void moveCard(SDL_Rect p1[], int k, int mouse_x, int mouse_y)
{
    if((mouse_x > p1[k].x && mouse_x < p1[k].x + p1[k].w)&&(mouse_y > p1[k].y && mouse_y < p1[k].y + p1[k].h))
    {
        p1[k].x=mouse_x-35;
        p1[k].y=mouse_y-105/2;
    }
}
