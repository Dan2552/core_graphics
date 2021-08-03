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

  world->window = SDL_CreateWindow("[title]", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);
  if (world->window == NULL) {
    world->status = -2;
    return world;
  }

  world->renderer = SDL_CreateRenderer(
    world->window,
    SDL_INITIALIZE_FIRST_THING_THAT_WORKS,
    0
  );

  if (!world->renderer) {
    world->status = -3;
    return world;
  }

  // printf("SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);\n");
  SDL_SetRenderDrawColor(world->renderer, 0, 0, 0, 255);
  // printf("SDL_RenderClear(renderer);\n");
  SDL_RenderClear(world->renderer);
  // printf("SDL_RenderPresent(renderer);\n");
  SDL_RenderPresent(world->renderer);

  SDL_GetWindowSize(
    world->window,
    &world->render_screen_width,
    &world->render_screen_height
  );

  SDL_GetRendererOutputSize(
    world->renderer,
    &world->pixel_screen_width,
    &world->pixel_screen_height
  );

  world->status = 1;

  return world;
}

void sdl_world_orbit(SDLWorld *world) {
  // printf("SDL_RenderPresent(renderer);\n");
  SDL_RenderPresent(world->renderer);
}

void sdl_world_dealloc(SDLWorld *world) {
  // printf("SDL_DestroyRenderer(renderer);\n");
  SDL_DestroyRenderer(world->renderer);
  // printf("SDL_DestroyWindow(renderer);\n");
  SDL_DestroyWindow(world->window);
  free(world);
}
