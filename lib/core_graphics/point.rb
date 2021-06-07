module CoreGraphics
  class Point
    def initialize(x, y)
      @x = x
      @y = y
    end

    attr_reader :x
    attr_reader :y

    def to_s
      "<Point #{x} #{y}>"
    end

    def inspect
      to_s
    end
  end
end
