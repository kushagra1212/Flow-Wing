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
  std::string fileName;

  SourceLocation() {
    this->lineNumber = 0;
    this->columnNumber = 0;
    this->fileName = "";
  }

  SourceLocation(int lineNumber, int columnNumber, std::string fileName = "") {
    this->lineNumber = lineNumber;
    this->columnNumber = columnNumber;
    this->fileName = fileName;
  }
};

} // namespace DiagnosticUtils

#endif // DIAGNOSTIC_UTILS_H