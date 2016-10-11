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

#define GOOD_FIGHTER 0
#define SMALL_YELLOW_SPACESHIP 1
#define VIPER_MARK 2
#define REPUBLIC_WHITE_SHIP 3
#define SMALL_BLUE_SPACESHIP 4
#define SPACESHIP_ALIEN 5
#define REPUCLIB_ATTACK_CRUISER 6

#define ENEMY_FIRE_LEVEL_1 50
#define ENEMY_FIRE_LEVEL_2 30
#define ENEMY_FIRE_LEVEL_3 15

//GLOBAL VARIABLES
    int gQuit=false;
    int gState = 0;
    int giEnemyFireLevel = ENEMY_FIRE_LEVEL_1;

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
    SDL_PushEvent(&event);
    return(interval);
}

int isEnemyTouched(enemy * evil, bullet * bullet){


    if( evil->isAlive && (bullet->posY <= 40) && ( (bullet->posX >= (evil->posX - 22)) && (bullet->posX <=  (evil->posX + 40)  ) ) )
        return true;
    else
        return false;
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

    struct enemy_bullet en_bullet;
    init_enemy_bullet(&en_bullet);

    struct enemy evil;
    init_enemy(&evil);


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

                    switch(gState){

                    case 0:
                        if(isEnemyTouched(&evil, &bullet)){
                            gState = 1;
                            destroy_enemy(&evil);
                        }
                    break;

                    case 1:
                        if(youWin(&Vaisseau)){
                            gState = 2;
                            init_enemy(&evil);
                            load_enemy(&evil, REPUCLIB_ATTACK_CRUISER);
                            giEnemyFireLevel = ENEMY_FIRE_LEVEL_2;
                            spaceship_init(&Vaisseau);
                            SDL_Delay(2000);
                        }
                    break;

                    case 2:
                        if(isEnemyTouched(&evil, &bullet)){
                            gState = 3;
                            destroy_enemy(&evil);
                        }
                        break;

                    case 3:
                        if(youWin(&Vaisseau)){
                            gState = 0;
                            init_enemy(&evil);
                            load_enemy(&evil, REPUBLIC_WHITE_SHIP);
                            giEnemyFireLevel = ENEMY_FIRE_LEVEL_3;
                            spaceship_init(&Vaisseau);
                        }
                        break;


                    }
            enemy_fire(&evil, &en_bullet, giEnemyFireLevel);
            finalDisplay(&Vaisseau, &bullet, &evil, &en_bullet);

            break;

        }

    }

    SDL_Quit();

    return 0;
}
#endif // JEU
