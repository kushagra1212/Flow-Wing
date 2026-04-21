#!/bin/bash
set -e

# Arguments:
#   $1: install_prefix - The installation directory (e.g., /usr/local/flow-wing/1.0.0/)
#   $2: installer_name - The output installer filename (e.g., FlowWing-1.0.0-macos-arm64.dmg)
#   $3: os - Platform (macOS, Windows, Linux)
#   $4: arch - Architecture (arm64, x86_64)

INSTALL_PREFIX="$1"
INSTALLER_NAME="$2"
OS="$3"
ARCH="$4"

echo "=== Building installer $INSTALLER_NAME ($OS $ARCH) ==="
echo "Install prefix: $INSTALL_PREFIX"
echo "Installer name: $INSTALLER_NAME"

case "$OS" in
  macOS)
    # Create .dmg using create-dmg
    echo "Creating macOS .dmg installer..."

    APP="/tmp/FlowWing.app"
    rm -rf "$APP"
    mkdir -p "$APP/Contents/MacOS" "$APP/Contents/Resources/FlowWingSDK"

    # Install tree must live at a fixed path inside the bundle (no versioned folder name guessing).
    cp -R "${INSTALL_PREFIX%/}/." "$APP/Contents/Resources/FlowWingSDK/"

    # App icon from repo assets (requires rsvg-convert: brew install librsvg).
    REPO_ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
    LOGO_SVG="$REPO_ROOT/assets/logo/logo.svg"
    ICON_EXTRA=""
    if [[ -f "$LOGO_SVG" ]] && command -v rsvg-convert >/dev/null 2>&1; then
      echo "Building AppIcon.icns from assets/logo/logo.svg"
      RASTER=/tmp/fw-icon-1024.png
      rsvg-convert -w 1024 -h 1024 "$LOGO_SVG" -o "$RASTER"
      ICONSET=/tmp/AppIcon.iconset
      rm -rf "$ICONSET"
      mkdir "$ICONSET"
      sips -z 16 16 "$RASTER" --out "$ICONSET/icon_16x16.png" >/dev/null
      sips -z 32 32 "$RASTER" --out "$ICONSET/icon_16x16@2x.png" >/dev/null
      sips -z 32 32 "$RASTER" --out "$ICONSET/icon_32x32.png" >/dev/null
      sips -z 64 64 "$RASTER" --out "$ICONSET/icon_32x32@2x.png" >/dev/null
      sips -z 128 128 "$RASTER" --out "$ICONSET/icon_128x128.png" >/dev/null
      sips -z 256 256 "$RASTER" --out "$ICONSET/icon_128x128@2x.png" >/dev/null
      sips -z 256 256 "$RASTER" --out "$ICONSET/icon_256x256.png" >/dev/null
      sips -z 512 512 "$RASTER" --out "$ICONSET/icon_256x256@2x.png" >/dev/null
      sips -z 512 512 "$RASTER" --out "$ICONSET/icon_512x512.png" >/dev/null
      sips -z 1024 1024 "$RASTER" --out "$ICONSET/icon_512x512@2x.png" >/dev/null
      iconutil -c icns "$ICONSET" -o "$APP/Contents/Resources/AppIcon.icns"
      ICON_EXTRA="
  <key>CFBundleIconFile</key>
  <string>AppIcon</string>"
    else
      echo "Warning: no app icon (missing $LOGO_SVG or rsvg-convert not in PATH)"
    fi

    # Valid app bundle requires Info.plist; without it Finder shows a broken / “no entry” icon.
    FW_VER="${FLOWWING_VERSION:-0.0.0}"
    cat > "$APP/Contents/Info.plist" << PLIST
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleExecutable</key>
  <string>FlowWing</string>
  <key>CFBundleIdentifier</key>
  <string>dev.flowwing.cli</string>
  <key>CFBundleName</key>
  <string>FlowWing</string>
  <key>CFBundlePackageType</key>
  <string>APPL</string>
  <key>CFBundleShortVersionString</key>
  <string>${FW_VER}</string>
  <key>CFBundleVersion</key>
  <string>1</string>
  <key>LSMinimumSystemVersion</key>
  <string>11.0</string>
  <key>NSHighResolutionCapable</key>
  <true/>${ICON_EXTRA}
</dict>
</plist>
PLIST

    # Launcher.
    #
    # FlowWing is a CLI, so double-clicking FlowWing.app in /Applications used
    # to exec the compiler with no args and exit silently — users reported
    # "drag into Applications and nothing happens". Make the GUI entry point
    # pop a Terminal window that:
    #   (a) prints `FlowWing --version`, then
    #   (b) tells the user how to add the SDK bin/ to PATH and keeps the shell
    #       open (login shell) so they can actually try it.
    # When the same binary is re-entered from Terminal (TERM set & stdin is a
    # tty) we assume the user knows what they're doing and exec the compiler
    # with forwarded args — this keeps `open -a FlowWing -- --help` etc.
    # working for power users.
    cat > "$APP/Contents/MacOS/FlowWing" << 'WRAPPER'
