module CoreGraphics
  class Rectangle
    def initialize(position, size)
      @position = position
      @size = size
    end

    attr_reader :position
    attr_reader :size

    def to_s
      "<Rectangle #{position} #{size}>"
    end

    def inspect
      to_s
    end
  end
end
