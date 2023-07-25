#include "../Utils.h"
using namespace Utils;
FunctionSymbol ConversionFunctions::Int32 =
    FunctionSymbol("Int32",
                   std::vector<FunctionParameterSymbol>({
                       FunctionParameterSymbol("value", false),
                   }),
                   type::INT);

FunctionSymbol ConversionFunctions::Double =
    FunctionSymbol("Double",
                   std::vector<FunctionParameterSymbol>({
                       FunctionParameterSymbol("value", false),
                   }),
                   type::DOUBLE);

FunctionSymbol ConversionFunctions::String =
    FunctionSymbol("String",
                   std::vector<FunctionParameterSymbol>({
                       FunctionParameterSymbol("value", false),
                   }),
                   type::STRING);

FunctionSymbol ConversionFunctions::Bool =
    FunctionSymbol("Bool",
                   std::vector<FunctionParameterSymbol>({
                       FunctionParameterSymbol("value", false),
                   }),
                   type::BOOL);
