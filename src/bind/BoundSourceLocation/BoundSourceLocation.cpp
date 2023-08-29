#include "BoundSourceLocation.h"

BoundSourceLocation::BoundSourceLocation(
    const struct DiagnosticUtils::SourceLocation &location)
    : _location(location) {}

const struct DiagnosticUtils::SourceLocation &
BoundSourceLocation::getLocation() const {
  return _location;
}
