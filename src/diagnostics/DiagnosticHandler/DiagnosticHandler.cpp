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

std::string DiagnosticHandler::getErrorProducingSnippet(int lineNumber,
                                                        int columnNumber) {
  std::string snippet = "\n";
  std::vector<std::string> lines = isRepl() ? getReplLines() : getLines();
  int lineCount = lines.size();
  int currentLineNumber = 1;

  auto errorMarker = [&]() {
    std::string marker = "";
    marker += GREEN_TEXT;
    marker += BOLD;
    for (int i = 0; i < columnNumber; i++) {
      marker += " ";
    }
    marker += "\n";
    marker += "   ";
    for (int i = 0; i < columnNumber; i++) {
      marker += "^";
    }
    marker += RESET;
    marker += "\n";
    return marker;
  };

  while (currentLineNumber <= lineCount) {
    if (currentLineNumber <= lineNumber + 4 &&
        currentLineNumber >= lineNumber - 4) {
      snippet += YELLOW + std::to_string(currentLineNumber) + "| " + RESET;
      if (currentLineNumber <= lineNumber && currentLineNumber >= lineNumber) {
        snippet += PINK_TEXT;
      } else {
        snippet += RESET;
      }
      snippet += lines[currentLineNumber - 1] + "\n";
      snippet += RESET;
      if (lineNumber == currentLineNumber) {

        snippet += errorMarker();
      }
    }
    currentLineNumber++;
  }
  if (lineNumber == currentLineNumber && snippet != "\n") {
    snippet += errorMarker();
  }
  return snippet;
}

void DiagnosticHandler::setReplLines(
    const std::vector<std::string> &replLines) {
  this->_replLines = replLines;
}

const std::vector<std::string> &DiagnosticHandler::getReplLines() const {
  return this->_replLines;
}

std::vector<std::string> DiagnosticHandler::getLines() {
  std::vector<std::string> lines;
  std::ifstream fileStream(_filePath);
  std::string line;

  while (std::getline(fileStream, line)) {
    lines.push_back(line);
  }

  return lines;
}

const int8_t DiagnosticHandler::isRepl() const {
  return this->_replLines.size() > 0 ? 1 : 0;
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
      break;
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

#ifdef JIT_TEST_MODE
  return diagnostic.getMessage();
#endif
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

  std::string logString =
      getErrorProducingSnippet(stoi(lineNumber), stoi(columnNumber));

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