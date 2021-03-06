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
//#define SPACESHIP


#ifdef SPACESHIP
#define GOOD_FIGHTER 0
#define SMALL_YELLOW_SPACESHIP 1
#define VIPER_MARK 2
#define REPUBLIC_WHITE_SHIP 3
#define SMALL_BLUE_SPACESHIP 4

//GLOBAL VARIABLES
    int gQuit=false;

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
                load_spaceship(&Vaisseau, REPUBLIC_WHITE_SHIP);
                break;

            case SDLK_DOWN:
                load_spaceship(&Vaisseau, SMALL_YELLOW_SPACESHIP);
                break;

            case SDLK_RIGHT:
                load_spaceship(&Vaisseau, SMALL_BLUE_SPACESHIP);
                break;

            case SDLK_LEFT:
                load_spaceship(&Vaisseau, GOOD_FIGHTER);
                break;

            case SDLK_m:
                destroy_spaceship(&Vaisseau);
                break;

            case SDLK_SPACE:
                fire(&Vaisseau, &bullet);
                break;

            }

        case SDL_USEREVENT:
            finalDisplay(&Vaisseau, &bullet);
            break;

        }

    }

    SDL_Quit();

    return 0;
}
#endif // SPACESHIP
