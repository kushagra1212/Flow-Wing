#ifndef INTERPRETERCONVERSION_H
#define INTERPRETERCONVERSION_H
#include "../../../utils/Utils.h"
#include <any>
#include <string>

class InterpreterConversion {

public:
  static std::string explicitConvertAnyToString(const std::any value);
  static std::string explicitConvertIntToString(const int value);
  static std::string explicitConvertDoubleToString(const double value);
  static std::string explicitConvertBoolToString(const bool value);

  static double explicitConvertToAnyToDouble(const std::any value);
  static double implicitConvertIntToDouble(const int value);
  static double implicitConvertBoolToDouble(const bool value);
  static double explicitConvertStringToDouble(const std::string value);

  static int explicitConvertAnyToInt(const std::any value);
  static int explicitConvertDoubleToInt(const double value);
  static int explicitConvertBoolToInt(const bool value);
  static int explicitConvertStringToInt(const std::string value);

  static bool explicitConvertAnyToBool(const std::any value);
  static bool explicitConvertIntToBool(const int value);
  static bool explicitConvertDoubleToBool(const double value);
  static bool explicitConvertStringToBool(const std::string value);
};

#endif // INTERPRETERCONVERSION_H