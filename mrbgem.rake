MRuby::Gem::Specification.new("mruby-core_graphics") do |spec|
  spec.license = "MIT"
  spec.authors = "Daniel Inkpen"
  spec.rbfiles = Dir.glob(File.join(__dir__, "lib", "core_graphics", "**", "*.rb")).sort

  # conf.cc do |cc|
  #   cc.flags << "-I/_path_/_to_/_SDL_/include/SDL2"
  # end
  #
  # conf.linker do |linker|
  #   linker.flags << "-L/_path_/_to_/_SDL_/lib -lSDL2 -lSDL2_image -lSDL2_ttf"
  # end
  spec.requirements = "SDL in compiler and linker flags"

  spec.add_dependency("mruby-core_platform", path: File.join(__dir__, "../core_platform"))
end
