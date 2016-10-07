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


int gQuit=false;
//Pour la vitesse de déplacement
int dX = 10;

int main(int argc, char** argv)
{
    /* Initialisation simple */

    SDL_Event event;

    // create window with a title
    SDLS_init("Hello World");
    //Fond noir
    SDLS_eraseWithBackgroundColor(0,0,0);

    struct spaceship Vaisseau;
    //Initialisation du vaisseau
    spaceship_init(&Vaisseau);
    //Affichage du vaisseau
    display_spaceship(&Vaisseau);

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
                //Déplacement vers la gauche
                move_spaceship(&Vaisseau, -dX);
                break;

            case SDLK_RIGHT:
                //Déplacement vers la droite
                move_spaceship(&Vaisseau, dX);
                break;

            case SDLK_UP:

                break;

            case SDLK_DOWN:


                break;
            }

        }

    }

    SDL_Quit();

    return 0;
}
