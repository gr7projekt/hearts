//
//  createButton.c
//  surface
//
//  Created by Niclas Ragnar on 2016-05-02.
//  Copyright (c) 2016 Niclas Ragnar. All rights reserved.
//

#include "button.h"

button createButton(int x, int y, int w, int h, char* filename, SDL_Renderer *renderer)
{
    button button;
    button.rect.x = x; // x & y position of button
    button.rect.y = y;
    button.rect.w = w; // width & height of button
    button.rect.h = h;
    //strcpy(button.filename, filename); //Filename of image.

    button.surface = IMG_Load(filename); // Loads the image. ONLY BMP ATM! IMG_LOAD for png etc.
    button.texture = SDL_CreateTextureFromSurface(renderer, button.surface); //Self explanatory.
    SDL_FreeSurface(button.surface); // Free the surface, idk why. Good to do i think.
   // SDL_RenderCopy(renderer, button.texture, NULL, &button.rect); // Maybe bad?
    return button;
}

SDL_Rect createRect(int x, int y, int w, int h) // Define button properties here.
{
    SDL_Rect rect;

    rect.x = x; // x & y coordinates of the image.
    rect.y = y;
    rect.w = w; // Size of image & click-able area.
    rect.h = h;
    return rect;
}

bool clickButton(SDL_Event e, SDL_Rect rect)
{
    int x = 0; // Variables to store mouse x & y pos.
    int y = 0;

    if (e.button.button == SDL_BUTTON_LEFT) // Check for click.
    {
        x = e.button.x; // Get mouse x & y pos.
        y = e.button.y;

        if ( (x > rect.x) && (x < rect.x + rect.w) && (y > rect.y) && (y < rect.y + rect.h) ) // Checks for click-able area.
        {
            return true; // Do things.
        }
    }
    return false; // Don't do things.
}
