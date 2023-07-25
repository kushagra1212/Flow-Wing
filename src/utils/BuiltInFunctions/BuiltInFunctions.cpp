#include "../Utils.h"

std::vector<Utils::FunctionSymbol> Utils::BuiltInFunctions::getAllFunctions() {
  return std::vector<FunctionSymbol>({print, random, input});
}

Utils::FunctionSymbol
Utils::BuiltInFunctions::getFunctionSymbol(std::string name) {
  for (FunctionSymbol function : getAllFunctions()) {
    if (function.name == name) {
      return function;
    }
  }
  return FunctionSymbol();
}
Utils::FunctionSymbol Utils::BuiltInFunctions::input =
    FunctionSymbol("input",
                   std::vector<FunctionParameterSymbol>({
                       FunctionParameterSymbol("prompt", false),
                   }),
                   type::STRING);

Utils::FunctionSymbol Utils::BuiltInFunctions::random =
    FunctionSymbol("random", std::vector<FunctionParameterSymbol>(), type::INT);
Utils::FunctionSymbol Utils::BuiltInFunctions::print =
    FunctionSymbol("print",
                   std::vector<FunctionParameterSymbol>({
                       FunctionParameterSymbol("value", false),
                   }),
                   type::VOID);