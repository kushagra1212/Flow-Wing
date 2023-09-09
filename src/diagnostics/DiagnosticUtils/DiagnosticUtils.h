#ifndef DIAGNOSTIC_UTILS_H
#define DIAGNOSTIC_UTILS_H
#include <string>
namespace DiagnosticUtils {

enum class DiagnosticLevel { Error, Warning, Info, Debug };

enum class DiagnosticType { Lexical, Syntactic, Semantic, CodeGen, Runtime };

std::string toString(DiagnosticLevel level);

std::string toString(DiagnosticType type);

struct SourceLocation {

  int lineNumber;
  int columnNumber;

  SourceLocation() {
    this->lineNumber = 0;
    this->columnNumber = 0;
  }

  SourceLocation(int lineNumber, int columnNumber) {
    this->lineNumber = lineNumber;
    this->columnNumber = columnNumber;
  }
};

} // namespace DiagnosticUtils

#endif // DIAGNOSTIC_UTILS_H