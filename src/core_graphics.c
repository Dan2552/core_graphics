#include "sdl_world_rb.h"
#include "sdl_texture_rb.h"
#include "mruby.h"
#include "mruby/class.h"
#include "SDL.h"

void mrb_mruby_core_graphics_gem_init(mrb_state *mrb) {
  struct RClass *render_module = mrb_define_module(mrb, "CoreGraphics");
  struct RClass *sdl_world = mrb_define_class_under(mrb, render_module, "Context", mrb->object_class);
  mrb_define_method(mrb, sdl_world, "c__initialize", sdl_world_rb_initialize, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, sdl_world, "c__orbit", sdl_world_rb_orbit, MRB_ARGS_NONE());

  struct RClass *sdl_texture = mrb_define_class_under(mrb, render_module, "Layer", mrb->object_class);
  mrb_define_method(mrb, sdl_texture, "c__initialize", sdl_texture_rb_initialize, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, sdl_texture, "c__clear_with_color", sdl_texture_clear, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, sdl_texture, "c__draw_child_texture", sdl_texture_draw_child_texture, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, sdl_texture, "c__draw", sdl_texture_draw, MRB_ARGS_NONE());

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    mrb_raise(mrb, E_RUNTIME_ERROR, "SDL_Init failed");
}

void mrb_mruby_core_graphics_gem_final(mrb_state *mrb) {
  SDL_Quit();
}
