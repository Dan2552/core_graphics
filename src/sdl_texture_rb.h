#ifndef SDL_TEXTURE_RB_H
#define SDL_TEXTURE_RB_H

#include "mruby.h"
#include "mruby/value.h"

mrb_value sdl_texture_rb_initialize(mrb_state *mrb, mrb_value self);
mrb_value sdl_texture_clear(mrb_state *mrb, mrb_value self);
mrb_value sdl_texture_draw_child_texture(mrb_state *mrb, mrb_value self);
mrb_value sdl_texture_draw(mrb_state *mrb, mrb_value self);

#endif // SDL_TEXTURE_RB_H
