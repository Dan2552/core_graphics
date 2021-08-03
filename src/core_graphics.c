#include "sdl_world_rb.h"
#include "sdl_texture_rb.h"
#include "sdl_image_rb.h"
#include "ttf_font_rb.h"
#include "mruby.h"
#include "mruby/class.h"
#include "SDL.h"
#include "SDL_ttf.h"

void mrb_mruby_core_graphics_gem_init(mrb_state *mrb) {
  struct RClass *core_graphics_module = mrb_define_module(mrb, "CoreGraphics");
  struct RClass *sdl_world = mrb_define_class_under(mrb, core_graphics_module, "Context", mrb->object_class);
  mrb_define_method(mrb, sdl_world, "c__initialize", sdl_world_rb_initialize, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, sdl_world, "c__orbit", sdl_world_rb_orbit, MRB_ARGS_NONE());

  struct RClass *sdl_texture = mrb_define_class_under(mrb, core_graphics_module, "Layer", mrb->object_class);
  mrb_define_method(mrb, sdl_texture, "c__initialize", sdl_texture_rb_initialize, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, sdl_texture, "c__clear_with_color", sdl_texture_clear, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, sdl_texture, "c__draw_child_texture", sdl_texture_draw_child_texture, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, sdl_texture, "c__draw", sdl_texture_draw, MRB_ARGS_NONE());

  struct RClass *sdl_image = mrb_define_class_under(mrb, core_graphics_module, "Image", mrb->object_class);
  mrb_define_method(mrb, sdl_image, "c__initialize", sdl_image_rb_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, sdl_image, "c__create_texture", sdl_image_rb_create_texture, MRB_ARGS_REQ(2));

  struct RClass *ttf_font = mrb_define_class_under(mrb, core_graphics_module, "Font", mrb->object_class);
  mrb_define_method(mrb, ttf_font, "c__setup_font", ttf_font_rb_setup_font, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ttf_font, "c__create_texture", ttf_font_rb_create_texture, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, ttf_font, "c__calculate_size", ttf_font_rb_calculate_size, MRB_ARGS_REQ(3));

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    mrb_raise(mrb, E_RUNTIME_ERROR, "SDL_Init failed");

  TTF_Init();
}

void mrb_mruby_core_graphics_gem_final(mrb_state *mrb) {
  TTF_Quit();
  SDL_Quit();
}
