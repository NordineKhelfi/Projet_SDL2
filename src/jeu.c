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

#define ENEMY_FIRE_LEVEL_1 50
#define ENEMY_FIRE_LEVEL_2 30
#define ENEMY_FIRE_LEVEL_3 5

//GLOBAL VARIABLES
    int gQuit=false;
    int gState = 0;
    int giEnemyFireLevel = ENEMY_FIRE_LEVEL_1;
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

int isEnemyTouched(enemy * evil, bullet * bullet, spaceship * ship){


    if( evil->isAlive && ship->isAlive && (bullet->posY <= 40) && ( (bullet->posX >= (evil->posX - 22)) && (bullet->posX <=  (evil->posX + 40)  ) ) )
        return true;
    else
        return false;
}

int amItouched( spaceship *ship, enemy_bullet *bullet) {

    if( ship->isAlive && (bullet->posY >= SDLS_getScreenHeight() - 150) && ( (bullet->posX >= (ship->posX - 22)) && (bullet->posX <=  (ship->posX + 75)  ) ) )
        return true;
    else
        return false;
}

void wait(int laps){
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


    Uint32 delay = 30; /* To round it down to the nearest 100 ms */
    SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, NULL); //init timer

    while(!gQuit){

        SDL_WaitEvent(&event); // c'est bloquant...

        switch(event.type){

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
                fire(&Vaisseau, &bullet);
                break;

            }


        case SDL_USEREVENT:
            move_enemy(&evil);
            move_enemy(&evil2);

                    switch(gState){

                    case 0:
                        if(isEnemyTouched(&evil, &bullet, &Vaisseau)){
                            gState = 1;
                            destroy_enemy(&evil);
                        }
                        #ifndef CHEAT
                        if(amItouched(&Vaisseau, &en_bullet))
                            destroy_spaceship(&Vaisseau);
                        #endif // CHEAT

                        break;

                    case 1:
                        if(youWin(&Vaisseau, &gFlag)){
                            gState = 2;
                            init_enemy(&evil, 0);
                            init_enemy_bullet(&en_bullet);
                            en_bullet.speed = 15;
                            load_enemy(&evil, REPUCLIB_ATTACK_CRUISER);
                            giEnemyFireLevel = ENEMY_FIRE_LEVEL_2;
                            spaceship_init(&Vaisseau);
                            wait(1000);
                        }
                        break;

                    case 2:
                        if(isEnemyTouched(&evil, &bullet, &Vaisseau)){
                            gState = 3;
                            destroy_enemy(&evil);
                        }
                        #ifndef CHEAT
                        if(amItouched(&Vaisseau, &en_bullet))
                            destroy_spaceship(&Vaisseau);
                        #endif // CHEAT
                        break;

                    case 3:
                        if(youWin(&Vaisseau, &gFlag)){
                            gState = 4;
                            init_enemy(&evil, 0);
                            init_enemy_bullet(&en_bullet);
                            load_enemy(&evil, SMALL_BLUE_SPACESHIP);
                            giEnemyFireLevel = ENEMY_FIRE_LEVEL_3;
                            spaceship_init(&Vaisseau);
                            bullet.speed = 20;
                            Vaisseau.speed = 20;
                            wait(1000);
                        }
                        break;

                    case 4:
                        if(isEnemyTouched(&evil, &bullet, &Vaisseau)){
                            gState = 5;
                            SDLS_changeColor(evil.texture_spaceship, 200, 200, 200);
                        }

                        #ifndef CHEAT
                        if(amItouched(&Vaisseau, &en_bullet))
                            destroy_spaceship(&Vaisseau);
                        #endif // CHEAT
                        break;


                    case 5:
                        if(isEnemyTouched(&evil, &bullet, &Vaisseau) && count >= 20){
                            gState = 6;
                            SDLS_changeColor(evil.texture_spaceship, 127, 127, 127);
                            count = 0;
                        }
                        count++;
                        #ifndef CHEAT
                        if(amItouched(&Vaisseau, &en_bullet))
                            destroy_spaceship(&Vaisseau);
                        #endif // CHEAT
                        break;

                    case 6:
                        if(isEnemyTouched(&evil, &bullet, &Vaisseau) && count >= 20){
                            gState = 7;
                            destroy_enemy(&evil);
                        }
                        count++;
                        #ifndef CHEAT
                        if(amItouched(&Vaisseau, &en_bullet))
                            destroy_spaceship(&Vaisseau);
                        #endif // CHEAT
                        break;

                    case 7:
                        if(youWin(&Vaisseau, &gFlag)){
                            gState = 8;
                            init_enemy(&evil, 0);
                            init_enemy_bullet(&en_bullet);

                            init_enemy(&evil2, 1);
                            init_enemy_bullet(&en_bullet2);

                            en_bullet.speed = 15;
                            en_bullet2.speed = 15;

                            giEnemyFireLevel = ENEMY_FIRE_LEVEL_2;
                            spaceship_init(&Vaisseau);
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

                        if(!evil.isAlive){
                            evil2.isAlive = false;
                            gState = 9;
                        }

                        count++;
                        #ifndef CHEAT
                        if(amItouched(&Vaisseau, &en_bullet))
                            destroy_spaceship(&Vaisseau);
                        #endif // CHEAT
                        break;

                    case 9:
                        if(youWin(&Vaisseau, &gFlag)){
                            gState = 10;
                            init_enemy(&evil, 0);
                            init_enemy_bullet(&en_bullet);
                            load_enemy(&evil, SMALL_BLUE_SPACESHIP);
                            giEnemyFireLevel = ENEMY_FIRE_LEVEL_3;
                            spaceship_init(&Vaisseau);
                            bullet.speed = 20;
                            Vaisseau.speed = 20;
                            wait(1000);
                        }
                        break;



                    }
            enemy_fire(&evil, &en_bullet, giEnemyFireLevel);
            finalDisplay(&Vaisseau, &bullet, &evil, &en_bullet, &evil2, &en_bullet2, &gFlag);

            break;

        }

    }

    SDL_Quit();

    return 0;
}
#endif // JEU
