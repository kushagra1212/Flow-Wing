#!/bin/sh
# prerm — passed to fpm --before-remove for .deb packages.
#
# Symmetric to post-install.sh: remove the /usr/local/bin symlinks this
# package created. Only remove a symlink if it still points inside our
# versioned install dir (do not clobber user-created files with the same name).
set -e

case "$1" in
  remove|upgrade|deconfigure)
    for link in /usr/local/bin/FlowWing /usr/local/bin/flowwing \
                /usr/local/bin/FlowWing-jit /usr/local/bin/flowwing-jit; do
      if [ -L "$link" ]; then
        target=$(readlink "$link" 2>/dev/null || true)
        case "$target" in
          /usr/local/flow-wing/*)
            rm -f "$link"
            ;;
        esac
      fi
    done
    ;;
  failed-upgrade) ;;
  *) ;;
esac
exit 0
