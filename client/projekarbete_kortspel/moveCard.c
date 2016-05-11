#include "moveCard.h"
#include <stdio.h>

int liftCard(SDL_Rect initial_pos[0],SDL_Rect p1[], int mouse_x, int mouse_y,bool picked[])
{
    int k=-1;
    for(int i=0;i<13;i++)
    {
        if(i==12)   //om sista kortet lyfts kan hela kortet lyftas
        {
            if((mouse_x > p1[i].x && mouse_x < p1[i].x + p1[i].w)&&(mouse_y > p1[i].y && mouse_y < p1[i].y + p1[i].h))
            {
                initial_pos[0].x = p1[i].x;

                p1[i].x = mouse_x-35;
                p1[i].y = mouse_y-105/2;
                k=i;
                picked[i]=true;
            }
        }
        else if(picked[i+1])    //om kortet ovan kortet vi vill ta lyfts, så kan vi trycka på hela ytan
        {
            if((mouse_x > p1[i].x && mouse_x < p1[i].x + p1[i].w)&&(mouse_y > p1[i].y && mouse_y < p1[i].y + p1[i].h))
            {
                initial_pos[0].x = p1[i].x;

                p1[i].x = mouse_x-35;
                p1[i].y = mouse_y-105/2;
                k=i;
                picked[i]=true;
            }
        }
        else    //annars trycker vi bara på halva ytan av kortet
        {
            if((mouse_x > p1[i].x && mouse_x < p1[i].x + DISTANCE_X)&&(mouse_y > p1[i].y && mouse_y < p1[i].y + p1[i].h))
            {
                initial_pos[0].x = p1[i].x;

                p1[i].x = mouse_x-35;
                p1[i].y = mouse_y-105/2;
                k=i;
                picked[i]=true;
            }
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
