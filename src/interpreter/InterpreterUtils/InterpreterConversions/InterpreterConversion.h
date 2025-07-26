/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#pragma once

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
