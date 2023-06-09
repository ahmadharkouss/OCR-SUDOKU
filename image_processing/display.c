
#include <err.h>
#include "SDL/SDL.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}


SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display1(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

   
    while(42){
        //To quit :
        SDL_Event red_cross;
        SDL_WaitEvent(&red_cross);
        //red cross for ubuntu
        if(red_cross.type == SDL_QUIT){
            break;
        }
        // keydown to use on Archlinux
        if(red_cross.type == SDL_KEYDOWN){
            if(red_cross.key.keysym.sym == SDLK_DOWN){
                break;
            }
        }
    }
    return screen;
}


