#include "loadMedia.h"

void loadMediaDropzone(SDL_Texture *dropzone[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsDropzone[])
{
    SDL_Surface* gDropSurface = IMG_Load("dropzone.png");

    dropzone[0] = SDL_CreateTextureFromSurface(gRenderer, gDropSurface);

    gSpriteClipsDropzone[ 0 ].x = 0;
    gSpriteClipsDropzone[ 0 ].y = 0;
    gSpriteClipsDropzone[ 0 ].w = DROP_X;
    gSpriteClipsDropzone[ 0 ].h = DROP_Y;
}

void loadMediaAdvertisment(SDL_Texture *advertisment[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsAdvertisment[])
{
    SDL_Surface* gAdvSurface = IMG_Load("advertisment.png");

    advertisment[0] = SDL_CreateTextureFromSurface(gRenderer, gAdvSurface);

    gSpriteClipsAdvertisment[ 0 ].x = 0;
    gSpriteClipsAdvertisment[ 0 ].y = 0;
    gSpriteClipsAdvertisment[ 0 ].w = 140;
    gSpriteClipsAdvertisment[ 0 ].h = 400;
}

void loadMediaClubs(int i, SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsClubs[])
{
    SDL_Surface* gCardSurface = IMG_Load("CARD.png");

    card[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);

    gSpriteClipsClubs[ 0 ].x = WIDTH*0;
    gSpriteClipsClubs[ 0 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 0 ].w = WIDTH;
    gSpriteClipsClubs[ 0 ].h = HEIGHT;

    gSpriteClipsClubs[ 1 ].x = WIDTH*1;
    gSpriteClipsClubs[ 1 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 1 ].w = WIDTH;
    gSpriteClipsClubs[ 1 ].h = HEIGHT;

    gSpriteClipsClubs[ 2 ].x = WIDTH*2;
    gSpriteClipsClubs[ 2 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 2 ].w = WIDTH;
    gSpriteClipsClubs[ 2 ].h = HEIGHT;

    gSpriteClipsClubs[ 3 ].x = WIDTH*3;
    gSpriteClipsClubs[ 3 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 3 ].w = WIDTH;
    gSpriteClipsClubs[ 3 ].h = HEIGHT;

    gSpriteClipsClubs[ 4 ].x = WIDTH*4;
    gSpriteClipsClubs[ 4 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 4 ].w = WIDTH;
    gSpriteClipsClubs[ 4 ].h = HEIGHT;

    gSpriteClipsClubs[ 5 ].x = WIDTH*5;
    gSpriteClipsClubs[ 5 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 5 ].w = WIDTH;
    gSpriteClipsClubs[ 5 ].h = HEIGHT;

    gSpriteClipsClubs[ 6 ].x = WIDTH*6;
    gSpriteClipsClubs[ 6 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 6 ].w = WIDTH;
    gSpriteClipsClubs[ 6 ].h = HEIGHT;

    gSpriteClipsClubs[ 7 ].x = WIDTH*7;
    gSpriteClipsClubs[ 7 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 7 ].w = WIDTH;
    gSpriteClipsClubs[ 7 ].h = HEIGHT;

    gSpriteClipsClubs[ 8 ].x = WIDTH*8;
    gSpriteClipsClubs[ 8 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 8 ].w = WIDTH;
    gSpriteClipsClubs[ 8 ].h = HEIGHT;

    gSpriteClipsClubs[ 9 ].x = WIDTH*9;
    gSpriteClipsClubs[ 9 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 9 ].w = WIDTH;
    gSpriteClipsClubs[ 9 ].h = HEIGHT;

    gSpriteClipsClubs[ 10 ].x = WIDTH*10;
    gSpriteClipsClubs[ 10 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 10 ].w = WIDTH;
    gSpriteClipsClubs[ 10 ].h = HEIGHT;

    gSpriteClipsClubs[ 11 ].x = WIDTH*11;
    gSpriteClipsClubs[ 11 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 11 ].w = WIDTH;
    gSpriteClipsClubs[ 11 ].h = HEIGHT;

    gSpriteClipsClubs[ 12 ].x = WIDTH*12;
    gSpriteClipsClubs[ 12 ].y = HEIGHT*0;
    gSpriteClipsClubs[ 12 ].w = WIDTH;
    gSpriteClipsClubs[ 12 ].h = HEIGHT;
}

void loadMediaDiamonds(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsDiamonds[])
{
    SDL_Surface* gCardSurface = IMG_Load("CARD.png");

    card[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);

    gSpriteClipsDiamonds[ 0 ].x = WIDTH*0;
    gSpriteClipsDiamonds[ 0 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 0 ].w = WIDTH;
    gSpriteClipsDiamonds[ 0 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 1 ].x = WIDTH*1;
    gSpriteClipsDiamonds[ 1 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 1 ].w = WIDTH;
    gSpriteClipsDiamonds[ 1 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 2 ].x = WIDTH*2;
    gSpriteClipsDiamonds[ 2 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 2 ].w = WIDTH;
    gSpriteClipsDiamonds[ 2 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 3 ].x = WIDTH*3;
    gSpriteClipsDiamonds[ 3 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 3 ].w = WIDTH;
    gSpriteClipsDiamonds[ 3 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 4 ].x = WIDTH*4;
    gSpriteClipsDiamonds[ 4 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 4 ].w = WIDTH;
    gSpriteClipsDiamonds[ 4 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 5 ].x = WIDTH*5;
    gSpriteClipsDiamonds[ 5 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 5 ].w = WIDTH;
    gSpriteClipsDiamonds[ 5 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 6 ].x = WIDTH*6;
    gSpriteClipsDiamonds[ 6 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 6 ].w = WIDTH;
    gSpriteClipsDiamonds[ 6 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 7 ].x = WIDTH*7;
    gSpriteClipsDiamonds[ 7 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 7 ].w = WIDTH;
    gSpriteClipsDiamonds[ 7 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 8 ].x = WIDTH*8;
    gSpriteClipsDiamonds[ 8 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 8 ].w = WIDTH;
    gSpriteClipsDiamonds[ 8 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 9 ].x = WIDTH*9;
    gSpriteClipsDiamonds[ 9 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 9 ].w = WIDTH;
    gSpriteClipsDiamonds[ 9 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 10 ].x = WIDTH*10;
    gSpriteClipsDiamonds[ 10 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 10 ].w = WIDTH;
    gSpriteClipsDiamonds[ 10 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 11 ].x = WIDTH*11;
    gSpriteClipsDiamonds[ 11 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 11 ].w = WIDTH;
    gSpriteClipsDiamonds[ 11 ].h = HEIGHT;

    gSpriteClipsDiamonds[ 12 ].x = WIDTH*12;
    gSpriteClipsDiamonds[ 12 ].y = HEIGHT;
    gSpriteClipsDiamonds[ 12 ].w = WIDTH;
    gSpriteClipsDiamonds[ 12 ].h = HEIGHT;
}

void loadMediaHearts(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsHearts[])
{
    SDL_Surface* gCardSurface = IMG_Load("CARD.png");

    card[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);

    gSpriteClipsHearts[ 0 ].x = WIDTH*0;
    gSpriteClipsHearts[ 0 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 0 ].w = WIDTH;
    gSpriteClipsHearts[ 0 ].h = HEIGHT;

    gSpriteClipsHearts[ 1 ].x = WIDTH*1;
    gSpriteClipsHearts[ 1 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 1 ].w = WIDTH;
    gSpriteClipsHearts[ 1 ].h = HEIGHT;

    gSpriteClipsHearts[ 2 ].x = WIDTH*2;
    gSpriteClipsHearts[ 2 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 2 ].w = WIDTH;
    gSpriteClipsHearts[ 2 ].h = HEIGHT;

    gSpriteClipsHearts[ 3 ].x = WIDTH*3;
    gSpriteClipsHearts[ 3 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 3 ].w = WIDTH;
    gSpriteClipsHearts[ 3 ].h = HEIGHT;

    gSpriteClipsHearts[ 4 ].x = WIDTH*4;
    gSpriteClipsHearts[ 4 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 4 ].w = WIDTH;
    gSpriteClipsHearts[ 4 ].h = HEIGHT;

    gSpriteClipsHearts[ 5 ].x = WIDTH*5;
    gSpriteClipsHearts[ 5 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 5 ].w = WIDTH;
    gSpriteClipsHearts[ 5 ].h = HEIGHT;

    gSpriteClipsHearts[ 6 ].x = WIDTH*6;
    gSpriteClipsHearts[ 6 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 6 ].w = WIDTH;
    gSpriteClipsHearts[ 6 ].h = HEIGHT;

    gSpriteClipsHearts[ 7 ].x = WIDTH*7;
    gSpriteClipsHearts[ 7 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 7 ].w = WIDTH;
    gSpriteClipsHearts[ 7 ].h = HEIGHT;

    gSpriteClipsHearts[ 8 ].x = WIDTH*8;
    gSpriteClipsHearts[ 8 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 8 ].w = WIDTH;
    gSpriteClipsHearts[ 8 ].h = HEIGHT;

    gSpriteClipsHearts[ 9 ].x = WIDTH*9;
    gSpriteClipsHearts[ 9 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 9 ].w = WIDTH;
    gSpriteClipsHearts[ 9 ].h = HEIGHT;

    gSpriteClipsHearts[ 10 ].x = WIDTH*10;
    gSpriteClipsHearts[ 10 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 10 ].w = WIDTH;
    gSpriteClipsHearts[ 10 ].h = HEIGHT;

    gSpriteClipsHearts[ 11 ].x = WIDTH*11;
    gSpriteClipsHearts[ 11 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 11 ].w = WIDTH;
    gSpriteClipsHearts[ 11 ].h = HEIGHT;

    gSpriteClipsHearts[ 12 ].x = WIDTH*12;
    gSpriteClipsHearts[ 12 ].y = HEIGHT*2;
    gSpriteClipsHearts[ 12 ].w = WIDTH;
    gSpriteClipsHearts[ 12 ].h = HEIGHT;
}

void loadMediaSpades(int i,SDL_Texture *card[], SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsSpades[])
{
    SDL_Surface* gCardSurface = IMG_Load("CARD.png");

    card[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);

    gSpriteClipsSpades[ 0 ].x = WIDTH*0;
    gSpriteClipsSpades[ 0 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 0 ].w = WIDTH;
    gSpriteClipsSpades[ 0 ].h = HEIGHT;

    gSpriteClipsSpades[ 1 ].x = WIDTH*1;
    gSpriteClipsSpades[ 1 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 1 ].w = WIDTH;
    gSpriteClipsSpades[ 1 ].h = HEIGHT;

    gSpriteClipsSpades[ 2 ].x = WIDTH*2;
    gSpriteClipsSpades[ 2 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 2 ].w = WIDTH;
    gSpriteClipsSpades[ 2 ].h = HEIGHT;

    gSpriteClipsSpades[ 3 ].x = WIDTH*3;
    gSpriteClipsSpades[ 3 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 3 ].w = WIDTH;
    gSpriteClipsSpades[ 3 ].h = HEIGHT;

    gSpriteClipsSpades[ 4 ].x = WIDTH*4;
    gSpriteClipsSpades[ 4 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 4 ].w = WIDTH;
    gSpriteClipsSpades[ 4 ].h = HEIGHT;

    gSpriteClipsSpades[ 5 ].x = WIDTH*5;
    gSpriteClipsSpades[ 5 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 5 ].w = WIDTH;
    gSpriteClipsSpades[ 5 ].h = HEIGHT;

    gSpriteClipsSpades[ 6 ].x = WIDTH*6;
    gSpriteClipsSpades[ 6 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 6 ].w = WIDTH;
    gSpriteClipsSpades[ 6 ].h = HEIGHT;

    gSpriteClipsSpades[ 7 ].x = WIDTH*7;
    gSpriteClipsSpades[ 7 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 7 ].w = WIDTH;
    gSpriteClipsSpades[ 7 ].h = HEIGHT;

    gSpriteClipsSpades[ 8 ].x = WIDTH*8;
    gSpriteClipsSpades[ 8 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 8 ].w = WIDTH;
    gSpriteClipsSpades[ 8 ].h = HEIGHT;

    gSpriteClipsSpades[ 9 ].x = WIDTH*9;
    gSpriteClipsSpades[ 9 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 9 ].w = WIDTH;
    gSpriteClipsSpades[ 9 ].h = HEIGHT;

    gSpriteClipsSpades[ 10 ].x = WIDTH*10;
    gSpriteClipsSpades[ 10 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 10 ].w = WIDTH;
    gSpriteClipsSpades[ 10 ].h = HEIGHT;

    gSpriteClipsSpades[ 11 ].x = WIDTH*11;
    gSpriteClipsSpades[ 11 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 11 ].w = WIDTH;
    gSpriteClipsSpades[ 11 ].h = HEIGHT;

    gSpriteClipsSpades[ 12 ].x = WIDTH*12;
    gSpriteClipsSpades[ 12 ].y = HEIGHT*3;
    gSpriteClipsSpades[ 12 ].w = WIDTH;
    gSpriteClipsSpades[ 12 ].h = HEIGHT;

}


void loadMediaBack(int i, SDL_Texture *card_2[], SDL_Texture *card_3[], SDL_Texture *card_4[],SDL_Renderer *gRenderer, SDL_Rect gSpriteClipsBack[])
{
    SDL_Surface* gCardSurface = IMG_Load("CARD.png");

    card_2[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);
    card_3[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);
    card_4[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);

//    baksida kort har värde 0.
    gSpriteClipsBack[ 0 ].x = WIDTH*1;
    gSpriteClipsBack[ 0 ].y = HEIGHT*4;
    gSpriteClipsBack[ 0 ].w = WIDTH;
    gSpriteClipsBack[ 0 ].h = HEIGHT;
}
