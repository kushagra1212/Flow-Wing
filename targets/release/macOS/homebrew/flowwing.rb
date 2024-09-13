class Flowwing < Formula
  desc "A Programming language that uniquely combines dynamic and static typing paradigms"
  homepage "https://github.com/kushagra1212/Flow-Wing"
  url "https://github.com/kushagra1212/Flow-Wing/releases/download/v0.0.1-alpha/FlowWing-0.0.1.tar.gz"
  sha256 "e57bf6b4fe750c8cc3424d6cd43ea443197814180dd1af0bfea012f18b14ee9a"
  license "FlowWing Contribution License v1.0"

  def install
    bin.install "bin/FlowWing"
    lib.install "lib/libbuilt_in_module.a"
    lib.install "lib/libflowwing_vector.so"
    lib.install "lib/libflowwing_map.so"
    lib.install "lib/libflowwing_string.so"
  end

  test do
    system "#{bin}/FlowWing", "--version"
  end
end
