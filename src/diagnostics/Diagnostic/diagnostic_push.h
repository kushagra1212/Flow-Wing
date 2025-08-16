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

/*
 * This header is intended to be included multiple times.
 * It does not have a #pragma once guard.
 *
 * It is used to temporarily disable specific warnings that are
 * common in third-party libraries, ensuring a clean build.
 */

#if defined(_MSC_VER)
// Microsoft Visual C++
#pragma warning(push)
// Disables warnings about data conversion that could lose data (e.g., uint64_t
// to unsigned int)
#pragma warning(disable : 4244)
// Disables warnings about a local variable hiding a class member
#pragma warning(disable : 4458)


#pragma warning(disable : 4100) // Unreferenced formal parameter
#pragma warning(disable : 4146) // Unary minus operator applied to unsigned type
#pragma warning(disable : 4245) // Conversion, signed/unsigned mismatch
#pragma warning(disable : 4267) // Conversion from 'size_t' to 'type', possible loss of data

#pragma warning(disable : 4324) // Structure was padded due to alignment specifier

#pragma warning(disable : 4127) // Conditional expression is constant
#pragma warning(disable : 4310) // Cast truncates constant value

#pragma warning(disable : 24624) // Truncation from 'type1' to 'type2'

#pragma warning(disable : 4624) // Conversion from 'type1' to 'type2', possible loss of data


#elif defined(__clang__)
// GCC and Clang
#pragma clang diagnostic push
// Disables warnings about data conversion (the equivalent of MSVC's 4244)
#pragma clang diagnostic ignored "-Wconversion"
// Disables warnings about variable shadowing (the equivalent of MSVC's 4458)
#pragma clang diagnostic ignored "-Wshadow"
// Disables warnings about unused function parameters
#pragma clang diagnostic ignored "-Wunused-parameter"

#pragma clang diagnostic ignored "-Wfloat-conversion"

#pragma clang diagnostic ignored "-Wunreachable-code"

#endif