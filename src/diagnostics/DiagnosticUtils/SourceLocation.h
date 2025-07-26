#pragma once
#include <string>

namespace DiagnosticUtils {
struct SourceLocation {
public:
  int lineNumber;
  int columnNumber;
  int length;
  std::string absoluteFilePath;

  SourceLocation() {
    this->lineNumber = 0;
    this->columnNumber = 0;
    this->absoluteFilePath = "";
  }

  SourceLocation(int lineNumber, int columnNumber, int length,
                 std::string absoluteFilePath) {
    this->lineNumber = lineNumber;
    this->columnNumber = columnNumber;
    this->length = length;
    this->absoluteFilePath = absoluteFilePath;
  }
};
} // namespace DiagnosticUtils