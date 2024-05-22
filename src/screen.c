#include "../include/screen.h"
#include <stdbool.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void init_window() {
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Orbits", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_SetWindowResizable(window, SDL_TRUE);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            screen_surface = SDL_GetWindowSurface(window);
            SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            // Hack to get window to stay up
            // TODO: Remove this hack
            SDL_Event e; 
            bool quit = false; 
            while( quit == false ) {
                while( SDL_PollEvent( &e ) ){
                    if( e.type == SDL_QUIT ) quit = true; 
                } 
            }
            SDL_DestroyWindow( window );
        }
        SDL_Quit();
    }
}