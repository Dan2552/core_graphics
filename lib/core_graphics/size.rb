module CoreGraphics
  class Size
    def initialize(width, height)
      @width = width
      @height = height
    end

    attr_reader :width
    attr_reader :height

    def to_s
      "<Size #{width} #{height}>"
    end

    def inspect
      to_s
    end
  end
end
