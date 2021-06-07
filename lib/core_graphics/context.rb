module CoreGraphics
  class Context
    def initialize(position, size)
      @display_queue = []
      c__initialize(position.x, position.y, size.width, size.height)
    end

    def draw
      c__orbit
    end
  end
end
