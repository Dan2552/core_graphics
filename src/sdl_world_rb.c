#include "sdl_world_rb.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/variable.h"

void sdl_world_rb_wrap(mrb_state *mrb, mrb_value instance, SDLWorld *world);

static void sdl_world_rb_free(mrb_state *mrb, void *world_uncast) {
  SDLWorld *world = (SDLWorld *)world_uncast;
  sdl_world_dealloc(world);
}

const struct mrb_data_type sdl_world_data_type = {"sdl_world", sdl_world_rb_free};

mrb_value sdl_world_rb_initialize(mrb_state *mrb, mrb_value self) {
  mrb_int x;
  mrb_int y;
  mrb_int w;
  mrb_int h;
  mrb_get_args(mrb, "iiii", &x, &y, &w, &h);

  SDLWorld *world = sdl_world_alloc(x, y, w, h);

  if (world->status == -2)
    mrb_raise(mrb, E_RUNTIME_ERROR, "SDL_CreateWindow failed");
  if (world->status == -3)
    mrb_raise(mrb, E_RUNTIME_ERROR, "SDL_CreateRenderer failed");
  if (world->status == -4)
    mrb_raise(mrb, E_RUNTIME_ERROR, "Could not allocate SDLWorld");

  sdl_world_rb_wrap(mrb, self, world);

  return mrb_nil_value();
}

mrb_value sdl_world_rb_orbit(mrb_state *mrb, mrb_value self) {
  sdl_world_orbit(sdl_world_rb_unwrap(mrb, self));
  return mrb_nil_value();
}

SDLWorld* sdl_world_rb_unwrap(mrb_state *mrb, mrb_value self) {
  SDLWorld *world = NULL;
  mrb_sym instance_var_name = mrb_intern_lit(mrb, "@data");
  mrb_value data = mrb_iv_get(mrb, self, instance_var_name);

  if (!mrb_nil_p(data)) {
    Data_Get_Struct(mrb, data, &sdl_world_data_type, world);
  }

  return world;
}

void sdl_world_rb_wrap(mrb_state *mrb, mrb_value self, SDLWorld *world) {
  SDLWorld *existing = sdl_world_rb_unwrap(mrb, self);
  if (existing != NULL)
    sdl_world_dealloc(existing);

  mrb_sym instance_var_name;
  mrb_value data;
  instance_var_name = mrb_intern_lit(mrb, "@data");
  data = mrb_obj_value(Data_Wrap_Struct(
    mrb,
    mrb->object_class,
    &sdl_world_data_type,
    world
  ));
  mrb_iv_set(mrb, self, instance_var_name, data);
}
