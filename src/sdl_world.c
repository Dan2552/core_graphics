#include "sdl_world.h"
#include "SDL.h"

static int SDL_INITIALIZE_FIRST_THING_THAT_WORKS = -1;

SDLWorld* sdl_world_alloc(int x, int y, int w, int h) {
  SDLWorld *world = NULL;
  world = malloc(sizeof(SDLWorld));

  if (!world) {
    world->status = -4;
    return world;
  }

  world->window = SDL_CreateWindow(NULL, x, y, w, h, SDL_WINDOW_ALLOW_HIGHDPI);
  if (world->window == NULL) {
    world->status = -2;
    return world;
  }

  world->renderer = SDL_CreateRenderer(
    world->window,
    SDL_INITIALIZE_FIRST_THING_THAT_WORKS,
    SDL_RENDERER_PRESENTVSYNC
  );

  if (!world->renderer) {
    world->status = -3;
    return world;
  }

  SDL_SetRenderDrawColor(world->renderer, 0, 0, 0, 255);
  SDL_RenderClear(world->renderer);
  SDL_RenderPresent(world->renderer);

  SDL_GetRendererOutputSize(
    world->renderer,
    &world->render_screen_width,
    &world->render_screen_height
  );

  world->status = 1;

  return world;
}

void sdl_world_orbit(SDLWorld *world) {
  SDL_RenderPresent(world->renderer);
}

void sdl_world_dealloc(SDLWorld *world) {
  SDL_DestroyRenderer(world->renderer);
  SDL_DestroyWindow(world->window);
  free(world);
}