#!/bin/bash
SDK_ROOT="$(cd "$(dirname "$0")/../Resources/FlowWingSDK" && pwd)"
export PATH="$SDK_ROOT/bin:$PATH"
export FLOWWING_MODULES_PATH="$SDK_ROOT/lib/modules"
export FLOWWING_LIB_PATH="$SDK_ROOT/lib"

# Heuristic: launched from Terminal (or `open -W` with args)?  Just exec.
if [ -t 0 ] || [ -t 1 ] || [ "$#" -gt 0 ]; then
  exec "$SDK_ROOT/bin/FlowWing" "$@"
fi

# Otherwise (Finder / Launchpad double-click): pop a Terminal window with a
# friendly session that shows the install is working and leaves the shell open.
WELCOME="/tmp/flowwing-welcome-$$.command"
cat > "$WELCOME" <<EOF
#!/bin/bash
clear
echo "=========================================="
echo "  FlowWing is installed."
echo "=========================================="
echo
"$SDK_ROOT/bin/FlowWing" --version || true
echo
echo "To use FlowWing / flowwing-jit from any Terminal, add this to your shell rc file"
echo "(~/.zshrc for zsh, ~/.bash_profile for bash):"
echo
echo "    export PATH=\"$SDK_ROOT/bin:\\\$PATH\""
echo
echo "Quick try (current shell already has PATH set):"
echo "    FlowWing --help"
echo "    FlowWing-jit <your-file>.fg"
echo
echo "Docs: https://github.com/kushagra1212/Flow-Wing"
echo
exec "\$SHELL" -l
EOF
chmod +x "$WELCOME"
open -a Terminal "$WELCOME"
WRAPPER
    chmod +x "$APP/Contents/MacOS/FlowWing"

    # Short usage note on the disk image (DMG does not modify shell PATH on the system).
    README="/tmp/FlowWing-DMG-README.txt"
    cat > "$README" << EOF
FlowWing ${FW_VER} (macOS)

FlowWing is a command-line compiler, not a GUI app. There are two ways to
install it on macOS; pick one.

──────────────────────────────────────────────────
OPTION A — This .dmg  (drag & drop, no admin)
──────────────────────────────────────────────────

1. Drag "FlowWing.app" into Applications.
2. Double-click it once. A Terminal window will open, print the version,
   and show you the exact PATH line to paste into ~/.zshrc (or ~/.bash_profile).
