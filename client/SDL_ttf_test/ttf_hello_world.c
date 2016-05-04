//
//https://wiki.libsdl.org/SDL_RenderCopy
//http://www.sdltutorials.com/sdl-ttf
//https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_43.html
//

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>

#define RES_Y 480
#define RES_X 640
#define SHAPE_SIZE 18

bool init();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

int main(int argc, char* args[])
{
    bool quit;
    SDL_Event e;
    SDL_Rect src;
    SDL_Rect dst;
    char trash[40];
    char str[21];

    printf("skriv in anvandarnamn.\n");
    printf("max 20 tecken sparas: ");
    fgets(trash,sizeof(trash),stdin);

//    int len = strlen(trash);
//    printf("len: %d\n",len);

    if(strlen(trash)>21 || strlen(trash)<2) //enterslaget räknas som 1 i längd
    {
        while(strlen(trash)>21 || strlen(trash)<2)
        {
            printf("for langt eller kort namn, max 20 tecken: ");
            fgets(trash,sizeof(trash),stdin);
//            len = strlen(trash);
//            printf("len: %d\n",len);
        }
    }

    for(int i=0;i<21;i++)
    {
        if(trash[i]=='\n')
        {
            trash[i]='\0';
        }
        str[i]=trash[i];
    }


//    char str[]="hello world!";
    printf("%s\n", str);

    src.x = 0;
    src.y = 0;
    src.w = SHAPE_SIZE*strlen(str)/2+1;
    src.h = SHAPE_SIZE;

    dst.x = RES_X/2-SHAPE_SIZE/2;
    dst.y = RES_Y/2-SHAPE_SIZE/2;
    dst.w = SHAPE_SIZE*strlen(str)/2+1;
    dst.h = SHAPE_SIZE;


    if (init()) {
        printf("init worked\n");
    }

    //TTL initiering
    if (TTF_Init() != 0){
        fprintf(stderr,"\nUnable to initialize TTF: %s\n", TTF_GetError());
        return 1;
    }
    //Open font
    gFont = TTF_OpenFont( "Calibri.ttf", SHAPE_SIZE);
    //misslyckad öppning?
    if( gFont == NULL ){
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	SDL_Color textColor = { 0, 0, 0 };
	//SDL_Color backColor = {255,255,255};
	TTF_SetFontStyle(gFont,TTF_STYLE_NORMAL);

    SDL_Surface* surfaceMessage = TTF_RenderUTF8_Blended(gFont,str,textColor);


    if(surfaceMessage == NULL){
        printf("Failed to render %s\n", TTF_GetError());
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);



    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xF0, 0xF0, 0xF0, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer, message, &src , &dst);

        SDL_RenderPresent(gRenderer);
    }
    return 0;
}

bool init(){
    bool test = true;
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Heartstart", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, RES_X, RES_Y, SDL_WINDOW_SHOWN);
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

