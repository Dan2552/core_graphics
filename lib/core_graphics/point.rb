module CoreGraphics
  class Point
    def initialize(x, y)
      @x = x
      @y = y
    end

    attr_reader :x
    attr_reader :y
  end
end
