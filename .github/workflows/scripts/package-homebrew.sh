#!/bin/bash
set -euo pipefail

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
TOKEN="${3:-}"

# Tap remote is https://github.com/$TAP_OWNER/homebrew-flowwing — default: user who runs the workflow
TAP_OWNER="${TAP_OWNER:-${GITHUB_ACTOR:-}}"

GIT_AUTHOR_NAME="${GIT_AUTHOR_NAME:-${GITHUB_ACTOR:-FlowWing Bot}}"
GIT_AUTHOR_EMAIL="${GIT_AUTHOR_EMAIL:-github-actions[bot]@users.noreply.github.com}"

echo "=== Publishing to Homebrew ==="
echo "Version: $VERSION"
echo "Release URL: $RELEASE_URL"

# Authenticated API calls avoid rate limits and empty JSON responses in CI.
GITHUB_API_HEADERS=()
if [ -n "${GITHUB_TOKEN:-}" ]; then
  GITHUB_API_HEADERS=(-H "Authorization: Bearer ${GITHUB_TOKEN}" -H "Accept: application/vnd.github+json" -H "X-GitHub-Api-Version: 2022-11-28")
fi

RELEASE_JSON="$(curl -fsSL "${GITHUB_API_HEADERS[@]}" "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/${VERSION}")"

# SDK zip only (release also publishes .dmg with the same "macos-arm64" in the name; jq must not match both).
MACOS_URL="$(echo "$RELEASE_JSON" | jq -r '.assets[]? | select(.name | endswith("-macos-arm64.zip")) | .browser_download_url' | head -n1)"
LINUX_URL="$(echo "$RELEASE_JSON" | jq -r '.assets[]? | select(.name | endswith("-linux-x86_64.deb")) | .browser_download_url' | head -n1)"

# Download to a file and hash the file. Piping `curl | shasum` can record the empty-file hash
# (e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855) if the request fails silently.
checksum_release_asset() {
  local url="$1"
  local label="$2"
  local tmp
  tmp="$(mktemp)"
  if ! curl -fSL --retry 3 --retry-delay 2 -o "$tmp" "$url"; then
    rm -f "$tmp"
    echo "Error: failed to download ${label}: ${url}" >&2
    exit 1
  fi
  local sz
  sz="$(wc -c < "$tmp" | tr -d ' ')"
  if [ "${sz:-0}" -eq 0 ]; then
    rm -f "$tmp"
    echo "Error: downloaded ${label} is 0 bytes: ${url}" >&2
    exit 1
  fi
  shasum -a 256 "$tmp" | cut -d' ' -f1
  rm -f "$tmp"
}

if [ -z "$MACOS_URL" ]; then
  echo "Warning: Could not find macOS arm64 SDK zip for Homebrew formula."
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

MACOS_SHA256="$(checksum_release_asset "$MACOS_URL" "macOS arm64 SDK zip")"

LINUX_BLOCK=""
if [ -n "$LINUX_URL" ]; then
  LINUX_SHA256="$(checksum_release_asset "$LINUX_URL" "Linux .deb")"
  LINUX_BLOCK="$(printf '%s\n' "  on_linux do" "    url \"$LINUX_URL\"" "    sha256 \"$LINUX_SHA256\"" "  end")"
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
      sha256 "$MACOS_SHA256"
    else
      odie "FlowWing: this tap only publishes an Apple Silicon (arm64) macOS SDK zip. Use Linux/Windows releases or build from source on Intel Macs."
    end
  end

${LINUX_BLOCK}

  # Do not use `on_windows` here: it is not defined on many Homebrew versions (e.g. macOS),
  # and the install path below only supports macOS arm64 and Linux anyway.

  license "GPL-2.0-only"

  def install
    if OS.mac? && Hardware::CPU.arm?
      # macOS ARM64 - flat structure matching actual zip contents
      bin.install "bin/FlowWing"
      
      # Install all library files recursively, preserving directory structure
      lib.install Dir["lib/**/*"]
    elsif OS.linux?
      # Linux
      deb_file = cached_download
      system "dpkg", "-x", deb_file, "deb_extracted"
      bin.install "deb_extracted/usr/local/flow-wing/#{version}/bin/*"
      lib.install Dir["deb_extracted/usr/local/flow-wing/#{version}/lib/**/*"]
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
