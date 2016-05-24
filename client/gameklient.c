#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
//#include <arpa/inet.h>
//#include <netinet/in.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "resolution.h"
#include "loadCard.h"
#include "cardPosition.h"
#include "loadMedia.h"

bool init();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* card[13] = {NULL};     //spelarens kort (det grafiska, inte riktiga handen)
SDL_Texture* card_2[13] = {NULL};   //v‰nster spelares baksida
SDL_Texture* card_3[13] = {NULL};   //motsatt spelares baksida
SDL_Texture* card_4[13] = {NULL};   //hˆger spelares baksida
SDL_Texture* advertisment[1] = {NULL};

SDL_Rect gSpriteClipsClubs[13];
SDL_Rect gSpriteClipsDiamonds[13];
SDL_Rect gSpriteClipsHearts[13];
SDL_Rect gSpriteClipsSpades[13];
SDL_Rect gSpriteClipsBack[1];
SDL_Rect gSpriteClipsAdvertisment[1];

int main(int argc, char *args[])
{
    int port = 45231;
    if(port >= 40000 && port <= 50000)
    {
            int mouse_x;
            int mouse_y;

            Card_struct player_card[13];     //spelarens riktiga kort
            Card_struct player_2_card[13];
            Card_struct player_3_card[13];
            Card_struct player_4_card[13];

            SDL_Event e;
            SDL_RendererFlip flip = SDL_FLIP_NONE; //SDL_FLIP_VERTICAL;
            bool quit = false;

            SDL_Rect position_1[13]; //positionen fˆr korten
            SDL_Rect position_2[13];
            SDL_Rect position_3[13];
            SDL_Rect position_4[13];
            SDL_Rect adv_pos[1];

            if (init()) {
                printf("init worked\n");
            }

            initCardPosition(position_1,position_2,position_3,position_4,adv_pos);

            loadCard(player_card, player_2_card, player_3_card, player_4_card);

            loadMediaAdvertisment(advertisment, gRenderer, gSpriteClipsAdvertisment);

            for(int i=0; i<13; i++)
            {
                printf("i: %d\n",i);
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
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if(e.button.button == SDL_BUTTON_LEFT)
                    {
                        mouse_x = e.button.x;
                        mouse_y = e.button.y;
                        if((mouse_x < adv_pos[0].w+adv_pos[0].x && mouse_x > adv_pos[0].x) && (mouse_y < adv_pos[0].h+adv_pos[0].y && mouse_y> adv_pos[0].y))
                            printf("reklam");
                    }

                }
                SDL_SetRenderDrawColor(gRenderer, 0x0D, 0x63, 0x02, 0xFF); //0D 53 02 mˆrk grˆn
                SDL_RenderClear(gRenderer);

                for(int i=0; i<13;i++){
                    SDL_RenderCopyEx(gRenderer, card_2[i], &gSpriteClipsBack[player_2_card[i].value],&position_2[i] , 0, NULL, flip);
                    SDL_RenderCopyEx(gRenderer, card_3[i], &gSpriteClipsBack[player_3_card[i].value],&position_3[i] , 0, NULL, flip);
                    SDL_RenderCopyEx(gRenderer, card_4[i], &gSpriteClipsBack[player_4_card[i].value],&position_4[i] , 0, NULL, flip);

                    if(player_card[i].suit == 0)
                        SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsClubs[player_card[i].value],&position_1[i] , 0, NULL, flip);
                    else if(player_card[i].suit == 1)
                        SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsDiamonds[player_card[i].value],&position_1[i] , 0, NULL, flip);
                    else if(player_card[i].suit == 2)
                        SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsHearts[player_card[i].value],&position_1[i] , 0, NULL, flip);
                    else if(player_card[i].suit == 3)
                        SDL_RenderCopyEx(gRenderer, card[i], &gSpriteClipsSpades[player_card[i].value],&position_1[i] , 0, NULL, flip);
                    else
                        continue;
                }
                SDL_RenderCopyEx(gRenderer, advertisment[0], &gSpriteClipsAdvertisment[0],&adv_pos[0] , 0, NULL, flip);

                SDL_RenderPresent(gRenderer);
            }
        }
        return 0;
}

        bool init(){
            bool test = true;
            SDL_Init(SDL_INIT_VIDEO);
            gWindow = SDL_CreateWindow("SDL F4", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, RES_X+75, RES_Y, SDL_WINDOW_SHOWN);
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
