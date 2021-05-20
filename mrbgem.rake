MRuby::Gem::Specification.new("mruby-core_graphics") do |spec|
  spec.license = "MIT"
  spec.authors = "Daniel Inkpen"
  spec.rbfiles = Dir.glob(File.join(__dir__, "lib", "core_graphics", "**", "*.rb"))
end
