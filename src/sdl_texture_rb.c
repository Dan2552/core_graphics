#include "sdl_texture_rb.h"
#include "sdl_world_rb.h"
#include "SDL.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/variable.h"

void sdl_texture_wrap_dealloc(SDLTextureWrap *texture_wrap) {
  // printf("SDL_DestroyTexture(texture);\n");
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

  // printf("SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, %d, %d);\n", width, height);

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
  mrb_value data = mrb_obj_value(Data_Wrap_Struct(
    mrb,
    mrb->object_class,
    &sdl_texture_data_type,
    texture_wrap
  ));

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@data"), data);
}

mrb_value sdl_texture_clear(mrb_state *mrb, mrb_value self) {
  SDLTextureWrap *texture_wrap = sdl_texture_unwrap(mrb, self);
  SDLWorld *world = texture_wrap->world;
  SDL_Texture *texture = texture_wrap->texture;
  SDL_Renderer *renderer = world->renderer;

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

  // printf("SDL_SetRenderTarget(renderer, texture);\n");
  SDL_SetRenderTarget(renderer, texture);

  // printf("SDL_SetRenderDrawColor(renderer, %d, %d, %d, %d);\n", red, green, blue, alpha);
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);

  // printf("SDL_RenderClear(renderer);\n");
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

  SDL_Rect destination_rect = {
    destination_x,
    destination_y,
    destination_w,
    destination_h
  };

  // printf("SDL_Rect destination_rect = { %d, %d, %d, %d };\n", destination_x, destination_y, destination_w, destination_h);

  // printf("SDL_SetRenderTarget(renderer, texture);\n");
  SDL_SetRenderTarget(renderer, texture);

  // printf("SDL_SetTextureBlendMode(child_texture, SDL_BLENDMODE_BLEND);\n");
  SDL_SetTextureBlendMode(child_texture, SDL_BLENDMODE_BLEND);

  // printf("SDL_RenderCopy(renderer, child_texture, NULL, &destination_rect);\n");
  SDL_RenderCopy(renderer, child_texture, NULL, &destination_rect);

  return mrb_nil_value();
}

mrb_value sdl_texture_draw(mrb_state *mrb, mrb_value self) {
  SDLTextureWrap *texture_wrap = sdl_texture_unwrap(mrb, self);
  SDLWorld *world = texture_wrap->world;
  SDL_Renderer *renderer = world->renderer;
  SDL_Texture *texture = texture_wrap->texture;

  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  SDL_Rect destination_rect = {
    0,
    0,
    width,
    height
  };

  // printf("SDL_SetRenderTarget(renderer, NULL);\n");
  SDL_SetRenderTarget(renderer, NULL);

  // printf("SDL_RenderCopy(renderer, texture, NULL, NULL);\n");
  SDL_RenderCopy(renderer, texture, NULL, &destination_rect);

  return mrb_nil_value();
}
