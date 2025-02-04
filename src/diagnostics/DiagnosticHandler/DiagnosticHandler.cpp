#include "DiagnosticHandler.h"

using namespace FlowWing;

DiagnosticHandler::DiagnosticHandler(std::string filePath,
                                     DiagnosticHandler *parent)
    : parent(parent) {
  this->_filePath = (filePath);
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
    marker += GREEN;
    marker += BOLD;
    for (int i = 0; i < columnNumber; i++) {
      marker += " ";
    }
    marker += "\n";
    marker += "   ";
    for (int i = 0; i < columnNumber; i++) {
      if (i == columnNumber - 1) {
        marker += "^";
      } else {
        marker += "~";
      }
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
        snippet += RED;
        snippet += BOLD;
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
    parent->setOutputFilePath(_outputFilePath);
    parent->logDiagnostics(outputStream, filter);
  }

  for (auto &diagnostic : diagnostics) {

    if (filter(diagnostic)) {
      printDiagnostic(outputStream, diagnostic);

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
  std::string message = diagnostic.getMessage();
  std::string level = DiagnosticUtils::toString(diagnostic.getLevel());
  std::string type = DiagnosticUtils::toString(diagnostic.getType());
  std::string lineNumber = std::to_string(diagnostic.getLocation().lineNumber +
                                          1 - previousLineCount);
  std::string columnNumber =
      std::to_string(diagnostic.getLocation().columnNumber + 1);
  std::string line = "Line " + lineNumber + ":" + columnNumber;
  std::string logString = "";
  std::string fileName = "";
  std::string fileOut = "";
  if (diagnostic.getType() == DiagnosticUtils::DiagnosticType::Linker) {
    line = "";
  } else {

    logString =
        diagnostic.getLevel() != DiagnosticUtils::DiagnosticLevel::Info
            ? getErrorProducingSnippet(stoi(lineNumber), stoi(columnNumber))
            : " ";

    fileName += "File: ";
    const std::string FILEPATH =
        (diagnostic.getLocation().absoluteFilePath != ""
             ? diagnostic.getLocation().absoluteFilePath
             : this->_filePath);
    fileName += this->getFileName(FILEPATH);

    if (_filePath != "") {
      fileOut = YELLOW;
      fileOut += "Location: " + FILEPATH + "\n" + RESET;
    }
  }

  if (diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Error) {

    logString += RED + fileName + " [" + level + "] : " + RED_TEXT + line +
                 RED + " \"" + message + "\"" + RESET + "\n";
  } else if (diagnostic.getLevel() ==
             DiagnosticUtils::DiagnosticLevel::Warning) {
    logString += YELLOW + fileName + " [" + level + "] : " + YELLOW_TEXT +
                 line + YELLOW + " \"" + message + "\"" + RESET + "\n";
  } else if (diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Info) {
    logString += BLUE + fileName + " [" + level + "] : " + BLUE_TEXT + line +
                 BLUE + " \"" + message + "\"" + RESET + "\n";
  } else if (diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Debug) {
    logString += GREEN + fileName + " [" + level + "] : " + GREEN_TEXT + line +
                 GREEN + " \"" + message + "\"" + RESET + "\n";
  }
  logString += fileOut;

  return logString;
}

void DiagnosticHandler::logJSONifAsked(const std::string &outputFilePath,
                                       const Diagnostic &diagnostic) {
  if (Utils::getExtension(outputFilePath) == ".json") {
    JSON errorObject = {
        {"level", DiagnosticUtils::toString(diagnostic.getLevel())},
        {"error",
         diagnostic.getLevel() == DiagnosticUtils::DiagnosticLevel::Error},
        {"message", (diagnostic.getMessage())},
        {"type", DiagnosticUtils::toString(diagnostic.getType())},
        {"location",
         {
             {"line", diagnostic.getLocation().lineNumber + 1},
             {"column", diagnostic.getLocation().columnNumber + 1},
             {"length", diagnostic.getLocation().length},
         }}};

    Utils::logJSON(errorObject, _outputFilePath.substr(
                                    0, _outputFilePath.find_last_of(".")) +
                                    ".err.json");
  }
}

const void DiagnosticHandler::printDiagnostic(std::ostream &outputStream,
                                              const Diagnostic &diagnostic) {

  this->logJSONifAsked(_outputFilePath, diagnostic);
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