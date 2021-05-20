module CoreGraphics
  class Size
    def initialize(width, height)
      @width = width
      @height = height
    end

    attr_reader :width
    attr_reader :height
  end
end
