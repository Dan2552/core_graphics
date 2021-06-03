module CoreGraphics
  class Context
    def initialize(position, size)
      @display_queue = []
      c__initialize(position.x, position.y, size.width, size.height)
    end

    # C code: sdl_world_rb_orbit
    # def c__orbit

    # attr_accessor :delegate
  end
end
