//
//
//  SDLtesta
//
//  Created by Jonas W�hslen on 2015-03-31.
//  Copyright (c) 2015 wahslen. All rights reserved.
//
//  Modified by Robert K�rrbrant on 2016-05-12 (13:55)
//

#include "includes.h"

//#include <windows.h>

bool init();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* advertisment[1] = {NULL};
SDL_Texture* dropzone[1] = {NULL};
SDL_Texture* coin[1] = {NULL};

SDL_Rect gSpriteClipsClubs[13];
SDL_Rect gSpriteClipsDiamonds[13];
SDL_Rect gSpriteClipsHearts[13];
SDL_Rect gSpriteClipsSpades[13];
SDL_Rect gSpriteClipsBack[1];
SDL_Rect gSpriteClipsAdvertisment[1];
SDL_Rect gSpriteClipsDropzone[1];
SDL_Rect gSpriteClipsCoin[1];

int main(int argc, char* args[])
{
    SDL_Texture* card[13] = {NULL};     //spelarens kort (det grafiska, inte riktiga handen)
    SDL_Texture* card_2[13] = {NULL};   //v�nster spelares baksida
    SDL_Texture* card_3[13] = {NULL};   //motsatt spelares baksida
    SDL_Texture* card_4[13] = {NULL};   //h�ger spelares baksida

    Uint16 port = 40000;

    int mouse_x;
    int mouse_y;

    Player player_1[1];     //spelarens riktiga kort
    Player player_2[1];
    Player player_3[1];
    Player player_4[1];

    SDL_Event e;

    int cardNr = -1;
    int turn = 0;
    int leadCard = 0;       //f�rgen som startade ska man f�lja.
    int whoIsPlaying;

    bool click = false;
    bool quit = false;
    bool picked[13] = {false};
    bool winner = true;
    bool brokenHeart = false;

                    //played card p0,p1,p2,p3 next turn
    char* trick[] = {"  ","  ","  ","  "};
    char recieved_trick[13] = {"EE;FF;FF;FF;"};
    char tmp[4];

//    char *trick[] = {"FF;", "EE;", "FF;", "FF;"};
//    char *trick[] = {"FF;", "FF;", "EE;", "FF;"};
//    char *trick[] = {"FF;", "FF;", "FF;", "EE;"};

    SDL_Rect position_1[13]; //positionen f�r korten till spelaren
    SDL_Rect position_2[13];
    SDL_Rect position_3[13];
    SDL_Rect position_4[13];
    SDL_Rect advertism_pos[1];
    SDL_Rect dropzone_pos[1];
    SDL_Rect initial_pos[1];    //temp var
    SDL_Rect played_pos[4]; //koordinaterna f�r spelade kort
    SDL_Rect coin_pos[5];

    initial_pos[0].y = RES_Y-HEIGHT; //korten man b�rjar med ligger alltid p� samma h�jd.. botten minus h�jden p� kortet.

    if (init()) {
        printf("init worked\n");
    }

    button help = createButton(0,0,20,20,"help.png",gRenderer);
    initSpritePosition(position_1,position_2,position_3,position_4,advertism_pos,dropzone_pos,played_pos,coin_pos);

    loadMediaCoin(coin, gRenderer, gSpriteClipsCoin);
    loadMediaAdvertisment(advertisment, gRenderer, gSpriteClipsAdvertisment);
    loadMediaDropzone(dropzone, gRenderer, gSpriteClipsDropzone);

    position(player_1,player_2,player_3,player_4);  //�ven absoluta platsen m�ste med som man f�r av server vid anslutning

<<<<<<< HEAD
    // create a UDPsocket on any available port (client)
    UDPsocket udpsock;
    UDPpacket *udPpacket;
    IPaddress iPaddress;
    uint8_t data;
    int channel;

    if(SDL_Init(0)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }
    // create a UDPsocket on any available port (client)
    udpsock=SDLNet_UDP_Open(0);
    if(!udpsock) {
        printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(2);
    }
    // Bind address to the first free channel
    //UDPsocket udpsock;
    //IPaddress *address;

    channel=SDLNet_UDP_Bind(udpsock, -1, &iPaddress);
    if(channel==-1) {
        printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
        // do something because we failed to bind
    }

=======
>>>>>>> parent of 27c486b... har påbörjat UDP-anropen
    while(!quit)
    {
        while(turn < 13 && !quit)
        {
<<<<<<< HEAD
            SDLNet_UDP_Recv(udpsock, udPpacket);
            strcpy(recieved_trick,(char *) udPpacket->data);
            int k=0;
            for(int i= 0;i<strlen(recieved_trick);i++,k++) {
                trick[k][0]=recieved_trick[i++];
                trick[k][1]=recieved_trick[i++];
                trick[k][2]='\0';
                printf(trick[k]);
            }
=======

            recieve(recieved_trick);
            seperate(trick, recieved_trick, tmp);
>>>>>>> parent of 27c486b... har påbörjat UDP-anropen
          //  for(int i=0; i<4; i++)
          //  {
          //      printf("%s",trick[i]);
          //  }printf("\n");

            if(winner)  //om runda �r klar och n�gon vunnit, ladda nya kort.
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
                else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    mouse_x = e.button.x;
                    mouse_y = e.button.y;
                    if((mouse_x < advertism_pos[0].w+advertism_pos[0].x && mouse_x > advertism_pos[0].x) && (mouse_y < advertism_pos[0].h+advertism_pos[0].y && mouse_y> advertism_pos[0].y))
                    {
                        openWeb();
                    }
                    if(clickButton(e, help.rect))//((mouse_x < help.rect.x+help.rect.w && mouse_x > help.rect.x) && (mouse_y < help.rect.y + help.rect.h && mouse_y > help.rect.y))
                    {
                        createWindow();
                    }
                }
                else if(e.type == SDL_MOUSEMOTION)
                {
                    if(myturn(trick,player_1))//strcmp(trick[player_1[0].id],"EE;") == 0) //ska endast g� att flytta korten om det �r min tur, +
                    {
                        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                        {
                            mouse_x=e.button.x;
                            mouse_y=e.button.y;
                            if(click == false)
                            {
                                cardNr = liftCard(initial_pos, position_1, mouse_x, mouse_y, picked);
                                click = true;
                            }

                            if(cardNr >-1)
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

                if(click == false && cardNr >-1)        //cardNr> -1 m�ste finnas f�r att undvika en bugg att baksidan laddas hos spelaren och blockerar kort.
                {
                    if(((position_1[cardNr].x + WIDTH/2 > dropzone_pos[0].x) && (position_1[cardNr].x + WIDTH/2 < dropzone_pos[0].x+dropzone_pos[0].w))&&((position_1[cardNr].y + HEIGHT/2 > dropzone_pos[0].y) && (position_1[cardNr].y + HEIGHT/2 < dropzone_pos[0].y + dropzone_pos[0].h)))
                    {
                        position_1[cardNr].x = -WIDTH;
                        position_1[cardNr].y = 0;
//                        position_1[cardNr].x = played_pos[0].x; //droppas in p� exakt plats
//                        position_1[cardNr].y = played_pos[0].y; //droppas in p� exakt plats

                        if(checkCard(player_1, cardNr, leadCard, brokenHeart, picked, turn, trick))
                        {
                            sendCard(player_1, cardNr, trick, recieved_trick);

                            printf("after sendCard: %c %c\n", trick[0][0], trick[0][1]);

                            turn++;
                            printf("turn %i\n",turn);
                            cardNr = -1;
                        }
                        else    //om kortet inte fick l�ggas i mitten
                        {
                            position_1[cardNr].x = initial_pos[0].x;
                            position_1[cardNr].y = initial_pos[0].y;
                            picked[cardNr] = false;
                        }
                    }
                    else    //om kortet placeras utanf�r dropbox
                    {
                        position_1[cardNr].x = initial_pos[0].x;
                        position_1[cardNr].y = initial_pos[0].y;
                    }
                }
            }

            SDL_SetRenderDrawColor(gRenderer, 0x0D, 0x63, 0x02, 0xFF); //0D 63 02
            SDL_RenderClear(gRenderer);

            whoIsPlaying = whos_turn(player_1,player_2,player_3,player_4,trick);
//            printf("wIP: %i\n",whoIsPlaying);

            SDL_RenderCopy(gRenderer, coin[0], &gSpriteClipsCoin[0], &coin_pos[whoIsPlaying]);
            SDL_RenderCopy(gRenderer, dropzone[0], &gSpriteClipsDropzone[0], &dropzone_pos[0] );

            renderPlayedCard(gRenderer, trick, played_pos, whoIsPlaying,
                             gSpriteClipsClubs, gSpriteClipsDiamonds, gSpriteClipsHearts, gSpriteClipsSpades,
                             card, card_2, card_3, card_4,
                             player_1,player_2,player_3,player_4); // renderar spelade kort i mitten

            SDL_RenderCopy(gRenderer, help.texture,NULL, &help.rect);

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
            for(int i = 0; i < 13 - player_2[0].turn ; i++ ){  //Renderar baksida kort till v�nster
                SDL_RenderCopy(gRenderer, card_2[i], &gSpriteClipsBack[0],&position_2[i] );
            }
            for(int i = 0; i < 13 - player_3[0].turn ; i++ ){  //Renderar baksida kort mittemot
                SDL_RenderCopy(gRenderer, card_3[i], &gSpriteClipsBack[0],&position_3[i] );
            }
            for(int i = 0; i < 13 - player_4[0].turn ; i++ ){  //Renderar baksida kort h�ger
                SDL_RenderCopy(gRenderer, card_4[i], &gSpriteClipsBack[0],&position_4[i] );
            }


            SDL_RenderCopy(gRenderer, advertisment[0], &gSpriteClipsAdvertisment[0],&advertism_pos[0] );
            SDL_RenderPresent(gRenderer);
        }
        winner = true;
        turn = 0;
    }
<<<<<<< HEAD
    SDLNet_UDP_Unbind(udpsock,channel);
    SDLNet_UDP_Close(udpsock);
    udpsock=NULL; //this helps us know that this UDPsocket is not valid anymore
    SDLNet_Quit();
=======
>>>>>>> parent of 27c486b... har påbörjat UDP-anropen
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
