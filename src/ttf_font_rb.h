#ifndef TTF_FONT_RB_H
#define TTF_FONT_RB_H

mrb_value ttf_font_rb_setup_font(mrb_state *mrb, mrb_value self);
mrb_value ttf_font_rb_create_texture(mrb_state *mrb, mrb_value self);
mrb_value ttf_font_rb_calculate_size(mrb_state *mrb, mrb_value self);

#endif // TTF_FONT_RB_H
