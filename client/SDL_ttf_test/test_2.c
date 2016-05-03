//
//  main.c
//  sdl_ttf-test
//
//  Created by Niclas Ragnar on 2016-04-26.
//  Copyright (c) 2016 Niclas Ragnar. All rights reserved.
//
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#define WIN_H 1024
#define WIN_W 1024
int main(int argc, const char * argv[])
{
    SDL_Window* gWindow = NULL;
    SDL_Surface* gSurface = NULL;
    SDL_Renderer* gRenderer = NULL;
    //SDL_Surface* image = NULL;
    //SDL_Surface* surfaceRect = NULL;

    //Init SDL, returns error if failed.
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL2.0 Test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,400,SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            fprintf(stderr,"\nUnable to create window: %s\n",SDL_GetError());
            return 1;
        }
        else
        {
            //Window created.
            //gSurface = SDL_GetWindowSurface(gWindow);

        }
    }

    //init fonts.
    if (TTF_Init() != 0)
    {
        fprintf(stderr,"\nUnable to initialize TTF: %s\n", TTF_GetError());
        return 1;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
    if(gRenderer == NULL)
    {
        printf("gRenderer Fungerar ej\n%s\n",SDL_GetError());
    }
    SDL_RenderClear(gRenderer);


    TTF_Font* font = TTF_OpenFont("Calibri.ttf", 24); //Choses font and size
    if (font == NULL)
    {
        printf("font error\n");
    }
    SDL_Color textColor = {0,0,0}; //text color in RGB format


    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, "put your text here", textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); //surface converted to texture
    //SDL_FreeSurface(surfaceMessage);

    SDL_Rect Message_rect;      //create a rect
    Message_rect.x = 0;         //controls the rect's x coordinate
    Message_rect.y = 0;         // controls the rect's y coordinte
    Message_rect.w = 48;       // controls the width of the rect
    Message_rect.h = 24;       // controls the height of the rect

    bool isrunning = true;
    SDL_Event event;
    //Running loop.
    while (isrunning)
    {
        //Event-loop
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                isrunning = false;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0x10, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);


        //SDL_RenderDrawRect(gRenderer, NULL);
        SDL_RenderCopy(gRenderer, message, NULL ,NULL);

        SDL_RenderPresent(gRenderer);
        SDL_UpdateWindowSurface(gWindow);

    }

    SDL_FreeSurface(gSurface);
    SDL_DestroyWindow(gWindow);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
