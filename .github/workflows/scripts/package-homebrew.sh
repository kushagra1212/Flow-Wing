#!/bin/bash
set -e

# Arguments:
#   $1: version - Release version (e.g., 1.0.0)
#   $2: release_url - GitHub release HTML URL
#   $3: token - GitHub token for the homebrew-tap repo
#   $4: username - Git username
#   $5: email - Git email

VERSION="$1"
RELEASE_URL="$2"
TOKEN="$3"
USERNAME="$4"
EMAIL="$5"

echo "=== Publishing to Homebrew ==="
echo "Version: $VERSION"
echo "Release URL: $RELEASE_URL"

# Determine the correct download URL based on platform
MACOS_URL="$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("macos-arm64")) | .browser_download_url')"

if [ -z "$MACOS_URL" ]; then
  echo "Warning: Could not find macOS artifact for Homebrew formula."
  exit 0
fi

# Create the formula
cat > FlowWing.rb << FORMULA_EOF
class Flowwing < Formula
  desc "A fast, simple, and easy to use programming language"
  homepage "https://github.com/kushagra1212/Flow-Wing"
  version "$VERSION"

  on_macos do
    if Hardware::CPU.arm?
      url "$MACOS_URL"
      sha256 "$(curl -s "$MACOS_URL" | shasum -a 256 | cut -d' ' -f1)"
    else
      # Intel Mac (if available)
      url "$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("macos")) | .browser_download_url')"
      sha256 "$(curl -s "$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("macos")) | .browser_download_url')" | shasum -a 256 | cut -d' ' -f1)"
    end
  end

  on_linux do
    url "$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("linux")) | .browser_download_url')"
    sha256 "$(curl -s "$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("linux")) | .browser_download_url')" | shasum -a 256 | cut -d' ' -f1)"
  end

  on_windows do
    url "$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("windows")) | .browser_download_url')"
    sha256 "$(curl -s "$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("windows")) | .browser_download_url')" | shasum -a 256 | cut -d' ' -f1)"
  end

  license "GPL-2.0-only"

  depends_on :macos => :arm64

  def install
    if OS.mac? && Hardware::CPU.arm?
      # macOS ARM64
      lib_dir = "FlowWing-$VERSION-macos-arm64"
      mkdir_p lib_dir
      system "unzip", "-d", lib_dir, "#{share}/#{lib_dir}.zip"
      bin.install Dir["#{lib_dir}/bin/*"]
      lib.install Dir["#{lib_dir}/lib/**/*"]
    elsif OS.linux?
      # Linux
      deb_file = "#{share}/FlowWing-$VERSION-linux-x86_64.deb"
      system "dpkg", "-x", deb_file, "deb_extracted"
      bin.install "deb_extracted/usr/local/flow-wing/$VERSION/bin/*"
      lib.install "deb_extracted/usr/local/flow-wing/$VERSION/lib"
    else
      skip "Unsupported platform for Homebrew formula"
    end
  end

  test do
    system "#{bin}/FlowWing", "--version"
  end
end
FORMULA_EOF

# Create a branch and PR
git config user.name "$USERNAME"
git config user.email "$EMAIL"
git checkout -b "bump-flowwing-$VERSION"
git add FlowWing.rb
git commit -m "FlowWing $VERSION"
git push "https://${TOKEN}@github.com/$USERNAME/homebrew-flowwing.git" "bump-flowwing-$VERSION" --force

# Create PR
curl -X POST \
  -H "Authorization: token $TOKEN" \
  -H "Accept: application/vnd.github.v3+json" \
  "https://api.github.com/repos/$USERNAME/homebrew-flowwing/pulls" \
  -d "{\"title\":\"FlowWing $VERSION\",\"head\":\"bump-flowwing-$VERSION\",\"base\":\"main\",\"body\":\"Auto-update for FlowWing $VERSION\\n\\nRelease: $RELEASE_URL\"}"

echo "=== Homebrew PR created ==="
