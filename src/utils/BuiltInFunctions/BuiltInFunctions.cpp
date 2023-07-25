#include "../Utils.h"

std::vector<Utils::FunctionSymbol> Utils::BuiltInFunctions::getAllFunctions() {
  return std::vector<FunctionSymbol>(
      {print, random, input, String, Int32, Double, Bool});
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

Utils::FunctionSymbol Utils::BuiltInFunctions::random = FunctionSymbol(
    "random", std::vector<FunctionParameterSymbol>(), type::INT32);
Utils::FunctionSymbol Utils::BuiltInFunctions::print =
    FunctionSymbol("print",
                   std::vector<FunctionParameterSymbol>({
                       FunctionParameterSymbol("value", false),
                   }),
                   type::VOID);

Utils::FunctionSymbol Utils::BuiltInFunctions::Int32 =
    FunctionSymbol("Int32",
                   std::vector<Utils::FunctionParameterSymbol>({
                       Utils::FunctionParameterSymbol("value", false),
                   }),
                   type::INT32);

Utils::FunctionSymbol Utils::BuiltInFunctions::Double =
    FunctionSymbol("Double",
                   std::vector<Utils::FunctionParameterSymbol>({
                       Utils::FunctionParameterSymbol("value", false),
                   }),
                   type::DOUBLE);

Utils::FunctionSymbol Utils::BuiltInFunctions::String =
    FunctionSymbol("String",
                   std::vector<Utils::FunctionParameterSymbol>({
                       Utils::FunctionParameterSymbol("value", false),
                   }),
                   type::STRING);

Utils::FunctionSymbol Utils::BuiltInFunctions::Bool =
    FunctionSymbol("Bool",
                   std::vector<Utils::FunctionParameterSymbol>({
                       Utils::FunctionParameterSymbol("value", false),
                   }),
                   type::BOOL);