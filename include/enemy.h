#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\biblio\SDLS.h"
//#include <spaceship.h>


typedef struct enemy {

    int posX ;
    int posY ;
    int speed;
    SDL_Texture * texture_spaceship;
    int isAlive;

} enemy;

typedef struct enemy_bullet {

    int isBullet;
    int flag;
    int speed;
    int posX;
    int posY;
    SDL_Texture * texture_bullet;

} enemy_bullet;

void init_enemy(enemy*);
void init_enemy_bullet(enemy_bullet *);
void move_enemy(enemy*);
void destroy_enemy(enemy *);
void enemy_fire(enemy *, enemy_bullet *, int);
void load_enemy(enemy*, int);
