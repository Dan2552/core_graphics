#include "mruby.h"
#include "SDL_image.h"
#include "sdl_texture_rb.h"
#include "sdl_world_rb.h"
#include "mruby/data.h"
#include "mruby/variable.h"

typedef struct SDLSurfaceWrap {
  SDL_Surface *surface;
} SDLSurfaceWrap;

void sdl_surface_wrap_dealloc(SDLSurfaceWrap *surface_wrap) {
  SDL_FreeSurface(surface_wrap->surface);
  free(surface_wrap);
}

static void sdl_surface_rb_free(mrb_state *mrb, void *uncast) {
  SDLSurfaceWrap *surface_wrap = (SDLSurfaceWrap *)uncast;
  sdl_surface_wrap_dealloc(surface_wrap);
}

const struct mrb_data_type sdl_surface_data_type = {"sdl_surface", sdl_surface_rb_free};

SDLSurfaceWrap* sdl_surface_rb_unwrap(mrb_state *mrb, mrb_value self) {
  SDLSurfaceWrap *surface_wrap = NULL;

  mrb_value data = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@surface"));

  if (!mrb_nil_p(data)) {
    Data_Get_Struct(mrb, data, &sdl_surface_data_type, surface_wrap);
  }

  return surface_wrap;
}

void sdl_surface_wrap(mrb_state *mrb, mrb_value self, SDLSurfaceWrap *surface_wrap) {
  mrb_value data = mrb_obj_value(Data_Wrap_Struct(
    mrb,
    mrb->object_class,
    &sdl_surface_data_type,
    surface_wrap
  ));

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@surface"), data);
}

mrb_value sdl_image_rb_initialize(mrb_state *mrb, mrb_value self) {
  const char *image_name;
  mrb_get_args(mrb, "z", &image_name);

  SDL_Surface *surface = IMG_Load(image_name);

  if (surface == NULL)
    mrb_raise(mrb, E_RUNTIME_ERROR, "image load failure");

  // TODO:
  // return mrb_raise(mrb, E_RUNTIME_ERROR, "image load failure (" + image_name + "):" + IMG_GetError());

  SDLSurfaceWrap *surface_wrap = malloc(sizeof(SDLSurfaceWrap));
  surface_wrap->surface = surface;

  sdl_surface_wrap(mrb, self, surface_wrap);

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@width"), mrb_float_value(mrb, surface->w));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@height"), mrb_float_value(mrb, surface->h));

  return mrb_nil_value();
}

mrb_value sdl_image_rb_create_texture(mrb_state *mrb, mrb_value self) {
  mrb_value world_wrap_rb;
  mrb_value texture_rb;
  mrb_get_args(mrb, "oo", &world_wrap_rb, &texture_rb);

  SDLWorld *world = sdl_world_rb_unwrap(mrb, world_wrap_rb);
  SDLSurfaceWrap *surface_wrap = sdl_surface_rb_unwrap(mrb, self);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(world->renderer, surface_wrap->surface);

  if (texture == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "image texture creation failure"); // TODO: use SDL_GetError()
  }

  SDLTextureWrap *texture_wrap = malloc(sizeof(SDLTextureWrap));
  texture_wrap->texture = texture;
  sdl_texture_wrap(mrb, texture_rb, texture_wrap);

  return mrb_nil_value();
}
