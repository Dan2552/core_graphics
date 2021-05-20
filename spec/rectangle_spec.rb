describe CoreGraphics::Rectangle do
  let(:position) { double(:position, x: 1, y: 2) }
  let(:size) { double(:size, width: 3, height: 4) }
  let(:described_instance) { described_class.new(position, size) }

  describe "#position" do
    subject { described_instance.position }

    it { is_expected.to eq(position) }
  end

  describe "#size" do
    subject { described_instance.size }

    it { is_expected.to eq(size) }
  end
end
