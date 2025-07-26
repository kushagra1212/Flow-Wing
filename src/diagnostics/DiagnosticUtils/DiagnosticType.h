#pragma once

namespace DiagnosticUtils {
enum class DiagnosticType {
  Lexical,
  Syntactic,
  Semantic,
  CodeGen,
  Runtime,
  Linker,
  Fatal
};
}
