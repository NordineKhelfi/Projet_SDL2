#define JEU
#ifdef  JEU

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

//#define CHEAT

#define GOOD_FIGHTER 0
#define SMALL_YELLOW_SPACESHIP 1
#define VIPER_MARK 2
#define REPUBLIC_WHITE_SHIP 3
#define SMALL_BLUE_SPACESHIP 4
#define SPACESHIP_ALIEN 5
#define REPUCLIB_ATTACK_CRUISER 6
#define DISCOVERY 7
#define ORANGE_SHIP 8

#define ENEMY_FIRE_LEVEL_1 50
#define ENEMY_FIRE_LEVEL_2 30
#define ENEMY_FIRE_LEVEL_3 5

//GLOBAL VARIABLES
int gQuit=false;
int gState = 0;
int giEnemyFireLevel = ENEMY_FIRE_LEVEL_1;
int gShipLives = 0;
int gSuperShots = 0;
int isSuperShot = false;
int gFlag = false;
int count = 0;

//this function is called each 100ms and send an event to the main...
Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;
    /* In this example, our callback pushes an SDL_USEREVENT event
    * into the queue */
    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    event.type = SDL_USEREVENT;
    event.user = userevent;
    if(!gFlag)
        SDL_PushEvent(&event);
    return(interval);
}

int isEnemyTouched(enemy * evil, bullet * bullet, spaceship * ship)
{


    if( evil->isAlive && ship->isAlive && (bullet->posY <= 40) && ( (bullet->posX >= (evil->posX - 22)) && (bullet->posX <=  (evil->posX + 50)  ) ) )
        return true;
    else
        return false;
}

int amItouched( spaceship *ship, enemy_bullet *bullet)
{

    if( ship->isAlive && (bullet->posY >= SDLS_getScreenHeight() - 150) && ( (bullet->posX >= (ship->posX - 22)) && (bullet->posX <=  (ship->posX + 75)  ) ) )
        return true;
    else
        return false;
}

void wait(int laps)
{
    gFlag = true;
    SDL_Delay(laps);
    gFlag = false;
}

