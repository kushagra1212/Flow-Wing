class Flowwing < Formula
  desc "Sculpting logic with the elegance of flow."
  homepage "https://github.com/kushagra1212/Flow-Wing"
  url "https://github.com/kushagra1212/Flow-Wing/releases/download/v0.0.1-alpha.1/FlowWing-0.0.1-alpha-m1.tar.gz"
  sha256 "4f2197dbb491875ef145dbba102e6b3a8c2dd5718179bce873ac8154fd241551"
  license "FlowWing Contribution License v1.0"

  def install
    bin.install "bin/FlowWing"
    (lib/"FlowWing/lib").install "lib/libbuilt_in_module.a"
    (lib/"FlowWing/lib").install "lib/libflowwing_string.a"
    (lib/"FlowWing/lib").install "lib/libraylib.a"
    (lib/"FlowWing/lib").install "lib/libflowwing_vector.so"
    (lib/"FlowWing/lib").install "lib/libflowwing_map.so"

    (lib/"FlowWing/lib/modules").install "lib/modules"
  end

  test do
    system "#{bin}/FlowWing", "--version"
  end
end
