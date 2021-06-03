#ifndef SDL_WORLD_RB_H
#define SDL_WORLD_RB_H

#include "mruby.h"
#include "mruby/value.h"
#include "sdl_world.h"

mrb_value sdl_world_rb_initialize(mrb_state *mrb, mrb_value self);
mrb_value sdl_world_rb_orbit(mrb_state *mrb, mrb_value self);

SDLWorld* sdl_world_rb_unwrap(mrb_state *mrb, mrb_value self);

#endif // SDL_WORLD_RB_H
