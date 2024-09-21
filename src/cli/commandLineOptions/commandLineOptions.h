#ifndef COMMANDLINEOPTIONS_H
#define COMMANDLINEOPTIONS_H

#include "../../common/version.h"
#include "../../utils/Utils.h"
#include "../argh.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

namespace FlowWing {
namespace Cli {

enum STATUS {
  FAILURE,
  PROCEED,
  DONE,
};

extern argh::parser *cmdl;

template <typename T> struct Option {
  std::string name;
  std::string description;
  std::optional<T> value;
  Option() = default;
  Option(const std::string &name, const std::string &description)
      : name(name), description(description) {}

  void setValue(const T &newValue) { value = newValue; }

  std::optional<T> getValue() const { return value; }
};

namespace isFlag {
int8_t versionName();

int8_t OptimizationLevel0();
int8_t OptimizationLevel1();
int8_t OptimizationLevel2();
int8_t OptimizationLevel3();

int8_t format();
int8_t shortFormat();

int8_t formatPrint();
int8_t ShortFormatPrint();

} // namespace isFlag

namespace isParam {
int8_t file();
int8_t shortFile();

int8_t code();
int8_t shortCode();

int8_t outputFile();
int8_t shortOutputFile();
} // namespace isParam

namespace Get {
std::string file();
std::string shortFile();

std::string code();
std::string shortCode();

std::string outputFile();
std::string shortOutputFile();

} // namespace Get

// Define command-line options

class OPTIONS {
public:
  //? Version
  static Option<bool> Version;
  static Option<bool> ShortVersion;

  //? File
  static Option<std::string> File;
  static Option<std::string> ShortFile;

  //? Format
  static Option<bool> Format;
  static Option<bool> ShortFormat;

  //? Format
  static Option<bool> FormatPrint;
  static Option<bool> ShortFormatPrint;

  //? Code
  static Option<std::string> Code;
  static Option<std::string> ShortCode;

  //? OutPut FIle
  static Option<std::string> OutputFile;
  static Option<std::string> ShortOutputFile;

  //? Optimization
  static Option<int> OptimizationLevel0;
  static Option<int> OptimizationLevel1;
  static Option<int> OptimizationLevel2;
  static Option<int> OptimizationLevel3;

  //? Library Path
  static Option<std::string> LibraryPath;

  //? Linking Library
  static Option<std::string> LinkLibrary;

  //? Framework
  static Option<std::string> Framework;

  //? Entry Point
  static Option<std::string> EntryPoint;
}; // namespace FlowWing_OPTIONS

enum FlowWing::Cli::STATUS handleBasicArgs();
enum FlowWing::Cli::STATUS handleFileArgs(std::vector<std::string> &text,
                                          std::string &filePath, char *argv[]);

} // namespace Cli

} // namespace FlowWing

#endif