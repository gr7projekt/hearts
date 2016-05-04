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
#include <time.h>

#include "resolution.h"
#include "loadCard.h"
#include "cardPosition.h"
#include "loadMedia.h"
#include "openWeb.h"
#include "moveCard.h"

bool init();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* card[13] = {NULL};     //spelarens kort (det grafiska, inte riktiga handen)
SDL_Texture* card_2[13] = {NULL};   //vänster spelares baksida
SDL_Texture* card_3[13] = {NULL};   //motsatt spelares baksida
SDL_Texture* card_4[13] = {NULL};   //höger spelares baksida
SDL_Texture* advertisment[1] = {NULL};
SDL_Texture* dropzone[1] = {NULL};

SDL_Rect gSpriteClipsClubs[13];
SDL_Rect gSpriteClipsDiamonds[13];
SDL_Rect gSpriteClipsHearts[13];
SDL_Rect gSpriteClipsSpades[13];
SDL_Rect gSpriteClipsBack[1];
SDL_Rect gSpriteClipsAdvertisment[1];
SDL_Rect gSpriteClipsDropzone[1];

int main(int argc, char* args[])
{
    int mouse_x;
    int mouse_y;

    int turn=0;

    Card_struct player_card[13];     //spelarens riktiga kort
    Card_struct player_2_card[13];
    Card_struct player_3_card[13];
    Card_struct player_4_card[13];

    SDL_Event e;

    int cardNr=-1;
    bool click = false;
    bool quit = false;

    SDL_Rect position_1[13]; //positionen för korten
    SDL_Rect position_2[13];
    SDL_Rect position_3[13];
    SDL_Rect position_4[13];
    SDL_Rect advertism_pos[1];
    SDL_Rect dropzone_pos[1];
    SDL_Rect initial_pos[1];

    initial_pos[0].y = RES_Y-HEIGHT; //korten man börjar med ligger alltid på samma höjd.. botten minus höjden på kortet.

    if (init()) {
        printf("init worked\n");
    }

    initCardPosition(position_1,position_2,position_3,position_4,advertism_pos,dropzone_pos);
    loadCard(player_card, player_2_card, player_3_card, player_4_card);

    loadMediaAdvertisment(advertisment, gRenderer, gSpriteClipsAdvertisment);
    loadMediaDropzone(dropzone, gRenderer, gSpriteClipsDropzone);

    for(int i=0; i<13; i++)
    {
        loadMediaBack(i, card_2, card_3, card_4, gRenderer, gSpriteClipsBack);

        if(player_card[i].suit == 0){
            loadMediaClubs(player_card[i].value, card, gRenderer, gSpriteClipsClubs);
        }
        else if(player_card[i].suit == 1){
            loadMediaDiamonds(player_card[i].value, card, gRenderer, gSpriteClipsDiamonds);
        }
        else if(player_card[i].suit == 2){
            loadMediaHearts(player_card[i].value, card, gRenderer, gSpriteClipsHearts);
        }
        else if(player_card[i].suit == 3){
            loadMediaSpades(player_card[i].value, card, gRenderer, gSpriteClipsSpades);
        }
        else{
            printf("error, unvalid card.");
        }
    }

    while (!quit) {
      //  Sleep(800);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    mouse_x = e.button.x;
                    mouse_y = e.button.y;
                    {
                        if((mouse_x < advertism_pos[0].w+advertism_pos[0].x && mouse_x > advertism_pos[0].x) && (mouse_y < advertism_pos[0].h+advertism_pos[0].y && mouse_y> advertism_pos[0].y))
                        {
                            openWeb();
                        }
                    }
                }
            }


            else if(e.type == SDL_MOUSEMOTION)
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    mouse_x=e.button.x;
                    mouse_y=e.button.y;
                    if(click == false)
                    {
                        cardNr = liftCard(initial_pos, position_1,mouse_x,mouse_y);
                        click = true;
                        printf("initial x pos: %d\n",initial_pos[0].x);
                        printf("cardNr: %d\n", cardNr);
                    }

                    if(click==true)
                    {
                        mouse_x = e.motion.x;
                        mouse_y = e.motion.y;
                        moveCard(position_1, cardNr, mouse_x, mouse_y);
                    }
                }
            }
            else
            {
                click=false;
            }
            if(click == false && cardNr >-1)        //cardNr> -1 måste finnas för att undvika en bugg att baksidan laddas hos spelaren och blockerar kort.
            {
                if(((position_1[cardNr].x + WIDTH/2 > dropzone_pos[0].x) && (position_1[cardNr].x + WIDTH/2 < dropzone_pos[0].x+dropzone_pos[0].w))&&((position_1[cardNr].y + HEIGHT/2 > dropzone_pos[0].y) && (position_1[cardNr].y + HEIGHT/2 < dropzone_pos[0].y + dropzone_pos[0].h)))
                {
                    //printf("innanfor dropzone \n");
                }
                else
                {
                    position_1[cardNr].x = initial_pos[0].x;
                    position_1[cardNr].y = initial_pos[0].y;
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0x0D, 0x63, 0x02, 0xFF); //0D 53 02 mörk grön

        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer, dropzone[0], &gSpriteClipsDropzone[0], &dropzone_pos[0] );

        for(int i = 0; i < 13 - turn ; i++ ){
                SDL_RenderCopy(gRenderer, card_2[i], &gSpriteClipsBack[player_2_card[i].value],&position_2[i] );
                SDL_RenderCopy(gRenderer, card_3[i], &gSpriteClipsBack[player_3_card[i].value],&position_3[i] );
                SDL_RenderCopy(gRenderer, card_4[i], &gSpriteClipsBack[player_4_card[i].value],&position_4[i] );

            if(player_card[i].suit == 0)
                SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsClubs[player_card[i].value],&position_1[i] );
            else if(player_card[i].suit == 1)
                SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsDiamonds[player_card[i].value],&position_1[i] );
            else if(player_card[i].suit == 2)
                SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsHearts[player_card[i].value],&position_1[i] );
            else if(player_card[i].suit == 3)
                SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsSpades[player_card[i].value],&position_1[i] );
            else
                continue;
        }

        SDL_RenderCopy(gRenderer, advertisment[0], &gSpriteClipsAdvertisment[0],&advertism_pos[0] );

        SDL_RenderPresent(gRenderer);
//        turn ++;
//        if (turn==13)
//            turn=0;
    }
    return 0;
}

bool init(){
    bool test = true;
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Heartstart Cardgame", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, RES_X+75, RES_Y, SDL_WINDOW_SHOWN);
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
