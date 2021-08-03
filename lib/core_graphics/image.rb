module CoreGraphics
  class Image
    def initialize(name, bundle = CorePlatform::Bundle.main)
      image_path = bundle.path_for_resource(name)

      # Load the surface. Note: we don't load covert to a texture at this point
      # because we don't know which context (SDL_Renderer) to create the texture
      # for.
      c__initialize(image_path)
      @size = Size.new(@width, @height)
    end

    attr_reader :size

    # Get (and cache) a drawable layer for the image for the given context.
    #
    def layer_for(context)
      textures[context] ||= begin
        texture = Layer.new(context, Size.new(@size.width, @size.height))
        c__create_texture(context, texture)
        texture
      end
    end

    private

    def textures
      @textures ||= {}
    end
  end
end
