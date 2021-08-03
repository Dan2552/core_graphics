#ifndef SDL_TEXTURE_RB_H
#define SDL_TEXTURE_RB_H

#include "mruby.h"
#include "mruby/value.h"
#include "sdl_world.h"

typedef struct SDLTextureWrap {
  SDL_Texture *texture;
  SDLWorld *world;
} SDLTextureWrap;

SDLTextureWrap* sdl_texture_unwrap(mrb_state *mrb, mrb_value self);
void sdl_texture_wrap(mrb_state *mrb, mrb_value instance, SDLTextureWrap *texture_wrap);

mrb_value sdl_texture_rb_initialize(mrb_state *mrb, mrb_value self);
mrb_value sdl_texture_clear(mrb_state *mrb, mrb_value self);
mrb_value sdl_texture_draw_child_texture(mrb_state *mrb, mrb_value self);
mrb_value sdl_texture_draw(mrb_state *mrb, mrb_value self);

#endif // SDL_TEXTURE_RB_H
