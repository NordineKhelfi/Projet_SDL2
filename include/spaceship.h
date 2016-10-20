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
    int speed;
    SDL_Texture * texture_spaceship;
    int isAlive;
    int lives;
    int superShot;


}spaceship;

typedef struct bullet {

    int isBullet;
    int flag;
    int speed;
    int posX;
    int posY;
    SDL_Texture * texture_bullet;

} bullet;

void spaceship_init(spaceship*);
void move_spaceship_right(spaceship*);
void move_spaceship_left(spaceship*);
void destroy_spaceship(spaceship*);
void fire(spaceship*, bullet*);
void super_fire(spaceship*, bullet*);
void init_bullet(bullet *);
void load_spaceship(spaceship*, int);
//void test(spaceship*);
