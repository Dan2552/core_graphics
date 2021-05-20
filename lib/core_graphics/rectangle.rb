module CoreGraphics
  class Rectangle
    def initialize(position, size)
      @position = position
      @size = size
    end

    attr_reader :position
    attr_reader :size
  end
end
