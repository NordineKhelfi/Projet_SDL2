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


int youWin(spaceship * ship, int *flag){

        TTF_Font * ttfFont= SDLS_loadFont("fonts\\arial.ttf",95);// load font in RAM, size 15
        SDL_Texture *texture_text2= SDLS_loadText(ttfFont,"YOU WIN !!!!", 255,255,255); // copy text to print (in white color) to texture
        SDLS_copyTexture(texture_text2,50,50); // copy texture to window on position 200,100
        SDLS_copyTexture(ship->texture_spaceship, ship->posX, ship->posY);
        SDLS_displayAll();

        (*flag) = true;
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
        (*flag) = false;
        //SDL_Delay(1000);
    return true;
}



void finalDisplay(spaceship * ship, bullet * bullet, enemy * evil, enemy_bullet *en_bullet, enemy *evil2, enemy_bullet *en_bullet2, enemy *evil3, enemy_bullet *en_bullet3, int *flag){

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

        if(en_bullet2->isBullet){
            en_bullet2->flag = false;
            if(en_bullet2->posY <= SDLS_getScreenHeight()){
                en_bullet2->posY += en_bullet2->speed;
                SDLS_copyTexture(en_bullet2->texture_bullet, en_bullet2->posX, en_bullet2->posY);
            }
            else{
                en_bullet2->isBullet = false;
                en_bullet2->flag = true;
                en_bullet2->posX = -50;
            }
        }

        if(en_bullet3->isBullet){
            en_bullet3->flag = false;
            if(en_bullet3->posY <= SDLS_getScreenHeight()){
                en_bullet3->posY += en_bullet3->speed;
                SDLS_copyTexture(en_bullet3->texture_bullet, en_bullet3->posX, en_bullet3->posY);
            }
            else{
                en_bullet3->isBullet = false;
                en_bullet3->flag = true;
                en_bullet3->posX = -50;
            }
        }

        SDLS_copyTexture(ship->texture_spaceship, ship->posX, ship->posY);
        if(evil->isAlive)
            SDLS_copyTexture(evil->texture_spaceship, evil->posX, evil->posY);
        if(evil2->isAlive)
            SDLS_copyTexture(evil2->texture_spaceship, evil2->posX, evil2->posY);
        if(evil3->isAlive)
            SDLS_copyTexture(evil3->texture_spaceship, evil3->posX, evil3->posY);

        //DISPLAY LIVES NUMBER
        SDL_Texture *texture_Heart = SDLS_loadImage("images\\59_heart.png");
        TTF_Font * ttfFont= SDLS_loadFont("fonts\\arial.ttf",30);// load font in RAM, size 15
        char cLives[3];
        sprintf(cLives, "x%d", ship->lives);
        SDL_Texture *texture_text_lives= SDLS_loadText(ttfFont, cLives, 255,255,255); // copy text to print (in white color) to texture
        SDLS_copyTexture(texture_Heart, SDLS_getScreenWidth() - 100, SDLS_getScreenHeight() - 45);
        SDLS_copyTexture(texture_text_lives,SDLS_getScreenWidth() - 65, SDLS_getScreenHeight() - 45); // copy texture to window on position 200,100

        //DISPLAY SUPERFIRE NUMBER
        SDL_Texture *texture_super_fire = SDLS_loadImage("images\\green_bullet_mini.png");
        char cSuper_shots[3];
        sprintf(cSuper_shots, "x%d", ship->superShot);
        SDL_Texture *texture_text_shots= SDLS_loadText(ttfFont, cSuper_shots, 255,255,255); // copy text to print (in white color) to texture
        SDLS_copyTexture(texture_text_shots,SDLS_getScreenWidth() - 65, SDLS_getScreenHeight() - 80);
        SDLS_copyTexture(texture_super_fire, SDLS_getScreenWidth() - 115, SDLS_getScreenHeight() - 80);
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

        (*flag) = true;
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
        (*flag) = false;

    }

}


