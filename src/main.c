#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\biblio\SDLS.h"
#include "..\biblio\net.h"

int main(int argc, char** argv)
{
    /* Initialisation simple */
    SDL_Event event;
// create window with a title
    SDLS_init("Hello World");

    SDLS_eraseWithBackgroundColor(255,255,255);

    SDL_Quit();

    return 0;
}
