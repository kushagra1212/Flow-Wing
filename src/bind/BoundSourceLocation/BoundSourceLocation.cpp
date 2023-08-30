#include "BoundSourceLocation.h"

BoundSourceLocation::BoundSourceLocation(
    DiagnosticUtils::SourceLocation location)
    : _location(location) {}

struct DiagnosticUtils::SourceLocation
BoundSourceLocation::getLocation() const {
  return _location;
}
