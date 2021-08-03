module CoreGraphics
  class Context
    def initialize(position, size)
      @display_queue = []
      c__initialize(position.x, position.y, size.width, size.height)

      @size = size
      @pixel_size = Size.new(@pixel_width, @pixel_height)
      @render_scale = @pixel_width / size.width.to_f
    end

    def draw
      c__orbit
    end

    attr_reader :render_scale
  end
end
