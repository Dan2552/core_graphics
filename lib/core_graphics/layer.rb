module CoreGraphics
  class Layer
    def initialize(context, size)
      @context = context
      @size = size
      c__initialize(context, size.width, size.height)
    end

    attr_reader :size

    def draw
      delegate.layer_will_draw(self)
      delegate.draw_layer(self)
    end

    def resize(size)
      delegate.layout_sublayers(self)
      # TODO: inform C
    end

    def set_needs_display

    end

    # C code: sdl_texture_rb_initialize
    # def initialize(world, w, h)
  end
end
