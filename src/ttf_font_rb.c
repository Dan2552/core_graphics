#include "mruby.h"
#include "SDL_ttf.h"
#include "mruby/data.h"
#include "mruby/variable.h"
#include "mruby/array.h"
#include "sdl_world_rb.h"
#include "sdl_texture_rb.h"

typedef struct TTFFontWrap {
  TTF_Font *font;
} TTFFontWrap;

void ttf_font_wrap_dealloc(TTFFontWrap *ttf_font_wrap) {
  if (TTF_WasInit())
    TTF_CloseFont(ttf_font_wrap->font);
  free(ttf_font_wrap);
}

static void ttf_font_rb_free(mrb_state *mrb, void *uncast) {
  TTFFontWrap *ttf_font_wrap = (TTFFontWrap *)uncast;
  ttf_font_wrap_dealloc(ttf_font_wrap);
}

const struct mrb_data_type ttf_font_data_type = {"ttf_font", ttf_font_rb_free};

TTF_Font* ttf_font_rb_unwrap(mrb_state *mrb, mrb_value data) {
  TTFFontWrap *ttf_font_wrap = NULL;

  if (!mrb_nil_p(data)) {
    Data_Get_Struct(mrb, data, &ttf_font_data_type, ttf_font_wrap);
  }

  return ttf_font_wrap->font;
}

mrb_value ttf_font_wrap(mrb_state *mrb, TTF_Font *font) {
  TTFFontWrap *wrap = malloc(sizeof(TTFFontWrap));
  wrap->font = font;

  return mrb_obj_value(Data_Wrap_Struct(
    mrb,
    mrb->object_class,
    &ttf_font_data_type,
    wrap
  ));
}

mrb_value ttf_font_rb_setup_font(mrb_state *mrb, mrb_value self) {
  const char *font_path;
  mrb_int font_size_rb;

  mrb_get_args(
    mrb,
    "zi",
    &font_path,
    &font_size_rb
  );

  int font_size = font_size_rb;

  TTF_Font *font = TTF_OpenFont(font_path, font_size);
  if (font == NULL) {
    printf("%s\n", TTF_GetError());
    mrb_raise(mrb, E_RUNTIME_ERROR, "Font load failure");
  }

  return ttf_font_wrap(mrb, font);
}

mrb_value ttf_font_rb_create_texture(mrb_state *mrb, mrb_value self) {
  mrb_value font_wrap;
  mrb_value world_wrap_rb;
  mrb_value texture_rb;
  const char *text;

  mrb_get_args(
    mrb,
    "oooz",
    &font_wrap,
    &world_wrap_rb,
    &texture_rb,
    &text
  );

  TTF_Font *font = ttf_font_rb_unwrap(mrb, font_wrap);
  SDLWorld *world = sdl_world_rb_unwrap(mrb, world_wrap_rb);

  SDL_Color text_color = { 0, 0, 0 };
  SDL_Surface *surface = TTF_RenderText_Blended(font, text, text_color);

  if (surface == NULL)
    mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to create texture from text");

  SDL_Texture *texture = SDL_CreateTextureFromSurface(world->renderer, surface);

  SDLTextureWrap *texture_wrap = malloc(sizeof(SDLTextureWrap));
  texture_wrap->texture = texture;
  sdl_texture_wrap(mrb, texture_rb, texture_wrap);

  return mrb_nil_value();
}

mrb_value ttf_font_rb_calculate_size(mrb_state *mrb, mrb_value self) {
  mrb_value font_wrap;
  const char *text;
  mrb_int font_size;

  mrb_get_args(
      mrb,
      "ozi",
      &font_wrap,
      &text,
      &font_size
  );

  TTF_Font *font = ttf_font_rb_unwrap(mrb, font_wrap);

  int width;
  int height;

  int error = TTF_SizeText(font, text, &width, &height);
  if (error) {
    printf("%s\n", TTF_GetError());
    mrb_raise(mrb, E_RUNTIME_ERROR, "Error reading font");
  }

  mrb_value values[2];
  values[0] = mrb_fixnum_value(width);
  values[1] = mrb_fixnum_value(height);

  return mrb_ary_new_from_values(mrb, 2, values);
}
