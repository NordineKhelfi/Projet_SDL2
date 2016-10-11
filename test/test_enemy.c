#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\biblio\SDLS.h"
#include <enemy.h>
#include <spaceship.h>
//#define ENEMY

#ifdef ENEMY
//GLOBAL VARIABLES
int gXenemy = 0;
int gQuit=false;
int gEnemySpeed = 5;


int main(int argc, char** argv)
{
    /* Initialisation simple */

    SDL_Event event;

    // create window with a title
    SDLS_init("Hello World");
    //Fond noir
    SDLS_eraseWithBackgroundColor(0,0,0);
    SDLS_displayAll();

    struct enemy Enemy;

    init_enemy(&Enemy, gXenemy, gEnemySpeed);

    /*struct spaceship Moi;

    spaceship_init(&Moi);
    display_spaceship(&Moi);*/



    while(!gQuit){

        SDL_WaitEvent(&event); // c'est bloquant...

        switch(event.type){

        case SDL_QUIT:
            gQuit = true;
            break;

        case SDL_KEYDOWN:       // sur l'utilisation du clavier on bouge la forme
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                //move_spaceship(&Moi, -10);
                break;

            case SDLK_RIGHT:
                //move_spaceship(&Moi, 10);
                break;

            case SDLK_UP:

                break;

            case SDLK_DOWN:


                break;

            case SDLK_m:

                break;
            }

        }

    }

    SDL_Quit();

    return 0;
}

#endif // ENEMY

