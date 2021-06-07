module CoreGraphics
  class Layer
    def initialize(context, size)
      @context = context
      @size = size
      c__initialize(context, size.width, size.height)
    end

    # TODO: spec
    attr_accessor :delegate
    attr_reader :size

    def draw
      @needs_display = false
      delegate.layer_will_draw(self)
      delegate.draw_layer(self)
    end

    def resize(size)
      delegate.layout_sublayers(self)
      # TODO: inform C
    end

    def set_needs_display
      @needs_display = true
    end

    def needs_display?
      @needs_display == true
    end

    def draw_child_layer(layer, x, y, w, h)
      c__draw_child_texture(layer, x, y, w, h)
    end

    def clear_with_color(red, green, blue, alpha)
      c__clear_with_color(red, green, blue, alpha)
    end
  end
end