int main(int argc, char** argv)
{
    /* Initialisation simple */

    SDL_Event event;


    // create window with a title
    SDLS_init("Hello World");
    //Fond noir
    SDLS_eraseWithBackgroundColor(0,0,0);

    struct spaceship Vaisseau;
    spaceship_init(&Vaisseau);

    struct bullet bullet;
    init_bullet(&bullet);

    struct enemy evil;
    init_enemy(&evil, 0);

    struct enemy_bullet en_bullet;
    init_enemy_bullet(&en_bullet);

    struct enemy evil2;
    evil2.isAlive = false;

    struct enemy_bullet en_bullet2;
    init_bullet(&en_bullet2);

    struct enemy evil3;
    evil3.isAlive = false;

    struct enemy_bullet en_bullet3;
    init_enemy_bullet(&en_bullet3);


    Uint32 delay = 30; /* To round it down to the nearest 100 ms */
    SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, NULL); //init timer

    while(!gQuit)
    {

        SDL_WaitEvent(&event); // c'est bloquant...

        switch(event.type)
        {

        case SDL_QUIT:
            gQuit = true;
            break;

        case SDL_KEYDOWN:       // sur l'utilisation du clavier on bouge la forme
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                move_spaceship_left(&Vaisseau);
                break;

            case SDLK_d:
                move_spaceship_right(&Vaisseau);
                break;

            case SDLK_b:
                if(Vaisseau.superShot>0)
                {
                    super_fire(&Vaisseau, &bullet);
                    isSuperShot = true;
                    Vaisseau.superShot--;
                    gSuperShots = Vaisseau.superShot;
                }
                break;

            case SDLK_UP:

                break;

            case SDLK_DOWN:

                break;

            case SDLK_RIGHT:

                break;

            case SDLK_LEFT:

                break;

            case SDLK_m:

                break;

            case SDLK_SPACE:
                isSuperShot = false;
                fire(&Vaisseau, &bullet);
                break;

            }


        case SDL_USEREVENT:
            move_enemy(&evil);
            move_enemy(&evil2);
            move_enemy(&evil3);

            switch(gState)
            {

            case 0:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau))
                {
                    gState = 1;
                    destroy_enemy(&evil);
                    gShipLives = Vaisseau.lives;
                    gSuperShots = Vaisseau.superShot;
                }
                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                count++;
                #endif // CHEAT

                break;

            case 1:
                if(youWin(&Vaisseau, &gFlag))
                {
                    gState = 2;
                    init_enemy(&evil, 0);
                    init_enemy_bullet(&en_bullet);
                    en_bullet.speed = 15;
                    load_enemy(&evil, REPUCLIB_ATTACK_CRUISER);
                    giEnemyFireLevel = ENEMY_FIRE_LEVEL_2;
                    spaceship_init(&Vaisseau);
                    Vaisseau.lives = gShipLives;
                    Vaisseau.superShot = gSuperShots;
                    wait(1000);
                }
                break;

            case 2:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau))
                {
                    gState = 3;
                    destroy_enemy(&evil);
                    gShipLives = Vaisseau.lives;
                    gSuperShots = Vaisseau.superShot;
                }
                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                count++;
                #endif // CHEAT
                break;

            case 3:
                if(youWin(&Vaisseau, &gFlag))
                {
                    gState = 4;
                    init_enemy(&evil, 0);
                    init_enemy_bullet(&en_bullet);
                    load_enemy(&evil, SMALL_BLUE_SPACESHIP);
                    giEnemyFireLevel = ENEMY_FIRE_LEVEL_3;
                    spaceship_init(&Vaisseau);
                    Vaisseau.lives = gShipLives;
                    Vaisseau.superShot = gSuperShots;
                    bullet.speed = 20;
                    Vaisseau.speed = 20;
                    wait(1000);
                }
                break;

            case 4:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau))
                {
                    if(isSuperShot)
                    {
                        gState = 7;
                        destroy_enemy(&evil);
                        gShipLives = Vaisseau.lives;
                        gSuperShots = Vaisseau.superShot;
                    }
                    else
                    {
                        gState = 5;
                        count = 0;
                        SDLS_changeColor(evil.texture_spaceship, 200, 200, 200);
                    }

                }

                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                count++;
                #endif // CHEAT
                break;


            case 5:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau) && count >= 20)
                {
                    count = 0;
                    if(isSuperShot)
                    {
                        gState = 7;
                        destroy_enemy(&evil);
                        gShipLives = Vaisseau.lives;
                        gSuperShots = Vaisseau.superShot;
                    }
                    else
                    {
                        gState = 6;
                        SDLS_changeColor(evil.texture_spaceship, 127, 127, 127);
                    }

                }

                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                #endif // CHEAT
                count++;
                break;

            case 6:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau) && count >= 20)
                {
                    count = 0;
                    gState = 7;
                    destroy_enemy(&evil);
                    gShipLives = Vaisseau.lives;
                    gSuperShots = Vaisseau.superShot;
                }
                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                #endif // CHEAT
                count++;
                break;

            case 7:
                if(youWin(&Vaisseau, &gFlag))
                {
                    gState = 8;
                    init_enemy(&evil, 0);
                    init_enemy_bullet(&en_bullet);

                    init_enemy(&evil2, 1);
                    init_enemy_bullet(&en_bullet2);

                    SDLS_changeColor(evil2.texture_spaceship, 180, 180, 180);

                    en_bullet.speed =  5;
                    en_bullet2.speed = 5;

                    giEnemyFireLevel = ENEMY_FIRE_LEVEL_2;
                    spaceship_init(&Vaisseau);
                    Vaisseau.lives = gShipLives;
                    Vaisseau.superShot = gSuperShots;
                    bullet.speed = 20;
                    Vaisseau.speed = 20;
                    wait(1000);
                }
                break;

            case 8:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau) && count >= 20)
                    destroy_enemy(&evil);
                if(isEnemyTouched(&evil2, &bullet, &Vaisseau) && count >= 20)
                    destroy_enemy(&evil2);

                if(!evil.isAlive)
                {
                    evil2.isAlive = false;
                    gShipLives = Vaisseau.lives;
                    gSuperShots = Vaisseau.superShot;
                    gState = 9;
                }

                count++;
                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                count++;
                #endif // CHEAT
                break;

            case 9:
                if(youWin(&Vaisseau, &gFlag))
                {
                    gState = 10;

                    init_enemy(&evil, 0);
                    init_enemy_bullet(&en_bullet);
                    init_enemy_bullet(&en_bullet2);
                    load_enemy(&evil, SMALL_BLUE_SPACESHIP);

                    init_enemy(&evil2, 1);
                    init_enemy_bullet(&en_bullet2);
                    load_enemy(&evil2, SMALL_BLUE_SPACESHIP);

                    init_enemy(&evil3, 2);
                    load_enemy(&evil3, SMALL_BLUE_SPACESHIP);

                    SDLS_changeColor(evil2.texture_spaceship, 150, 150, 150);
                    SDLS_changeColor(evil3.texture_spaceship, 150, 150, 150);

                    giEnemyFireLevel = ENEMY_FIRE_LEVEL_3;
                    spaceship_init(&Vaisseau);
                    Vaisseau.lives = gShipLives;
                    Vaisseau.superShot = gSuperShots;
                    bullet.speed = 20;
                    Vaisseau.speed = 20;
                    wait(1000);
                }
                break;

            case 10:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau) && count >= 20)
                    destroy_enemy(&evil);
                if(isEnemyTouched(&evil2, &bullet, &Vaisseau) && count >= 20)
                    destroy_enemy(&evil2);
                if(isEnemyTouched(&evil3, &bullet, &Vaisseau) && count >= 20)
                    destroy_enemy(&evil3);

                if(!evil.isAlive)
                {
                    evil2.isAlive = false;
                    evil3.isAlive = false;
                    gShipLives = Vaisseau.lives;
                    Vaisseau.superShot = gSuperShots;
                    gState = 11;
                }

                count++;
                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                count++;
                #endif // CHEAT

                break;

            case 11:
                if(youWin(&Vaisseau, &gFlag))
                {
                    gState = 12;

                    init_enemy(&evil, 0);
                    evil.lives = 4;
                    init_enemy_bullet(&en_bullet);
                    init_enemy_bullet(&en_bullet2);
                    load_enemy(&evil, DISCOVERY);

                    /*init_enemy(&evil2, 1);
                    init_enemy_bullet(&en_bullet2);
                    load_enemy(&evil2, DISCOVERY);

                    init_enemy(&evil3, 2);
                    load_enemy(&evil3, DISCOVERY);

                    SDLS_changeColor(evil2.texture_spaceship, 150, 150, 150);
                    SDLS_changeColor(evil3.texture_spaceship, 150, 150, 150);*/

                    giEnemyFireLevel = ENEMY_FIRE_LEVEL_3;
                    spaceship_init(&Vaisseau);
                    Vaisseau.lives = gShipLives;
                    Vaisseau.superShot = gSuperShots;
                    bullet.speed = 20;
                    Vaisseau.speed = 20;
                    wait(1000);
                }

                break;

            case 12:
                if(isEnemyTouched(&evil, &bullet, &Vaisseau) && count >= 20)
                {
                    count = 0;
                    if(isSuperShot)
                        evil.lives -= 2;
                    else
                        evil.lives--;
                    if(evil.lives <= 0)
                    {
                        gState = 13;
                        destroy_enemy(&evil);
                        gShipLives = Vaisseau.lives;
                        gSuperShots = Vaisseau.superShot;
                    }

                }

                #ifndef CHEAT
                if(amItouched(&Vaisseau, &en_bullet) && count >= 20)
                {
                    count = 0;
                    Vaisseau.lives--;
                    if(Vaisseau.lives == 0)
                        destroy_spaceship(&Vaisseau);
                }
                count++;
                #endif // CHEAT

                break;

            case 13:
                if(youWin(&Vaisseau, &gFlag))
                {
                    puts("Congratulations !!!");
                    gQuit = true;
                    SDL_Quit();
                }
                break;


            }


            enemy_fire(&evil, &en_bullet, giEnemyFireLevel);
            enemy_fire(&evil2, &en_bullet2, giEnemyFireLevel);
            enemy_fire(&evil3, &en_bullet3, giEnemyFireLevel);

            finalDisplay(&Vaisseau, &bullet, &evil, &en_bullet, &evil2, &en_bullet2, &evil3, &en_bullet3, &gFlag);

            break;

        }

    }

    SDL_Quit();

    return 0;
}
#endif // JEU
