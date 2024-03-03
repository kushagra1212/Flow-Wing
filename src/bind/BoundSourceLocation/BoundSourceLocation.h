#ifndef BOUND_SOURCE_LOCATION_H
#define BOUND_SOURCE_LOCATION_H

#include "../../diagnostics/DiagnosticUtils/DiagnosticUtils.h"

class BoundSourceLocation {
 public:
  BoundSourceLocation(DiagnosticUtils::SourceLocation location);
  DiagnosticUtils::SourceLocation getLocation() const;

  BoundSourceLocation() = delete;

 private:
  DiagnosticUtils::SourceLocation _location;
};

#endif  // BOUND_SOURCE_LOCATION_H