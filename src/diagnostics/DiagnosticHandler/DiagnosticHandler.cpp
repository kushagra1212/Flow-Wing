#include "DiagnosticHandler.h"

DiagnosticHandler::DiagnosticHandler(std::string filePath,
                                     DiagnosticHandler *parent)
    : parent(parent) {
  this->_filePath = Utils::getAbsoluteFilePath(filePath);
}

void DiagnosticHandler::addDiagnostic(const Diagnostic &diagnostic) {

  this->diagnostics.push_back(diagnostic);
}

void DiagnosticHandler::addParentDiagnostics(DiagnosticHandler *pat) {
  if (pat != nullptr) {
    this->parent = pat;
  }
}

std::string DiagnosticHandler::getAbsoluteFilePath() { return this->_filePath; }

const void DiagnosticHandler::logDiagnostics(
    std::ostream &outputStream,
    std::function<bool(const Diagnostic &)> filter) {

  if (parent != nullptr) {
    parent->logDiagnostics(outputStream, filter);
  }

  for (auto &diagnostic : this->diagnostics) {
    if (filter(diagnostic)) {
      printDiagnostic(outputStream, diagnostic);
      if (_filePath != "") {
        std::string fileOut = YELLOW;
        fileOut += "Location: " + this->_filePath + "\n" + RESET;
        outputStream << fileOut;
      }
    }
  }

  // Reset the diagnostics
}

std::string DiagnosticHandler::getFileName(const std::string &filePath) {
  if (filePath == "") {
    return "REPL";
  }
  const int &lastSlashIndex = filePath.find_last_of("/\\");
  if (lastSlashIndex == std::string::npos) {
    return "FILE NOT FOUND";
  }

  return filePath.substr(lastSlashIndex + 1);
}

std::string DiagnosticHandler::getLogString(const Diagnostic &diagnostic) {
  std::string fileName = "File: ";
  fileName += this->getFileName(diagnostic.getLocation().absoluteFilePath != ""
                                    ? diagnostic.getLocation().absoluteFilePath
                                    : this->_filePath);
  std::string message = diagnostic.getMessage();
  std::string level = DiagnosticUtils::toString(diagnostic.getLevel());
  std::string type = DiagnosticUtils::toString(diagnostic.getType());
  std::string lineNumber = std::to_string(diagnostic.getLocation().lineNumber +
                                          1 - previousLineCount);
  std::string columnNumber =
      std::to_string(diagnostic.getLocation().columnNumber + 1);

  std::string logString = "";

  if (diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Error) {

    logString += RED + fileName + " [" + level + "] : " + RED_TEXT + "Line " +
                 lineNumber + ":" + columnNumber + RED + " \"" + message +
                 "\"" + RESET + "\n";
  } else if (diagnostic.getLevel() ==
             DiagnosticUtils::DiagnosticLevel::Warning) {
    logString += YELLOW + fileName + " [" + level + "] : " + YELLOW_TEXT +
                 "Line " + lineNumber + ":" + columnNumber + YELLOW + " \"" +
                 message + "\"" + RESET + "\n";
  } else if (diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Info) {
    logString += BLUE + fileName + " [" + level + "] : " + BLUE_TEXT + "Line " +
                 lineNumber + ":" + columnNumber + BLUE + " \"" + message +
                 "\"" + RESET + "\n";
  } else if (diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Debug) {
    logString += GREEN + fileName + " [" + level + "] : " + GREEN_TEXT +
                 "Line " + lineNumber + ":" + columnNumber + GREEN + " \"" +
                 message + "\"" + RESET + "\n";
  }

  return logString;
}

const void DiagnosticHandler::printDiagnostic(std::ostream &outputStream,
                                              const Diagnostic &diagnostic) {
  outputStream << getLogString(diagnostic);
}

bool DiagnosticHandler::hasError(DiagnosticUtils::DiagnosticLevel level) const {
  bool hasError = std::any_of(diagnostics.begin(), diagnostics.end(),
                              [level](const Diagnostic &diagnostic) {
                                return diagnostic.getLevel() == level;
                              });

  if (parent != nullptr) {
    return parent->hasError(level) || hasError;
  }

  return hasError;
}

bool DiagnosticHandler::hasError(DiagnosticUtils::DiagnosticType type) const {
  bool hasError = std::any_of(
      diagnostics.begin(), diagnostics.end(),
      [type](const Diagnostic &diagnostic) {
        return diagnostic.getType() == type &&
               diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Error;
      });
  if (parent != nullptr) {
    return parent->hasError(type) || hasError;
  }

  return hasError;
}

void DiagnosticHandler::updatePreviousLineCount(const int count) {
  this->previousLineCount = count;
}