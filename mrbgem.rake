MRuby::Gem::Specification.new("mruby-core_graphics") do |spec|
  spec.license = "MIT"
  spec.authors = "Daniel Inkpen"
  spec.rbfiles = Dir.glob(File.join(__dir__, "lib", "core_graphics", "**", "*.rb")).sort

  # TODO: figure out this, especially to be different per platform?
  sdl_install = "/Users/dan2552/.avian/build/desktop/install"

  spec.cc.flags << "-I#{sdl_install}/include/SDL2"
  spec.linker.flags << "-L#{sdl_install}/lib -lSDL2"
end
