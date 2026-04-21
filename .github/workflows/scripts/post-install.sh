#!/bin/sh
# postinst — passed to fpm --after-install for .deb packages.
#
# The release installs into /usr/local/flow-wing/<version>/bin/FlowWing which is
# NOT on a typical $PATH, so `flowwing --version` would fail after `dpkg -i`.
# This hook creates stable symlinks in /usr/local/bin/ for both the AOT driver
# (FlowWing / flowwing) and the JIT interpreter (FlowWing-jit / flowwing-jit).
#
# We resolve the newest install dir dynamically: the package filename embeds
# the version but the post-install script itself is version-agnostic by design.
set -e

case "$1" in
  configure|"")
    install_root=""
    if [ -d /usr/local/flow-wing ]; then
      # Pick the most recent versioned install (sort -V handles v0.0.3, v0.0.10, ...)
      install_root=$(ls -1d /usr/local/flow-wing/*/ 2>/dev/null | sort -V | tail -n 1 | sed 's:/$::')
    fi

    if [ -n "$install_root" ] && [ -x "$install_root/bin/FlowWing" ]; then
      mkdir -p /usr/local/bin
      ln -sfn "$install_root/bin/FlowWing"     /usr/local/bin/FlowWing
      ln -sfn "$install_root/bin/FlowWing"     /usr/local/bin/flowwing
      if [ -x "$install_root/bin/FlowWing-jit" ]; then
        ln -sfn "$install_root/bin/FlowWing-jit" /usr/local/bin/FlowWing-jit
        ln -sfn "$install_root/bin/FlowWing-jit" /usr/local/bin/flowwing-jit
      fi
    fi
    ;;
  abort-upgrade|abort-remove|abort-deconfigure) ;;
  *) ;;
esac
exit 0
