#!/bin/bash
set -e

# Arguments:
#   $1: version - Release version (e.g., 1.0.0)
#   $2: release_url - GitHub release HTML URL
#   $3: token - GitHub PAT with push access to the tap repo (HOMEBREW_TAP_TOKEN)
#
# Git author and tap repo owner ($GITHUB_ACTOR / homebrew-$GITHUB_ACTOR on GitHub):
#   Set GIT_AUTHOR_NAME and GIT_AUTHOR_EMAIL in CI (e.g. github.actor + noreply email).
#   Locally you can export them or rely on GITHUB_ACTOR when set.

VERSION="$1"
RELEASE_URL="$2"
TOKEN="$3"

# Tap remote is https://github.com/$TAP_OWNER/homebrew-flowwing — default: user who runs the workflow
TAP_OWNER="${TAP_OWNER:-${GITHUB_ACTOR:-}}"

GIT_AUTHOR_NAME="${GIT_AUTHOR_NAME:-${GITHUB_ACTOR:-FlowWing Bot}}"
GIT_AUTHOR_EMAIL="${GIT_AUTHOR_EMAIL:-github-actions[bot]@users.noreply.github.com}"

echo "=== Publishing to Homebrew ==="
echo "Version: $VERSION"
echo "Release URL: $RELEASE_URL"

# Determine the correct download URL based on platform
MACOS_URL="$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("macos-arm64")) | .browser_download_url')"

if [ -z "$MACOS_URL" ]; then
  echo "Warning: Could not find macOS artifact for Homebrew formula."
  exit 0
fi

if [ -z "$TOKEN" ]; then
  echo "Warning: HOMEBREW_TAP_TOKEN is not set; skipping Homebrew tap PR."
  exit 0
fi

if [ -z "$TAP_OWNER" ]; then
  echo "Error: TAP_OWNER / GITHUB_ACTOR is empty (cannot infer github.com/<owner>/homebrew-flowwing)."
  exit 1
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

# Push only the formula to the tap repo. Do NOT push a branch from this (Flow-Wing) clone: that
# branch would contain the entire project tree, and GitHub rejects PAT pushes that touch
# .github/workflows/* without the workflow scope.
REPO_ROOT="${GITHUB_WORKSPACE:-$PWD}"
FORMULA_SRC="$REPO_ROOT/FlowWing.rb"
TAP_DIR="$(mktemp -d)"
trap 'rm -rf "$TAP_DIR"' EXIT

TAP_REMOTE="https://x-access-token:${TOKEN}@github.com/${TAP_OWNER}/homebrew-flowwing.git"
GIT_TERMINAL_PROMPT=0 git -c credential.helper= clone --depth 1 "$TAP_REMOTE" "$TAP_DIR"

cd "$TAP_DIR"
git config user.name "$GIT_AUTHOR_NAME"
git config user.email "$GIT_AUTHOR_EMAIL"
git checkout -b "bump-flowwing-$VERSION"
cp "$FORMULA_SRC" FlowWing.rb
git add FlowWing.rb
git commit -m "FlowWing $VERSION"
git -c credential.helper= push "$TAP_REMOTE" "bump-flowwing-$VERSION" --force
cd "$REPO_ROOT"

# Create PR
curl -X POST \
  -H "Authorization: token $TOKEN" \
  -H "Accept: application/vnd.github.v3+json" \
  "https://api.github.com/repos/${TAP_OWNER}/homebrew-flowwing/pulls" \
  -d "{\"title\":\"FlowWing $VERSION\",\"head\":\"bump-flowwing-$VERSION\",\"base\":\"main\",\"body\":\"Auto-update for FlowWing $VERSION\\n\\nRelease: $RELEASE_URL\"}"

echo "=== Homebrew PR created ==="
