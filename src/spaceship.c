#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\biblio\SDLS.h"

#define GOOD_FIGHTER 0
#define SMALL_YELLOW_SPACESHIP 1
#define VIPER_MARK 2
#define REPUBLIC_WHITE_SHIP 3
#define SMALL_BLUE_SPACESHIP 4
#define REPUCLIB_ATTACK_CRUISER 6

typedef struct spaceship {

    //int test ;
    int posX ;
    int posY ;
    int speed;
    SDL_Texture * texture_spaceship;
    int isAlive;


}spaceship;

typedef struct bullet {

    int isBullet;
    int flag;
    int speed;
    int posX;
    int posY;
    SDL_Texture * texture_bullet;

} bullet;


void spaceship_init(spaceship *vaisseau){

    //puts("SPACESHIP_INIT()");
    vaisseau->texture_spaceship = SDLS_loadImage("images//goodFighter.png");
    vaisseau->posX = (SDLS_getScreenWidth() / 2) - 70;
    vaisseau->posY = SDLS_getScreenHeight() - 160;
    vaisseau->speed = 10;
    vaisseau->isAlive = true;
}


void init_bullet(bullet *bullet){
    bullet->flag = true;
    bullet->isBullet = false;
    bullet->posX = -50;
    bullet->posY = -50;
    bullet->speed = 10;
}


void move_spaceship_right(spaceship *vaisseau){
    if(vaisseau->isAlive)
    if(vaisseau->posX < SDLS_getScreenWidth() - 130)
            vaisseau->posX += vaisseau->speed;
}


void move_spaceship_left(spaceship *vaisseau){
    if(vaisseau->isAlive)
    if(vaisseau->posX >0)
            vaisseau->posX -= vaisseau->speed;
}


int threadExplosion( void* data )
{
    int iFire = 0;
    int iQuit = false;
    SDL_Rect spriteLargeExplosion1[16] =
    {
        {0  , 0  , 128, 128},
        {128, 0  , 128, 128},
        {256, 0  , 128, 128},
        {384, 0  , 128, 128},
        {0  , 128, 128, 128},
        {128, 128, 128, 128},
        {256, 128, 128, 128},
        {384, 128, 128, 128},
        {0  , 256, 128, 128},
        {128, 256, 128, 128},
        {256, 256, 128, 128},
        {384, 256, 128, 128},
        {0  , 384, 128, 128},
        {128, 384, 128, 128},
        {256, 384, 128, 128},
        {384, 384, 128, 128},
    };

    SDL_Texture * texture_large_exp1 = SDLS_loadImage("images//large_exp1.png");

    while( iQuit == false )
    {
        SDL_Rect destFire = {data, SDLS_getScreenHeight() - 160, 128, 128};
        SDLS_copyTextureEx(texture_large_exp1, spriteLargeExplosion1[iFire], destFire);
        iFire++;
        SDLS_displayAll();
        SDLS_eraseWithBackgroundColor(0,0,0);
        SDL_Delay(50);

        if(iFire >= 16)
            iQuit = true;
    }

    TTF_Font * ttfFont= SDLS_loadFont("fonts\\arial.ttf",95);// load font in RAM, size 15
    SDL_Texture *texture_text2= SDLS_loadText(ttfFont,"GAME OVER", 255,255,255); // copy text to print (in white color) to texture
    SDLS_copyTexture(texture_text2,50,50); // copy texture to window on position 200,100
    SDLS_displayAll();

}

void destroy_spaceship(spaceship *ship){

    if(ship->isAlive == true){
        int data = ship->posX;
        ship->isAlive = false;
        SDL_Thread* threadID = SDL_CreateThread( threadExplosion, "Receiver", (void*)data );
    }
}


void fire(spaceship *ship, bullet *bullet){

    if(bullet->flag == true){
        bullet->texture_bullet = SDLS_loadImage("images//bullet.png");
        bullet->isBullet = true;
        bullet->posX = ship->posX + 32;
        bullet->posY = SDLS_getScreenHeight() - 130;
    }

}

void load_spaceship(spaceship *ship, int choice){

    switch (choice){

    case SMALL_YELLOW_SPACESHIP :
        ship->texture_spaceship = SDLS_loadImage("images//small_yellow_spaceship.png");
        break;
    case VIPER_MARK :
        ship->texture_spaceship = SDLS_loadImage("images//viper_mark.png");
        break;
    case REPUBLIC_WHITE_SHIP :
        ship->texture_spaceship = SDLS_loadImage("images//republic_white_ship.png");
        break;
    case SMALL_BLUE_SPACESHIP:
        ship->texture_spaceship = SDLS_loadImage("images//small_blue_spaceship.gif");
        break;
    case GOOD_FIGHTER :
        ship->texture_spaceship = SDLS_loadImage("images//goodFighter.png");
        break;
    case REPUCLIB_ATTACK_CRUISER:
        ship->texture_spaceship = SDLS_loadImage("images//republic_attack_cruiser.png");
        break;

    }
}

