module CoreGraphics
  class Context
    def c__initialize(x, y, w, h)
      @pixel_width = w * 2
      @pixel_height = h * 2
    end
    def c__orbit
    end
  end
end

describe CoreGraphics::Context do
  let(:position) { double(:position, x: 1, y: 2) }
  let(:size) { double(:size, width: 1, height: 2) }
  let(:described_instance) { described_class.new(position, size) }

  describe "#draw" do
    subject { described_instance.draw }

    it "calls c__orbit" do
      expect(described_instance)
        .to receive(:c__orbit)

      subject
    end
  end

  describe "#render_scale" do
    subject { described_instance.render_scale }

    it "has a scale determined from the @pixel_width (set by c__initialize)" do
      expect(subject).to eq(2.0)
    end
  end
end
