#include "commandLineOptions.h"

namespace FlowWingCliOptions {
Option<bool> OPTIONS::Version{"--version",
                              "When this flag is set, Version will be "
                              "printed"};

Option<bool> OPTIONS::ShortVersion{"-V", "Short hand flag for --version"};

//! File
Option<std::string> OPTIONS::File{
    "--file", "Use --file=<filename.fg/filePath.fg> to specify a file"};
Option<std::string> OPTIONS::ShortFile{"-F", "Short hand Arg for --file"};

//! Format
Option<bool> OPTIONS::Format{"--format",
                             "When this flag is set, the output will "
                             "be in a format that is easier to read"};

Option<bool> OPTIONS::ShortFormat{"-FM", "Short hand flag for --format"};

//! Format Print Cout
Option<bool> OPTIONS::FormatPrint{
    "--format-print", "When this flag is set, the output will be printed to "
                      "the console in a format that is easier to read"};

Option<bool> OPTIONS::ShortFormatPrint{"-FMP",
                                       "Short hand flag for --format-print"};

Option<std::string> OPTIONS::OutputFile{
    "--out", "Use --out=<filename.fg> to specify an output file"};

Option<std::string> OPTIONS::ShortOutputFile{"-O", "Short hand flag for --out"};

} // namespace FlowWingCliOptions