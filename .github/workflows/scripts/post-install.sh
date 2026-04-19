#!/bin/sh
# postinst — passed to fpm --after-install for .deb packages
set -e
case "$1" in
  configure) ;;
  abort-upgrade|abort-remove|abort-deconfigure) ;;
  *) ;;
esac
exit 0
