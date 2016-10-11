#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\biblio\SDLS.h"
#include "..\biblio\net.h"
#include <spaceship.h>
#include <enemy.h>


int youWin(spaceship * ship){

        TTF_Font * ttfFont= SDLS_loadFont("fonts\\arial.ttf",95);// load font in RAM, size 15
        SDL_Texture *texture_text2= SDLS_loadText(ttfFont,"YOU WIN !!!!", 255,255,255); // copy text to print (in white color) to texture
        SDLS_copyTexture(texture_text2,50,50); // copy texture to window on position 200,100
        SDLS_copyTexture(ship->texture_spaceship, ship->posX, ship->posY);
        SDLS_displayAll();

        SDL_Delay(1500);

        int dY = 1;
    while(ship->posY >= -150){

        ship->posY -= dY;
        dY++;
        SDLS_eraseWithBackgroundColor(0,0,0);
        SDLS_copyTexture(ship->texture_spaceship, ship->posX, ship->posY);
        SDLS_copyTexture(texture_text2,50,50);
        SDLS_displayAll();
    }
        //SDL_Delay(1000);
    return true;
}



void finalDisplay(spaceship * ship, bullet * bullet, enemy * evil, enemy_bullet *en_bullet){

    int iQuit = false;

    if(ship->isAlive){
        SDLS_eraseWithBackgroundColor(0,0,0);

        if(bullet->isBullet){
            bullet->flag = false;
            if(bullet->posY >=0){
                bullet->posY -= bullet->speed;
                SDLS_copyTexture(bullet->texture_bullet, bullet->posX, bullet->posY);
            }
            else{
                bullet->isBullet = false;
                bullet->flag = true;
                bullet->posX = -50;
            }
        }

        if(en_bullet->isBullet){
            en_bullet->flag = false;
            if(en_bullet->posY <= SDLS_getScreenHeight()){
                en_bullet->posY += en_bullet->speed;
                SDLS_copyTexture(en_bullet->texture_bullet, en_bullet->posX, en_bullet->posY);
            }
            else{
                en_bullet->isBullet = false;
                en_bullet->flag = true;
                en_bullet->posX = -50;
            }
        }

        SDLS_copyTexture(ship->texture_spaceship, ship->posX, ship->posY);
        if(evil->isAlive)
            SDLS_copyTexture(evil->texture_spaceship, evil->posX, evil->posY);

        SDLS_displayAll();
    }

    if(!evil->isAlive){
        ship->isAlive = false;
        int iFire = 0;
        SDL_Rect spriteLargeExplosion2[16] =
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

        SDL_Texture * texture_large_exp2 = SDLS_loadImage("images//large_exp2.png");

        while( iQuit == false )
        {
            SDL_Rect destFire = {evil->posX, 20, 128, 128};
            SDLS_copyTextureEx(texture_large_exp2, spriteLargeExplosion2[iFire], destFire);
            SDLS_copyTexture(ship->texture_spaceship, ship->posX, ship->posY);
            iFire++;
            SDLS_displayAll();
            SDLS_eraseWithBackgroundColor(0,0,0);
            SDL_Delay(50);


            if(iFire >= 16)
                iQuit = true;
        }

    }

}


