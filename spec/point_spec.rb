describe CoreGraphics::Point do
  let(:x) { 12 }
  let(:y) { 4 }
  let(:described_instance) { described_class.new(x, y) }

  describe "#x" do
    subject { described_instance.x }

    it { is_expected.to eq(x) }
  end

  describe "#y" do
    subject { described_instance.y }

    it { is_expected.to eq(y) }
  end
end