3. New Terminal tabs will then have \`FlowWing\` and \`FlowWing-jit\` on PATH.

Manual PATH (if you prefer):

  export PATH="/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin:\$PATH"
  FlowWing --version

Or call the binary directly without touching PATH:

  "/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin/FlowWing" --version

──────────────────────────────────────────────────
OPTION B — The .pkg  (double-click, auto PATH)
──────────────────────────────────────────────────

The accompanying FlowWing-${FW_VER}-macos-*.pkg does OPTION A automatically:
it installs under /usr/local/flow-wing/${FW_VER}/ and drops symlinks in
/usr/local/bin (already on Terminal's default PATH).

The .pkg is not signed with an Apple Developer ID, so on first run macOS
Gatekeeper will say "cannot be opened … move to Trash". This is normal for
open-source installers. Bypass it ONCE, either way:

  • Finder:  Control-click the .pkg → Open → Open anyway.
  • Terminal: xattr -d com.apple.quarantine ~/Downloads/FlowWing-*.pkg
             open ~/Downloads/FlowWing-*.pkg

After the .pkg finishes, open a new Terminal tab and run:

  flowwing --version
  flowwing-jit --version

──────────────────────────────────────────────────
Architecture note
──────────────────────────────────────────────────

This build targets the same CPU as the runner that produced it
(arm64 Apple Silicon for the macos-arm64 asset). An Intel Mac cannot run an
arm64 build and vice versa — download the matching asset for your machine.
EOF

    # create-dmg's source must be a *folder whose contents* appear at the DMG root.
    # Passing the .app path directly makes hdiutil/makehybrid flatten the bundle so only
    # a top-level "Contents" folder appears (no FlowWing.app). Stage a parent directory instead.
    STAGE="/tmp/flowwing-dmg-stage"
    rm -rf "$STAGE"
    mkdir -p "$STAGE"
    cp -R "$APP" "$STAGE/FlowWing.app"
    cp "$README" "$STAGE/Read me (PATH).txt"

    # --skip-jenkins / --sandbox-safe: avoid Finder AppleScript in CI; reduces hangs and “window won’t close” issues.
    create-dmg \
      --volname "FlowWing ${FW_VER}" \
      --window-size 600 400 \
      --icon-size 128 \
      --icon "FlowWing.app" 150 200 \
      --app-drop-link 450 200 \
      --icon "Read me (PATH).txt" 300 200 \
      --sandbox-safe \
      --skip-jenkins \
      "/tmp/$INSTALLER_NAME" \
      "$STAGE"

    echo "macOS .dmg created: /tmp/$INSTALLER_NAME"
    mv "/tmp/$INSTALLER_NAME" "$INSTALLER_NAME"

    # ------------------------------------------------------------------
    # Also build a signed-style .pkg installer (GUI double-click).
    #
    # Motivation: a .dmg cannot modify the user's shell PATH because drag-
    # and-drop copying does not run any script. A .pkg, on the other hand,
    # runs a postinstall script as root, which lets us place the SDK under
    # /usr/local/flow-wing/<version>/ and drop symlinks into /usr/local/bin/
    # (which Terminal.app has on PATH by default). End result: after the
    # .pkg finishes, users can run `flowwing --version` and
    # `flowwing-jit --version` immediately.
    # ------------------------------------------------------------------
    PKG_INSTALLER_NAME="${PKG_INSTALLER_NAME:-${INSTALLER_NAME%.dmg}.pkg}"
    echo "Creating macOS .pkg installer ($PKG_INSTALLER_NAME)..."

    PKG_ROOT="/tmp/flowwing-pkg-root"
    PKG_SCRIPTS="/tmp/flowwing-pkg-scripts"
    PKG_VERSIONED_DIR="/usr/local/flow-wing/${FW_VER}"

    rm -rf "$PKG_ROOT" "$PKG_SCRIPTS"
    mkdir -p "${PKG_ROOT}${PKG_VERSIONED_DIR}" "$PKG_SCRIPTS"
    cp -R "${INSTALL_PREFIX%/}/." "${PKG_ROOT}${PKG_VERSIONED_DIR}/"

    # postinstall runs as root after the payload is copied to / .
    # - Creates flowwing / FlowWing / flowwing-jit / FlowWing-jit symlinks
    #   in /usr/local/bin so the binaries are on the default Terminal PATH.
    # - Stable /usr/local/flow-wing/current → <version>/ symlink so later
    #   upgrades can flip the pointer without re-writing /usr/local/bin.
    cat > "$PKG_SCRIPTS/postinstall" << 'POSTINSTALL'
#!/bin/bash
set -e

INSTALL_ROOT="/usr/local/flow-wing"
CURRENT_LINK="${INSTALL_ROOT}/current"
BIN_DIR="/usr/local/bin"

mkdir -p "$BIN_DIR"

# Pick the newest versioned install and point /usr/local/flow-wing/current at it.
NEWEST_VERSION_DIR="$(ls -1dt "${INSTALL_ROOT}"/*/ 2>/dev/null | grep -v "/current/$" | sort -V | head -n 1 | sed 's:/$::' || true)"
if [ -n "$NEWEST_VERSION_DIR" ]; then
  ln -sfn "$NEWEST_VERSION_DIR" "$CURRENT_LINK"
fi

TARGET_BIN="${CURRENT_LINK}/bin"

if [ -x "${TARGET_BIN}/FlowWing" ]; then
  ln -sfn "${TARGET_BIN}/FlowWing"     "${BIN_DIR}/FlowWing"
  ln -sfn "${TARGET_BIN}/FlowWing"     "${BIN_DIR}/flowwing"
fi
if [ -x "${TARGET_BIN}/FlowWing-jit" ]; then
  ln -sfn "${TARGET_BIN}/FlowWing-jit" "${BIN_DIR}/FlowWing-jit"
  ln -sfn "${TARGET_BIN}/FlowWing-jit" "${BIN_DIR}/flowwing-jit"
fi

exit 0
POSTINSTALL

    chmod +x "$PKG_SCRIPTS/postinstall"

    # Component package → distribution package. productbuild produces a
    # Distribution-style .pkg that Installer.app accepts as a double-click
    # installer (plain pkgbuild output works too, but productbuild is the
    # macOS-recommended layer for user-facing installers).
    COMPONENT_PKG="/tmp/flowwing-component.pkg"
    pkgbuild \
      --root "$PKG_ROOT" \
      --identifier "dev.flowwing.cli" \
      --version "${FW_VER}" \
      --install-location "/" \
      --scripts "$PKG_SCRIPTS" \
      "$COMPONENT_PKG"

    productbuild \
      --identifier "dev.flowwing.cli.distribution" \
      --version "${FW_VER}" \
      --package "$COMPONENT_PKG" \
      "$PKG_INSTALLER_NAME"

    rm -rf "$PKG_ROOT" "$PKG_SCRIPTS" "$COMPONENT_PKG"
    echo "macOS .pkg created: $PKG_INSTALLER_NAME"
    ;;
    
  Windows)
    # Create NSIS installer
    echo "Creating Windows NSIS installer..."
    
    # Create NSIS script
    cat > installer.nsi << NSIS_EOF
!include MUI.nsh
!include LogicLib.nsh

Name "FlowWing $FLOWWING_VERSION"
OutFile "$INSTALLER_NAME"

RequestExecutionLevel admin
SetOverwrite on

!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE English

; Default install directory
InstallDir "C:\Program Files\FlowWing\\$FLOWWING_VERSION"

Section "Install"
  SetOutPath \$INSTDIR
  
  ; Copy all files from the install prefix
  File /r "$INSTALL_PREFIX\*"
  
  ; Create Start Menu shortcut
  CreateShortCut "\$SMPROGRAMS\FlowWing.lnk" "\$INSTDIR\bin\FlowWing.exe" ""
  
  ; Write Registry keys for uninstaller
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing" "DisplayVersion" "$FLOWWING_VERSION"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing" "InstallLocation" "\$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing" "UninstallString" "\$INSTDIR\uninstall.exe"
  
  ; Add bin to System PATH using PowerShell (Bypasses NSIS 1024-char limit)
  DetailPrint "Adding FlowWing to System PATH..."
  nsExec::ExecToLog 'powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "\$target = ''\$INSTDIR\bin''; \$path = [Environment]::GetEnvironmentVariable(''PATH'', ''Machine''); if (\$path -notmatch [regex]::Escape(\$target)) { [Environment]::SetEnvironmentVariable(''PATH'', \$path + '';'' + \$target, ''Machine'') }"'
  
  ; Create uninstaller
  WriteUninstaller "\$INSTDIR\uninstall.exe"
SectionEnd

Section "Uninstall"
  ; Remove from System PATH using PowerShell
  DetailPrint "Removing FlowWing from System PATH..."
  nsExec::ExecToLog 'powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "\$target = ''\$INSTDIR\bin''; \$path = [Environment]::GetEnvironmentVariable(''PATH'', ''Machine''); \$newPath = (\$path -split '';'' | Where-Object { \$_ -and \$_ -ne \$target }) -join '';''; [Environment]::SetEnvironmentVariable(''PATH'', \$newPath, ''Machine'')"'
  
  ; Remove registry entries
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing"
  
  ; Remove start menu shortcut
  Delete "\$SMPROGRAMS\FlowWing.lnk"
  
  ; Remove installed files
  RMDir /r "\$INSTDIR"
SectionEnd
NSIS_EOF
    
    # Build the installer
    makensis installer.nsi
    
    echo "Windows NSIS installer created: $INSTALLER_NAME"
    ;;
    
  Linux)
    # Create .deb using fpm
    echo "Creating Linux .deb installer..."

    DEB_ARCH=$ARCH
    if [ "$ARCH" = "x86_64" ]; then
      DEB_ARCH="amd64"
    fi
    
    # Create control file
    mkdir -p /tmp/flowwing-deb/DEBIAN
    cat > /tmp/flowwing-deb/DEBIAN/control << DEB_EOF
Package: flowwing
Version: $FLOWWING_VERSION
Section: devel
Priority: optional
Architecture: $DEB_ARCH
Maintainer: FlowWing <kushagrarathore002@gmail.com>
Description: FlowWing Programming Language
 FlowWing is a fast, simple, and easy to use programming language with
 static and dynamic typing, object-oriented programming, and memory management.
DEB_EOF

    # fpm ships the hook scripts into DEBIAN/ with the mode they have on disk, so force +x
    # (git doesn't always preserve the executable bit on shell scripts across clones / Windows).
    chmod +x .github/workflows/scripts/post-install.sh .github/workflows/scripts/pre-remove.sh

    # Package using fpm (DEB_ARCH is e.g. amd64 for x86_64)
    # Note: fpm has no --deb-repo; use --deb-field for custom control stanzas if needed.
    fpm -f \
      -s dir \
      -t deb \
      -n flowwing \
      -v "$FLOWWING_VERSION" \
      -a "$DEB_ARCH" \
      --after-install .github/workflows/scripts/post-install.sh \
      --before-remove .github/workflows/scripts/pre-remove.sh \
      --package "$INSTALLER_NAME" \
      "${INSTALL_PREFIX%/}/=/usr/local/flow-wing/${FLOWWING_VERSION}/"
    
    echo "Linux .deb installer created: $INSTALLER_NAME"
    ;;
esac

echo "=== Installer build complete ==="
