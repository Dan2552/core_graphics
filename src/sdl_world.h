#ifndef SDL_WORLD_H
#define SDL_WORLD_H

#include "SDL.h"

typedef struct SDLWorld {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int render_screen_width;
  int render_screen_height;
  int status;
} SDLWorld;

SDLWorld* sdl_world_alloc(int x, int y, int w, int h);
void sdl_world_orbit(SDLWorld *world);
void sdl_world_dealloc(SDLWorld *world);

#endif // SDL_WORLD_H
