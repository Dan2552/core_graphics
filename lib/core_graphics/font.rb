module CoreGraphics
  class Font
    PATHS = [
      "/System/Library/Fonts",
      "/System/Library/Fonts/Cache",
      "/System/Library/Fonts/Supplemental"
    ].freeze

    TYPES = [
      ".ttc",
      ".ttf",
      ".fon",
      ""
    ]

    def initialize(font_name, font_size, bundle = CorePlatform::Bundle.main)
      @font_path = find_font(font_name, bundle)
      @font_size = font_size
    end

    # Get a drawable layer from the font for the given context.
    #
    def layer_for(context, text)
      font_data = font_for(context)
      width, height = c__calculate_size(font_data, text, @font_size)
      texture = Layer.new(context, Size.new(width, height))
      c__create_texture(font_data, context, texture, text)
      texture
    end

    private

    def find_font(font_name, bundle)
      lookup = PATHS + [bundle.path_for_resource(nil)]

      lookup.each do |path|
        TYPES.each do |type|
          potential = File.join(path, "#{font_name}#{type}")
          return potential if File.file?(potential)
        end
      end

      raise "Font \"#{font_name}\" not found. Searched in #{lookup}"
    end

    def font_for(context)
      @context_fonts ||= {}
      @context_fonts[context] ||= c__setup_font(
        @font_path,
        @font_size * context.render_scale
      )
    end
  end
end
