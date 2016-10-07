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


/* //Pour DEBUG
void test(spaceship *ship){

    ship->test = 36;
}*/


void spaceship_init(spaceship *vaisseau){

    //puts("SPACESHIP_INIT()");
    vaisseau->texture_spaceship = SDLS_loadImage("images//goodFighter.png");
    vaisseau->posX = 0;
    vaisseau->posY = SDLS_getScreenHeight() - 180;

}

void display_spaceship(spaceship *vaisseau){

    //puts("DISPLAY_SPACESHIP()");
    SDLS_copyTexture(vaisseau->texture_spaceship, vaisseau->posX, vaisseau->posY);
    SDLS_displayAll();
}

void move_spaceship(spaceship *vaisseau, int dX){

    if(dX >0){
        if(vaisseau->posX < SDLS_getScreenWidth() - 130)
            vaisseau->posX += dX;
    }
    else{
        if(vaisseau->posX >0)
            vaisseau->posX += dX;
    }
    //puts("MOVE()");
    SDLS_eraseWithBackgroundColor(0,0,0);
    SDLS_copyTexture(vaisseau->texture_spaceship, vaisseau->posX, vaisseau->posY);
    SDLS_displayAll();

}
