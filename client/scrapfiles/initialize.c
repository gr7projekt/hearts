//
//  initialize.c
//  surface
//
//  Created by Niclas Ragnar on 2016-05-03.
//  Copyright (c) 2016 Niclas Ragnar. All rights reserved.
//

#include "libraries.h"

int initialize()
{
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    return 0
}