//
//  struct.h
//  surface
//
//  Created by Niclas Ragnar on 2016-05-02.
//  Copyright (c) 2016 Niclas Ragnar. All rights reserved.
//

#ifndef surface_struct_h
#define surface_struct_h

struct Button { // Contains all nesseccary information for creating a button.
    const char* filename[50]; // Filename of the image to load.
    struct SDL_Rect rect; // Contains x & y coordinates and width and height of button.
    struct SDL_Surface* surface; // Surface the image is loaded on.
    struct SDL_Texture* texture; // The texture that is rendered.
};
typedef struct Button button; // Self explanatory.

#endif
