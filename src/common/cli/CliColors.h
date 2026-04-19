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

constexpr auto RESET = "\033[0m"; // Reset all colors

constexpr auto RED_TEXT = "\033[1;31m";
constexpr auto YELLOW_TEXT = "\033[1;33m";
constexpr auto GREEN_TEXT = "\033[1;32m";
constexpr auto BLUE_TEXT = "\033[1;34m";
constexpr auto WHITE_TEXT = "\033[1;37m";

constexpr auto BOLD_TEXT = "\033[1m";

constexpr auto ERROR_TEXT = RED_TEXT;
constexpr auto WARNING_TEXT = YELLOW_TEXT;
constexpr auto SUCCESS_TEXT = GREEN_TEXT;
constexpr auto INFO_TEXT = WHITE_TEXT;
constexpr auto DEBUG_TEXT = BLUE_TEXT;

constexpr auto HIGHLIGHT_TEXT = YELLOW_TEXT;

constexpr auto CLEAR_COLOR = RESET;

constexpr auto GRAY_TEXT = "\033[0;37m";