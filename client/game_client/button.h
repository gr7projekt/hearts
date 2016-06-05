//
//  button.h
//  surface
//
//  Created by Niclas Ragnar on 2016-05-02.
//  Copyright (c) 2016 Niclas Ragnar. All rights reserved.
//

#ifndef __surface__createButton__
#define __surface__createButton__

#include "includes.h"

bool clickButton(SDL_Event e, SDL_Rect rect); // Checks if button was clicked or not.
SDL_Rect createRect(int x, int y, int w, int h); // Creates a rectangle, used in Button struct.
button createButton(int x, int y, int w, int h, char* filename,SDL_Renderer* renderer); // Creates the button and specifies wich file to load. ALSO RENDERS ATM! Maybe not needed? x & y is coordinate and w is size.

#endif /* defined(__surface__createButton__) */
