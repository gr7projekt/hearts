//
//
//  SDLtesta
//
//  Created by Jonas Wåhslen on 2015-03-31.
//  Copyright (c) 2015 wahslen. All rights reserved.
//
//  Modified by Robert Kärrbrant on 2016-04-20
//

#include <stdio.h>
#include <SDL.h>    //<SDL2/SDL.h>
#include <SDL_image.h>  //<SDL2_image/SDL_image.h>
#include <stdbool.h>

#define HEIGHT 105
#define WIDTH 70

struct card_struct{
    int suit;
    int value;
};

bool init();
void loadMediaClubs(int i);
void loadMediaDiamonds(int i);
void loadMediaHearts(int i);
void loadMediaSpades(int i);
void loadMediaBack(int i);


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* card[13] = {NULL};     //spelarens kort (det grafiska, inte riktiga handen)
//SDL_Texture* card2 = NULL;

SDL_Rect gSpriteClipsClubs[13];
SDL_Rect gSpriteClipsDiamonds[13];
SDL_Rect gSpriteClipsHearts[13];
SDL_Rect gSpriteClipsSpades[13];
SDL_Rect gSpriteClipsBack[1];

int main(int argc, char* args[])
{
    struct card_struct player_card[13];     //spelarens riktiga kort

    SDL_Event e;
    SDL_RendererFlip flip = SDL_FLIP_NONE; //SDL_FLIP_VERTICAL;
    bool quit = false;

    SDL_Rect possition[13]; //positionen för korten
    // int player_card[13];    //Här är spelarens kort

    for(int i=0 ; i<13; i++)
    {
        possition[i].y = 480-HEIGHT;  //100
        possition[i].x = 75+i*35;       // (640-(12*35+70))/2=75, för att centrera
        possition[i].h = HEIGHT;   //16
        possition[i].w = WIDTH;
    }

    if (init()) {
        printf("worked\n");
    }

    int k=0;

    for(int i=0; i<13; i++) // HÄR SKA DET LADDAS IN INFORMATION FRÅN SERVERN OM VILKA KORT SOM DELAS UT
    {
        player_card[i].value = i;   //om det är en 2'a 7'a eller dam
        player_card[i].suit = k;    //vilken färg kortet har, 0=klöver 1=ruter 2=hjärter 3=spader
        k++;
        if(k>3)
            k=0;
    }

    for(int i=0; i<13; i++)
    {

        if(player_card[i].suit == 0)
        {
            loadMediaClubs(player_card[i].value);
        }
        else if(player_card[i].suit == 1)
        {
            loadMediaDiamonds(player_card[i].value);
        }
        else if(player_card[i].suit == 2)
        {
            loadMediaHearts(player_card[i].value);
        }
        else if(player_card[i].suit == 3)
        {
            loadMediaSpades(player_card[i].value);
        }
        else
        {
            printf("unvalid card.");
        }

    }

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
 /*           else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        possition[0].y -= 3;
                        flip = SDL_FLIP_NONE;
                        if(player_card[0] == 4)
                            player_card[0] = 5;
                        else
                            player_card[0] = 4;
                        break;

                    case SDLK_DOWN:
                        possition[0].y += 3;
                        flip = SDL_FLIP_NONE;
                        if(player_card[0] == 0)
                            player_card[0] = 1;
                        else
                            player_card[0] = 0;
                        break;

                    case SDLK_LEFT:
                        possition[0].x -= 3;
                        flip = SDL_FLIP_NONE;    //SDL_FLIP_HORIZONTAL;
                        if(player_card[0] == 6)
                            player_card[0] = 7;
                        else
                            player_card[0] = 6;
                        break;

                    case SDLK_RIGHT:
                        possition[0].x += 3;
                        flip = SDL_FLIP_NONE;
                        if(player_card[0] == 2)
                            player_card[0] = 3;
                        else
                            player_card[0] = 2;
                        break;
                    default:

                        break;
                }
            }
*/
        }
        SDL_SetRenderDrawColor(gRenderer, 0x0D, 0x63, 0x02, 0xFF); //0D 53 02 mörk grön
        SDL_RenderClear(gRenderer);
        for(int i=0; i<13;i++){
            if(player_card[i].suit == 0)
                SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsClubs[player_card[i].value],&possition[i] , 0, NULL, flip);
            else if(player_card[i].suit == 1)
                SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsDiamonds[player_card[i].value],&possition[i] , 0, NULL, flip);
            else if(player_card[i].suit == 2)
                SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsHearts[player_card[i].value],&possition[i] , 0, NULL, flip);
            else if(player_card[i].suit == 3)
                SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsSpades[player_card[i].value],&possition[i] , 0, NULL, flip);
            else
                continue;
        }
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}

void loadMediaClubs(int i)
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

void loadMediaDiamonds(int i)
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

void loadMediaHearts(int i)
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

void loadMediaSpades(int i)
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

void loadMediaBack(int i)
{
    SDL_Surface* gCardSurface = IMG_Load("CARD.png");

    card[i] = SDL_CreateTextureFromSurface(gRenderer, gCardSurface);

    //baksida kort har värde 0.
    gSpriteClipsBack[ 0 ].x = WIDTH*1;
    gSpriteClipsBack[ 0 ].y = HEIGHT*4;
    gSpriteClipsBack[ 0 ].w = WIDTH;
    gSpriteClipsBack[ 0 ].h = HEIGHT;
}


bool init(){
    bool test = true;
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("SDL F4", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        printf("Fungerar ej\n");
        test = false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL){
        printf("Fungerar ej\n");
        test = false;
    }
    return test;

}
