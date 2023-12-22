#include "IRParser.h"

IRParser::IRParser() { this->_ir = ""; }

void IRParser::mergeIR(const std::string &ir) { this->_ir += ir; }

void IRParser::mergeIR(llvm::Module *module) {
  this->mergeIR(this->getIR(module));
}

const std::string &IRParser::getIR() const { return this->_ir; }

std::string IRParser::getIR(llvm::Module *module) {
  std::vector<std::string> irLines;

  // Raw string to collect the IR output
  std::string irString;
  llvm::raw_string_ostream irStream(irString);

  // Print the IR to the raw_string_ostream.
  irStream << *module;

  // Convert the raw_string_ostream to a std::string.
  std::string ir = irStream.str();

  return ir;
}

void IRParser::removeDuplicates() {

  std::string ir = "";
  std::string bg = "";

  // Remove Duplicates Function Definition
  ir += this->removeDuplicatesStartWithAndEndWith("define", "}");
  ir += "\n";

  // Remove Duplicates Function Declaration
  bg += this->removeDuplicatesStartWithAndEndWith("declare", "\n");
  bg += "\n";
  // Remove Duplicates Global
  bg += this->removeDuplicatesStartWithAndEndWith("@", "\n");
  bg += "\n";
  this->_ir = bg + ir;
}

std::string
IRParser::removeDuplicatesStartWithAndEndWith(const std::string &startWith,
                                              const std::string &endWith) {
  std::unordered_set<std::string> unique;
  std::string deduplicatedIR;
  size_t pos = 0;
  size_t startPos = 0;

  while ((pos = this->_ir.find(startWith, startPos)) != std::string::npos) {
    size_t endPos = this->_ir.find_first_of(endWith, pos);

    if (endWith == "}") {
      endPos += 1;
    }

    std::string statement = this->_ir.substr(pos, endPos - pos);

    if (unique.find(statement) == unique.end()) {
      unique.insert(statement);
      deduplicatedIR += statement;
      deduplicatedIR += "\n";
    }

    this->_ir.erase(pos, endPos - pos);

    // Move the start position to the next position
    startPos = pos;
  }

  return deduplicatedIR;
}

void IRParser::printIR() { std::cout << this->_ir << "\n"; }