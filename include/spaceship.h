#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\biblio\SDLS.h"

typedef struct spaceship {

    //int test ;
    int posX ;
    int posY ;
    SDL_Texture * texture_spaceship;


}spaceship;

void spaceship_init(spaceship*);
void display_spaceship(spaceship*);
void move_spaceship(spaceship*, int);
//void test(spaceship*);
