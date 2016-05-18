#include "rendering.h"

void renderPlayedCard(SDL_Renderer *gRenderer, char *on_table[], SDL_Rect played_pos[], int whoIsPlaying, SDL_Rect gSpriteClipsClubs[], SDL_Rect gSpriteClipsDiamonds[], SDL_Rect gSpriteClipsHearts[], SDL_Rect gSpriteClipsSpades[])
{
    for(int i=0;i<4;i++)
    {
        if(on_table[i][0] == '0')
        {
            if(on_table[i][1] == 'A')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[10], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'B')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[11], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'C')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[12], &played_pos[whoIsPlaying]);
            else if(on_table[i][1]-48 <=9 && on_table[i][1]-48 >=0)
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[on_table[i][0] - 48], &played_pos[whoIsPlaying]);
            else
                continue;
        }
        else if(on_table[i][0] == '1')
        {
            if(on_table[i][1] == 'A')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsDiamonds[10], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'B')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsDiamonds[11], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'C')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsDiamonds[12], &played_pos[whoIsPlaying]);
            else if(on_table[i][1]-48 <=9 && on_table[i][1]-48 >=0)
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsDiamonds[on_table[i][0] - 48], &played_pos[whoIsPlaying]);
            else
                continue;
        }
        else if(on_table[i][0] == '2')
        {
            if(on_table[i][1] == 'A')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsHearts[10], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'B')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsHearts[11], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'C')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsHearts[12], &played_pos[whoIsPlaying]);
            else if(on_table[i][1]-48 <=9 && on_table[i][1]-48 >=0)
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsHearts[on_table[i][0] - 48], &played_pos[whoIsPlaying]);
            else
                continue;
        }
        else if(on_table[i][0] == '3')
        {
            if(on_table[i][1] == 'A')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[10], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'B')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[11], &played_pos[whoIsPlaying]);
            else if(on_table[i][1] == 'C')
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[12], &played_pos[whoIsPlaying]);
            else if(on_table[i][1]-48 <=9 && on_table[i][1]-48 >=0)
                SDL_RenderCopy(gRenderer, NULL, &gSpriteClipsSpades[on_table[i][0] - 48], &played_pos[whoIsPlaying]);
            else
                continue;
        }
        else
            continue;
    }
}
