#!/bin/sh
# prerm — passed to fpm --before-remove for .deb packages
set -e
case "$1" in
  remove|upgrade|deconfigure) ;;
  failed-upgrade) ;;
  *) ;;
esac
exit 0
