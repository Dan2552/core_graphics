#include "sdl_texture_rb.h"
#include "sdl_world_rb.h"
#include "SDL.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/variable.h"

// TODO: could I just be saving a pointer in an instance var?
// https://github.com/katzer/mruby-r3/commit/185455010e82fdc491ded1c705b2c0521bb266ba

typedef struct SDLTextureWrap {
  SDL_Texture *texture;
  SDLWorld *world;
} SDLTextureWrap;

SDLTextureWrap* sdl_texture_unwrap(mrb_state *mrb, mrb_value self);
void sdl_texture_wrap(mrb_state *mrb, mrb_value instance, SDLTextureWrap *texture_wrap);

void sdl_texture_wrap_dealloc(SDLTextureWrap *texture_wrap) {
  SDL_DestroyTexture(texture_wrap->texture);
  free(texture_wrap);
}

static void sdl_texture_rb_free(mrb_state *mrb, void *uncast) {
  SDLTextureWrap *texture_wrap = (SDLTextureWrap *)uncast;
  sdl_texture_wrap_dealloc(texture_wrap);
}

const struct mrb_data_type sdl_texture_data_type = {"sdl_texture", sdl_texture_rb_free};

mrb_value sdl_texture_rb_initialize(mrb_state *mrb, mrb_value self) {
  mrb_value world_wrap;
  mrb_int w;
  mrb_int h;
  mrb_get_args(mrb, "oii", &world_wrap, &w, &h);

  SDLWorld *world = sdl_world_rb_unwrap(mrb, world_wrap);

  int width = w;
  int height = h;

  SDL_Texture *texture = SDL_CreateTexture(
    world->renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    width,
    height
  );

  SDLTextureWrap *texture_wrap = malloc(sizeof(SDLTextureWrap));
  texture_wrap->texture = texture;
  texture_wrap->world = world;

  sdl_texture_wrap(mrb, self, texture_wrap);

  return mrb_nil_value();
}

SDLTextureWrap* sdl_texture_unwrap(mrb_state *mrb, mrb_value self) {
  SDLTextureWrap *texture_wrap = NULL;
  mrb_sym instance_var_name = mrb_intern_lit(mrb, "@data");
  mrb_value data = mrb_iv_get(mrb, self, instance_var_name);

  if (!mrb_nil_p(data)) {
    Data_Get_Struct(mrb, data, &sdl_texture_data_type, texture_wrap);
  }

  return texture_wrap;
}

void sdl_texture_wrap(mrb_state *mrb, mrb_value self, SDLTextureWrap *texture_wrap) {
  SDLTextureWrap *existing = sdl_texture_unwrap(mrb, self);
  if (existing != NULL)
    sdl_texture_wrap_dealloc(existing);

  mrb_sym instance_var_name;
  mrb_value data;
  instance_var_name = mrb_intern_lit(mrb, "@data");
  data = mrb_obj_value(Data_Wrap_Struct(
    mrb,
    mrb->object_class,
    &sdl_texture_data_type,
    texture_wrap
  ));
  mrb_iv_set(mrb, self, instance_var_name, data);
}

mrb_value sdl_texture_clear(mrb_state *mrb, mrb_value self) {
  SDLTextureWrap *texture_wrap = sdl_texture_unwrap(mrb, self);
  SDLWorld *world = texture_wrap->world;
  SDL_Texture *texture = texture_wrap->texture;
  SDL_Renderer *renderer = world->renderer;

  SDL_SetRenderTarget(renderer, texture);

  mrb_int red_rb;
  mrb_int green_rb;
  mrb_int blue_rb;
  mrb_int alpha_rb;

  mrb_get_args(
    mrb,
    "iiii",
    &red_rb,
    &green_rb,
    &blue_rb,
    &alpha_rb
  );

  int red = red_rb;
  int green = green_rb;
  int blue = blue_rb;
  int alpha = alpha_rb;

  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
  SDL_RenderClear(renderer);

  return mrb_nil_value();
}

mrb_value sdl_texture_draw_child_texture(mrb_state *mrb, mrb_value self) {
  mrb_value child_texture_self;
  mrb_int destination_x;
  mrb_int destination_y;
  mrb_int destination_w;
  mrb_int destination_h;

  mrb_get_args(
    mrb,
    "oiiii",
    &child_texture_self,
    &destination_x,
    &destination_y,
    &destination_w,
    &destination_h
  );

  SDLTextureWrap *texture_wrap = sdl_texture_unwrap(mrb, self);
  SDLTextureWrap *child_texture_wrap = sdl_texture_unwrap(mrb, child_texture_self);

  SDLWorld *world = texture_wrap->world;
  SDL_Renderer *renderer = world->renderer;

  SDL_Texture *texture = texture_wrap->texture;
  SDL_Texture *child_texture = child_texture_wrap->texture;

  SDL_Rect rect_of_shadow_image = {
    destination_x,
    destination_y,
    destination_w,
    destination_h
  };

  SDL_SetRenderTarget(renderer, texture);
  SDL_RenderCopy(renderer, child_texture, NULL, &rect_of_shadow_image);

  return mrb_nil_value();
}
