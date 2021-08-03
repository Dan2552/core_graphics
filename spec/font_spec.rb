describe CoreGraphics::Font do
  let(:font_name) { "Arial" }
  let(:font_size) { 18 }
  let(:bundle) { double(:bundle, path_for_resource: "/tmp") }

  let(:described_instance) { described_class.new(font_name, font_size, bundle) }

  describe "#layer_for" do
    let(:context) { double(:graphics_context, render_scale: 2.0) }
    let(:text) { "hello world" }
    subject { described_instance.layer_for(context, text) }

    it "uses c__setup_font to generate a font" do
      expect(described_instance)
        .to receive(:c__setup_font)
        .with(
          "/System/Library/Fonts/Supplemental/Arial.ttf",
          font_size * context.render_scale
        )

      subject rescue nil
    end

    it "builds a layer to create the texture onto" do
      font = double(:font)

      expect(described_instance)
        .to receive(:c__calculate_size)
        .with(font, text, font_size)
        .and_return([100, 50])

      layer = double(:layer)

      expect(CoreGraphics::Layer)
        .to receive(:new)
        .and_return(layer)

      expect(described_instance)
        .to receive(:c__setup_font)
        .and_return(font)

      expect(described_instance)
        .to receive(:c__create_texture)
        .with(font, context, layer, text)

      subject
    end
  end
end
