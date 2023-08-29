#ifndef BOUND_SOURCE_LOCATION_H
#define BOUND_SOURCE_LOCATION_H

#include "../../diagnostics/DiagnosticUtils/DiagnosticUtils.h"

class BoundSourceLocation {
public:
  BoundSourceLocation(const struct DiagnosticUtils::SourceLocation &location);
  const struct DiagnosticUtils::SourceLocation &getLocation() const;

private:
  const struct DiagnosticUtils::SourceLocation &_location;
};

#endif // BOUND_SOURCE_LOCATION_H