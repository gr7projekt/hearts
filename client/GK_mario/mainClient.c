//
//
// Created by Grupp7 as part of course HI2016
// 2016-06-03
//
//
//
//

#include "includes.h"

//#include <windows.h>

bool init();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* dropzone[1] = {NULL};
SDL_Texture* coin[1] = {NULL};

SDL_Rect gSpriteClipsClubs[13];
SDL_Rect gSpriteClipsDiamonds[13];
SDL_Rect gSpriteClipsHearts[13];
SDL_Rect gSpriteClipsSpades[13];
SDL_Rect gSpriteClipsBack[1];
SDL_Rect gSpriteClipsDropzone[1];
SDL_Rect gSpriteClipsCoin[1];

int main(int argc, char* argv[])
{
    SDL_Texture* card_club[13] = {NULL};
    SDL_Texture* card_diamond[13] = {NULL};
    SDL_Texture* card_heart[13] = {NULL};
    SDL_Texture* card_spade[13] = {NULL};

    SDL_Texture* card_back[13] = {NULL};

    //int preport = //atoi(argv[1]);
    Uint16 port = 41337; //(Uint16)preport;

    if(port >= 40000 && port <= 50000) {

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
        int whoStarted;

        int count;

        bool click = false;
        bool quit = false;
        bool picked[13] = {false};
        bool brokenHeart = false;

        char *trick[4];
        char recievetable[13] = {"EE;FF;FF;FF;"};
        char tmptable[13];
        char myhand[40];
        char tmp[4];

        //    char *trick[] = {"FF", "EE", "FF", "FF"};
        //    char *trick[] = {"FF", "FF", "EE", "FF"};
        //    char *trick[] = {"FF", "FF", "FF", "EE"};

        SDL_Rect position_1[13]; //positionen f�r korten till spelaren
        SDL_Rect position_2[13];
        SDL_Rect position_3[13];
        SDL_Rect position_4[13];
        SDL_Rect dropzone_pos[1];
        SDL_Rect initial_pos[1];    //temp var
        SDL_Rect played_pos[4]; //koordinaterna f�r spelade kort
        SDL_Rect coin_pos[5];

        initial_pos[0].y = RES_Y - HEIGHT; //korten man b�rjar med ligger alltid p� samma h�jd.. botten minus h�jden p� kortet.

        if (init()) {
            printf("init worked\n");
        }
        if(SDLNet_Init()==-1) {
            printf("SDLNet_Init: %s\n", SDLNet_GetError());
            exit(2);
        }

        char ip[20];
        getIP(ip);
        printf("ip: %s\n",ip);


        //de knappar som alltid finns.
        button advertisment = createButton(RES_X+10, RES_Y/2-200, 65, 400, "advertisment2.png", gRenderer);
        button help = createButton(0, 0, 20, 20, "help.png", gRenderer);

        initSpritePosition(position_1, position_2, position_3, position_4, dropzone_pos, played_pos, coin_pos);

        loadMediaCoin(coin, gRenderer, gSpriteClipsCoin);
        loadMediaDropzone(dropzone, gRenderer, gSpriteClipsDropzone);
        loadMediaBack(card_back, gRenderer, gSpriteClipsBack);
        for (int i = 0; i < 13; i++) {
            loadMediaClubs(i,card_club, gRenderer, gSpriteClipsClubs);
            loadMediaDiamonds(i,card_diamond, gRenderer, gSpriteClipsDiamonds);
            loadMediaHearts(i,card_heart, gRenderer, gSpriteClipsHearts);
            loadMediaSpades(i,card_spade, gRenderer, gSpriteClipsSpades);

        }

        position(player_1, player_2, player_3, player_4);  //�ven absoluta platsen m�ste med som man f�r av server vid anslutning argv[2]
        zeropoint(player_1,player_2,player_3,player_4);

        while (!quit) {
            recievehand(myhand);

            if(strlen(myhand)==39){
                printf("efter recieve: %s\n",myhand);
                resetTurn(player_1, player_2, player_3, player_4);
                loadCard(player_1, player_2, player_3, player_4, myhand); //kortet som delas ut
                printf("efter load card\n");
            }

            while (turn < 13 && !quit) {

              //  receiveontable(recievetable);

                if(strlen(recievetable)==12){
                    for (int i=0;i<13;i++)
                        tmptable[i] = recievetable[i];  //sparar strängen för att kunna skicka tillbaka hela med mitt lagda kort.

                    split(recievetable,';',trick);
                    //seperate(trick, recievetable, tmp, &whoStarted);
                }

                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                        mouse_x = e.button.x;
                        mouse_y = e.button.y;

                        if (clickButton(e, advertisment.rect)){//(mouse_x < advertism_pos[0].w + advertism_pos[0].x && mouse_x > advertism_pos[0].x) && (mouse_y < advertism_pos[0].h + advertism_pos[0].y && mouse_y > advertism_pos[0].y)) {
                            openWeb();
                        }
                        if (clickButton(e, help.rect)){//((mouse_x < help.rect.x+help.rect.w && mouse_x > help.rect.x) && (mouse_y < help.rect.y + help.rect.h && mouse_y > help.rect.y))
                            createWindow();
                        }
                    }
                    else if (e.type == SDL_MOUSEMOTION) {

                        //POLL EVENT LOCK FOR MY CARDS, LOCK IF NOT MY TURN
                        if (myturn(trick, player_1))//strcmp(trick[player_1[0].id],"EE;") == 0) //ska endast g� att flytta korten om det �r min tur, +
                        {
                            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                                mouse_x = e.button.x;
                                mouse_y = e.button.y;
                                if (click == false) {
                                    cardNr = liftCard(initial_pos, position_1, mouse_x, mouse_y, picked);
                                    click = true;
                                }

                                if (cardNr > -1) {
                                    mouse_x = e.motion.x;
                                    mouse_y = e.motion.y;
                                    moveCard(position_1, cardNr, mouse_x, mouse_y);
                                }
                            }
                        }
                    }
                    else {
                        click = false;
                    }

                    if (click == false && cardNr > -1)        //cardNr> -1 m�ste finnas f�r att undvika en bugg att baksidan laddas hos spelaren och blockerar kort.
                    {
                        if (((position_1[cardNr].x + WIDTH / 2 > dropzone_pos[0].x) && (position_1[cardNr].x + WIDTH / 2 < dropzone_pos[0].x + dropzone_pos[0].w)) && ((position_1[cardNr].y + HEIGHT / 2 > dropzone_pos[0].y) && (position_1[cardNr].y + HEIGHT / 2 < dropzone_pos[0].y + dropzone_pos[0].h))) {

                            position_1[cardNr].x = -WIDTH;
                            position_1[cardNr].y = 0;

                            if (checkCard(player_1, cardNr, leadCard, brokenHeart, picked, turn, trick)) {
                                sendCard(player_1, cardNr, trick, recievetable, &port,tmptable);

                                printf("after sendCard: %c %c\n", trick[0][0], trick[0][1]);

                                turn++;
                                printf("turn %i\n", turn);
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

                whoIsPlaying = whos_turn(player_1, player_2, player_3, player_4, trick);

                SDL_RenderCopy(gRenderer, coin[0], &gSpriteClipsCoin[0], &coin_pos[whoIsPlaying]);
                SDL_RenderCopy(gRenderer, dropzone[0], &gSpriteClipsDropzone[0], &dropzone_pos[0]);

                renderPlayedCard(gRenderer, trick, played_pos, whoIsPlaying,
                                 gSpriteClipsClubs, gSpriteClipsDiamonds, gSpriteClipsHearts, gSpriteClipsSpades,
                                 card_club, card_diamond, card_heart, card_spade,
                                 player_1, player_2, player_3, player_4); // renderar spelade kort i mitten


                SDL_RenderCopy(gRenderer, help.texture, NULL, &help.rect);
                SDL_RenderCopy(gRenderer, advertisment.texture, NULL, &advertisment.rect);

                for (int i = 0; i < 13; i++)   //Renderar spelarens egna kort
                {
                    if (player_1[0].game_hand[i].suit == 0)
                        SDL_RenderCopy(gRenderer, card_club[i], &gSpriteClipsClubs[player_1[0].game_hand[i].value],
                                       &position_1[i]);
                    else if (player_1[0].game_hand[i].suit == 1)
                        SDL_RenderCopy(gRenderer, card_diamond[i], &gSpriteClipsDiamonds[player_1[0].game_hand[i].value],
                                       &position_1[i]);
                    else if (player_1[0].game_hand[i].suit == 2)
                        SDL_RenderCopy(gRenderer, card_heart[i], &gSpriteClipsHearts[player_1[0].game_hand[i].value],
                                       &position_1[i]);
                    else if (player_1[0].game_hand[i].suit == 3)
                        SDL_RenderCopy(gRenderer, card_spade[i], &gSpriteClipsSpades[player_1[0].game_hand[i].value],
                                       &position_1[i]);
                    else
                        continue;
                }
                for (int i = 0; i < 13 - player_2[0].turn; i++) {  //Renderar baksida kort till v�nster
                    SDL_RenderCopy(gRenderer, card_back[0], &gSpriteClipsBack[0], &position_2[i]);
                }
                for (int i = 0; i < 13 - player_3[0].turn; i++) {  //Renderar baksida kort mittemot
                    SDL_RenderCopy(gRenderer, card_back[0], &gSpriteClipsBack[0], &position_3[i]);
                }
                for (int i = 0; i < 13 - player_4[0].turn; i++) {  //Renderar baksida kort h�ger
                    SDL_RenderCopy(gRenderer, card_back[0], &gSpriteClipsBack[0], &position_4[i]);
                }

                SDL_RenderPresent(gRenderer);
                count++;
                printf("count: %d\n",count);
            }
            turn = 0;
        }
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
