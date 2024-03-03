#ifndef DIAGNOSTIC_UTILS_H
#define DIAGNOSTIC_UTILS_H
#include <string>
namespace DiagnosticUtils {

enum class DiagnosticLevel { Error, Warning, Info, Debug };

enum class DiagnosticType {
  Lexical,
  Syntactic,
  Semantic,
  CodeGen,
  Runtime,
  Linker,
  Fatal
};

std::string toString(DiagnosticLevel level);

std::string toString(DiagnosticType type);

struct SourceLocation {
  int lineNumber;
  int columnNumber;
  std::string absoluteFilePath;

  SourceLocation() {
    this->lineNumber = 0;
    this->columnNumber = 0;
    this->absoluteFilePath = "";
  }

  SourceLocation(int lineNumber, int columnNumber,
                 std::string absoluteFilePath) {
    this->lineNumber = lineNumber;
    this->columnNumber = columnNumber;
    this->absoluteFilePath = absoluteFilePath;
  }
};

}  // namespace DiagnosticUtils

#endif  // DIAGNOSTIC_UTILS_H