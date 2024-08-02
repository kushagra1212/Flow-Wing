#ifndef COMMANDLINEOPTIONS_H
#define COMMANDLINEOPTIONS_H

#include <optional>
#include <string>

namespace FlowWingCliOptions {
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
}; // namespace FlowWing_OPTIONS

} // namespace FlowWingCliOptions

#endif