#include "rendering.h"

void renderPlayedCard(SDL_Renderer *gRenderer, char *trick[], SDL_Rect played_pos[], int whoIsPlaying,
                      SDL_Rect gSpriteClipsClubs[], SDL_Rect gSpriteClipsDiamonds[], SDL_Rect gSpriteClipsHearts[], SDL_Rect gSpriteClipsSpades[],
                      SDL_Texture* card1[],SDL_Texture* card2[], SDL_Texture* card3[], SDL_Texture* card4[],
                      Player p1[], Player p2[], Player p3[], Player p4[])
{
    int tmp_pos;
    for(int i=0;i<4;i++)
    {
        if(i == p1[0].id)
            tmp_pos = p1[0].relativ_pos;
        if(i == p2[0].id)
            tmp_pos = p2[0].relativ_pos;
        if(i == p3[0].id)
            tmp_pos = p3[0].relativ_pos;
        if(i == p4[0].id)
            tmp_pos = p4[0].relativ_pos;

   // printf("trick: %s, player %i\n",trick[i],i);
        if(trick[i][0] == '0')
        {
            if(trick[i][1] == 'A')
                SDL_RenderCopy(gRenderer, card1[10], &gSpriteClipsClubs[10], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'B')
                SDL_RenderCopy(gRenderer, card1[11], &gSpriteClipsClubs[11], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'C')
                SDL_RenderCopy(gRenderer, card1[12], &gSpriteClipsClubs[12], &played_pos[tmp_pos]);
            else if(trick[i][1] - 48 <=9 && trick[i][1] - 48 >=0)
                SDL_RenderCopy(gRenderer, card1[trick[i][1] - 48], &gSpriteClipsClubs[trick[i][1] - 48], &played_pos[tmp_pos]);
            else
                continue;
        }
        else if(trick[i][0] == '1')
        {
            if(trick[i][1] == 'A')
                SDL_RenderCopy(gRenderer, card2[10], &gSpriteClipsDiamonds[10], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'B')
                SDL_RenderCopy(gRenderer, card2[11], &gSpriteClipsDiamonds[11], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'C')
                SDL_RenderCopy(gRenderer, card2[12], &gSpriteClipsDiamonds[12], &played_pos[tmp_pos]);
            else if(trick[i][1]-48 <=9 && trick[i][1]-48 >=0)
                SDL_RenderCopy(gRenderer, card2[trick[i][1]-48], &gSpriteClipsDiamonds[trick[i][1] - 48], &played_pos[tmp_pos]);
            else
                continue;
        }
        else if(trick[i][0] == '2')
        {
            if(trick[i][1] == 'A')
                SDL_RenderCopy(gRenderer, card3[10], &gSpriteClipsHearts[10], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'B')
                SDL_RenderCopy(gRenderer, card3[11], &gSpriteClipsHearts[11], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'C')
                SDL_RenderCopy(gRenderer, card3[12], &gSpriteClipsHearts[12], &played_pos[tmp_pos]);
            else if(trick[i][1]-48 <=9 && trick[i][1]-48 >=0)
                SDL_RenderCopy(gRenderer, card3[ trick[i][1]-48], &gSpriteClipsHearts[trick[i][1] - 48], &played_pos[tmp_pos]);
            else
                continue;
        }
        else if(trick[i][0] == '3')
        {
            if(trick[i][1] == 'A')
                SDL_RenderCopy(gRenderer, card4[10], &gSpriteClipsSpades[10], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'B')
                SDL_RenderCopy(gRenderer, card4[11], &gSpriteClipsSpades[11], &played_pos[tmp_pos]);
            else if(trick[i][1] == 'C')
                SDL_RenderCopy(gRenderer, card4[12], &gSpriteClipsSpades[12], &played_pos[tmp_pos]);
            else if( trick[i][1]-48 <=9 && trick[i][1]-48 >=0)
                SDL_RenderCopy(gRenderer, card4[trick[i][1]-48], &gSpriteClipsSpades[trick[i][1] - 48], &played_pos[tmp_pos]);
            else
                continue;
        }
        else
            continue;
    }
}
