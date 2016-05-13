//
//  createWindow.c
//  surface
//
//  Created by Niclas Ragnar on 2016-05-02.
//  Copyright (c) 2016 Niclas Ragnar. All rights reserved.
//

#include "window.h"

#define HWIN_WIDTH 640+75 // Window size, ez to change.
#define HWIN_LENGTH 480

void createWindow()
{
    bool running = true;
    int windowID = 0;
    SDL_Event event;
    SDL_Window* window = NULL;
    SDL_Surface* image = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* rules = NULL;
    
    SDL_Init(SDL_INIT_VIDEO); // Init things. Prints error message if failed.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
    }
    
    window = SDL_CreateWindow("Help Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,HWIN_WIDTH,HWIN_LENGTH,SDL_WINDOW_SHOWN); //Creates the window. Prints error message if failed.
    if (window == NULL) {
        fprintf(stderr,"\nUnable to create new window: %s\n",SDL_GetError());
    }
    else {
        windowID = SDL_GetWindowID(window); // Sucess, get window ID.
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE); // Create renderer. Prints error message if failed.
    if(renderer == NULL) {
        printf("\nrenderer not working: %s\n",SDL_GetError());
    }

    image = SDL_LoadBMP("heart-rules.bmp"); // Loads rule image. Prints error message if failed.
    if (image == NULL) {
        printf("\nUnable to load image: %s\n", SDL_GetError());
    }
    
    rules = SDL_CreateTextureFromSurface(renderer, image);
    if (rules == NULL) { // Convert previous image to texture for rendering. Prints error message if failed.
        printf("\nUnable to create texture: %s\n", SDL_GetError());
    }

    while (running)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, rules, NULL ,NULL);
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_WINDOWEVENT && SDL_WINDOWEVENT_CLOSE == event.window.event && event.window.windowID == windowID)
            {
                running = false;
            }
        }
    }
    SDL_DestroyTexture(rules);
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

