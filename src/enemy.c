#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\biblio\SDLS.h"
#include <spaceship.h>
#define SMALL_YELLOW_SPACESHIP 1
#define VIPER_MARK 2
#define REPUBLIC_WHITE_SHIP 3
#define SMALL_BLUE_SPACESHIP 4
#define SPACESHIP_ALIEN 5
#define REPUCLIB_ATTACK_CRUISER 6
#define DISCOVERY 7
#define ORANGE_SHIP 8

typedef struct enemy {

    int posX ;
    int posY ;
    int speed;
    SDL_Texture * texture_spaceship;
    int isAlive;
    int lives;
    int toggle;

} enemy;

typedef struct enemy_bullet {

    int isBullet;
    int flag;
    int fire_count;
    int speed;
    int posX;
    int posY;
    SDL_Texture * texture_bullet;

} enemy_bullet;

//GLOBAL VARIABLES
int toggle = false;
int toggle2 = false;
int fire_count = 0;


void init_enemy(enemy *evil, int enemy_level){

    evil->isAlive = true;
    evil->lives = 0;
    evil->speed = 7;
    evil->toggle = false;
    if(enemy_level == 0)
        evil->posX = 0;
    if(enemy_level == 1)
        evil->posX = SDLS_getScreenWidth() - 40;
    if(enemy_level == 2)
        evil->posX = SDLS_getScreenWidth() / 2;
    evil->posY = 0;
    evil->texture_spaceship = SDLS_loadImage("images//evilFighter.png");

}

void init_enemy_bullet(enemy_bullet *bullet){
    bullet->flag = true;
    bullet->isBullet = false;
    bullet->fire_count = 0;
    bullet->posX = -50;
    bullet->posY = -50;
    bullet->speed = 10;
}

void move_enemy(enemy * evil){
    if(evil->isAlive){
        if(evil->toggle == false)
            evil->posX += evil->speed;
        else
            evil->posX -= evil->speed;

        if(evil->posX >= SDLS_getScreenWidth() - 130)
            evil->toggle = true;
        if(evil->posX <= 0)
            evil->toggle = false;
    }

}


void destroy_enemy(enemy *ship){

    ship->isAlive = false;

}

void enemy_fire(enemy *ship, enemy_bullet *bullet, int iFire_level){

    if(ship->isAlive)
        if( (bullet->fire_count++ % iFire_level) == 0 ){
            if(bullet->flag == true){
                bullet->texture_bullet = SDLS_loadImage("images//bullet.png");
                bullet->isBullet = true;
                bullet->posX = ship->posX + 32;
                bullet->posY = 130;
            }
        }

}


void load_enemy(enemy *ship, int choice){

    switch (choice){

    case SMALL_YELLOW_SPACESHIP :
        ship->texture_spaceship = SDLS_loadImage("images//small_spaceship_enemy.png");
        break;
    case VIPER_MARK :
        ship->texture_spaceship = SDLS_loadImage("images//viper_mark_enemy.png");
        break;
    case REPUBLIC_WHITE_SHIP :
        ship->texture_spaceship = SDLS_loadImage("images//republic_white_ship.png");
        break;
    case SMALL_BLUE_SPACESHIP:
        ship->texture_spaceship = SDLS_loadImage("images//small_blue_spaceship_enemy.gif");
        break;
    case SPACESHIP_ALIEN:
        ship->texture_spaceship = SDLS_loadImage("images//spaceship_alien.png");
        break;
    case REPUCLIB_ATTACK_CRUISER:
        ship->texture_spaceship = SDLS_loadImage("images//republic_attack_cruiser_enemy.png");
        break;
    case DISCOVERY:
        ship->texture_spaceship = SDLS_loadImage("images//discovery.png");
        break;
    case ORANGE_SHIP:
        ship->texture_spaceship = SDLS_loadImage("images//ship.png");
        break;
    }
}

/* //MULTIPLAYER, Why not ..?
void move_enemy(enemy *evil, int gPosX){



}*/
