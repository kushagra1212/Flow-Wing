#include "commandLineOptions.h"

namespace FlowWingCliOptions {

// Version Options
Option<bool> OPTIONS::Version{
    "--version", "When this flag is set, the version will be printed"};
Option<bool> OPTIONS::ShortVersion{"-V", "Short hand flag for --version"};

// File Options
Option<std::string> OPTIONS::File{
    "--file", "Use --file=<filename.fg/filePath.fg> to specify a file"};
Option<std::string> OPTIONS::ShortFile{"-F", "Short hand flag for --file"};

// Format Options
Option<bool> OPTIONS::Format{"--format",
                             "When this flag is set, the output will be in a "
                             "format that is easier to read"};
Option<bool> OPTIONS::ShortFormat{"-FM", "Short hand flag for --format"};

// Format Print Options
Option<bool> OPTIONS::FormatPrint{
    "--format-print", "When this flag is set, the output will be printed to "
                      "the console in a format that is easier to read"};
Option<bool> OPTIONS::ShortFormatPrint{"-FMP",
                                       "Short hand flag for --format-print"};

// Output File Options
Option<std::string> OPTIONS::OutputFile{
    "--out", "Use --out=<filename.fg> to specify an output file"};
Option<std::string> OPTIONS::ShortOutputFile{"-O", "Short hand flag for --out"};

// Code Options
Option<std::string> OPTIONS::Code{
    "--code", "Use --code=<code> to specify a code as input"};
Option<std::string> OPTIONS::ShortCode{"-C", "Short hand flag for --code"};

// Optimization Options
Option<int> OPTIONS::OptimizationLevel0{"-O0", "No optimization"};
Option<int> OPTIONS::OptimizationLevel1{"-O1", "Optimize for speed"};
Option<int> OPTIONS::OptimizationLevel2{"-O2", "Further optimize for speed"};
Option<int> OPTIONS::OptimizationLevel3{"-O3", "Full optimization"};

// Library Path Option
Option<std::string> OPTIONS::LibraryPath{
    "-L", "Specify the path to library directories"};

// Linking Library Option
Option<std::string> OPTIONS::LinkLibrary{"-l",
                                         "Specify libraries to link with"};

// Framework Option
Option<std::string> OPTIONS::Framework{"-framework",
                                       "Specify frameworks to link with"};

// Entry Point
Option<std::string> OPTIONS::EntryPoint{"-e",
                                        "Specify the entry point function"};

} // namespace FlowWingCliOptions
