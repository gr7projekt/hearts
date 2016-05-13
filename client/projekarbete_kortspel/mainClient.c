//
//
//  SDLtesta
//
//  Created by Jonas Wåhslen on 2015-03-31.
//  Copyright (c) 2015 wahslen. All rights reserved.
//
//  Modified by Robert Kärrbrant on 2016-05-12 (13:55)
//

#include "includes.h"

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

    Player player_1[1];     //spelarens riktiga kort
    Player player_2[1];
    Player player_3[1];
    Player player_4[1];

    SDL_Event e;

    int my_turn = 1;        //lås om jag kan klicka på mina kort eller ej.
    int cardNr = -1;
    bool click = false;
    bool quit = false;
    bool picked[13] = {false};
    bool winner = true;
    int turn = 0;
    int leadCard = 0;       //färgen som startade ska man följa.
    bool brokenHeart = false;

    SDL_Rect position_1[13]; //positionen för korten till spelaren
    SDL_Rect position_2[13];
    SDL_Rect position_3[13];
    SDL_Rect position_4[13];
    SDL_Rect advertism_pos[1];
    SDL_Rect dropzone_pos[1];
    SDL_Rect initial_pos[1];

    SDL_Rect played_pos[4];

    initial_pos[0].y = RES_Y-HEIGHT; //korten man börjar med ligger alltid på samma höjd.. botten minus höjden på kortet.

    if (init()) {
        printf("init worked\n");
    }

    button help = createButton(0,0,20,20,"help.png",gRenderer);
    initSpritePosition(position_1,position_2,position_3,position_4,advertism_pos,dropzone_pos,played_pos);

    loadMediaAdvertisment(advertisment, gRenderer, gSpriteClipsAdvertisment);
    loadMediaDropzone(dropzone, gRenderer, gSpriteClipsDropzone);

    while(!quit)
    {
        while(turn < 13 && !quit)
        {
            if(winner)  //om runda är klar och någon vunnit, ladda nya kort.
            {
                resetTurn(player_1,player_2,player_3,player_4);
                winner = false;
                loadCard(player_1, player_2, player_3, player_4); //kortet som delas ut

//                for(int i=0; i<13; i++)
//                {
//                    printf("kort: %i , suit: %i \n", i, player_1[0].game_hand[i].suit);
//                }

                for(int i=0; i<13; i++)
                {
                    loadMediaBack(i, card_2, card_3, card_4, gRenderer, gSpriteClipsBack);

                    if(player_1[0].game_hand[i].suit == 0){
                        loadMediaClubs(player_1[0].game_hand[i].value, card, gRenderer, gSpriteClipsClubs);
                    }
                    else if(player_1[0].game_hand[i].suit == 1){
                        loadMediaDiamonds(player_1[0].game_hand[i].value, card, gRenderer, gSpriteClipsDiamonds);
                    }
                    else if(player_1[0].game_hand[i].suit == 2){
                        loadMediaHearts(player_1[0].game_hand[i].value, card, gRenderer, gSpriteClipsHearts);
                    }
                    else if(player_1[0].game_hand[i].suit == 3){
                        loadMediaSpades(player_1[0].game_hand[i].value, card, gRenderer, gSpriteClipsSpades);
                    }
                    else{
                        printf("error, unvalid card.");
                        return 1;
                    }
                }
            }

            while (SDL_PollEvent(&e))
            {
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
                    if(my_turn) //ska endast gå att flytta korten om det är min tur
                    {
                        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                        {
                            mouse_x=e.button.x;
                            mouse_y=e.button.y;
                            if(click == false)
                            {
                                cardNr = liftCard(initial_pos, position_1, mouse_x, mouse_y, picked);
                                click = true;
                               // printf("initial x pos: %d\n",initial_pos[0].x);
                               // printf("cardNr: %d\n", cardNr);
                            }

                            if(click==true && cardNr >-1)
                            {
                                mouse_x = e.motion.x;
                                mouse_y = e.motion.y;
                                moveCard(position_1, cardNr, mouse_x, mouse_y);
                            }
                        }
                    }
                }
                else
                {
                    click = false;
                }

                if(click == false && cardNr >-1)        //cardNr> -1 måste finnas för att undvika en bugg att baksidan laddas hos spelaren och blockerar kort.
                {
                    if(((position_1[cardNr].x + WIDTH/2 > dropzone_pos[0].x) && (position_1[cardNr].x + WIDTH/2 < dropzone_pos[0].x+dropzone_pos[0].w))&&((position_1[cardNr].y + HEIGHT/2 > dropzone_pos[0].y) && (position_1[cardNr].y + HEIGHT/2 < dropzone_pos[0].y + dropzone_pos[0].h)))
                    {
                        position_1[cardNr].x = played_pos[0].x; //droppas in på exakt plats
                        position_1[cardNr].y = played_pos[0].y; //droppas in på exakt plats


                        if(checkCard(player_1, cardNr, leadCard, brokenHeart, picked))
                        {
                            sendCard(player_1, cardNr);

                            turn++;
                            printf("turn %i\n",turn);
                            cardNr = -1;
                        }
                        else    //om kortet inte fick läggas i mitten
                        {
                            position_1[cardNr].x = initial_pos[0].x;
                            position_1[cardNr].y = initial_pos[0].y;
                            picked[cardNr] = false;
                        }
                    }
                    else    //
                    {
                        position_1[cardNr].x = initial_pos[0].x;
                        position_1[cardNr].y = initial_pos[0].y;
                    }
                }
            }

            SDL_SetRenderDrawColor(gRenderer, 0x0D, 0x63, 0x02, 0xFF); //0D 53 02 mörk grön
            SDL_RenderClear(gRenderer);

            SDL_RenderCopy(gRenderer, dropzone[0], &gSpriteClipsDropzone[0], &dropzone_pos[0] );
            SDL_RenderCopy(gRenderer, help.texture,NULL, &help.rect);

//            for(int i=0 ; i<4; i++)
//            {
//                SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsHearts[i],&played_pos[i]);
//            }

            for(int i = 0; i < 13 ; i++ )   //Renderar spelarens egna kort
            {
                if(player_1[0].game_hand[i].suit == 0 )
                    SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsClubs[player_1[0].game_hand[i].value],&position_1[i] );
                else if(player_1[0].game_hand[i].suit == 1 )
                    SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsDiamonds[player_1[0].game_hand[i].value],&position_1[i] );
                else if(player_1[0].game_hand[i].suit == 2 )
                    SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsHearts[player_1[0].game_hand[i].value],&position_1[i] );
                else if(player_1[0].game_hand[i].suit == 3 )
                    SDL_RenderCopy(gRenderer, card[i], &gSpriteClipsSpades[player_1[0].game_hand[i].value],&position_1[i] );
                else
                    continue;
            }
            for(int i = 0; i < 13 - player_2[0].turn ; i++ ){  //Renderar baksida kort till vänster
                SDL_RenderCopy(gRenderer, card_2[i], &gSpriteClipsBack[0],&position_2[i] );
            }
            for(int i = 0; i < 13 - player_3[0].turn ; i++ ){  //Renderar baksida kort mittemot
                SDL_RenderCopy(gRenderer, card_3[i], &gSpriteClipsBack[0],&position_3[i] );
            }
            for(int i = 0; i < 13 - player_4[0].turn ; i++ ){  //Renderar baksida kort höger
                SDL_RenderCopy(gRenderer, card_4[i], &gSpriteClipsBack[0],&position_4[i] );
            }

            SDL_RenderCopy(gRenderer, advertisment[0], &gSpriteClipsAdvertisment[0],&advertism_pos[0] );
            SDL_RenderPresent(gRenderer);

        }
        winner = true;
        turn = 0;
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
