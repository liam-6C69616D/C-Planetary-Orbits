#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* window;
extern SDL_Surface* screen_surface;

void init_window();

#endif