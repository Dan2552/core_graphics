describe CoreGraphics::Size do
  let(:width) { 64 }
  let(:height) { 32 }
  let(:described_instance) { described_class.new(width, height) }

  describe "#width" do
    subject { described_instance.width }

    it { is_expected.to eq(width) }
  end

  describe "#height" do
    subject { described_instance.height }

    it { is_expected.to eq(height) }
  end
end
