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

// ANSI color codes
constexpr auto RESET = "\033[0m";
constexpr auto RED = "\033[31m";
constexpr auto GREEN = "\033[32m";
constexpr auto YELLOW = "\033[33m";
constexpr auto BLUE = "\033[34m";
constexpr auto RED_TEXT = "\033[1;31m";
constexpr auto YELLOW_TEXT = "\033[1;33m";
constexpr auto GREEN_TEXT = "\033[1;32m";
constexpr auto ORANGE_TEXT = "\033[1;33m";
constexpr auto BLUE_TEXT = "\033[1;34m";
constexpr auto PINK_TEXT = "\033[1;35m";
constexpr auto CYAN_TEXT = "\033[1;36m";
constexpr auto MAGENTA_TEXT = "\033[1;35m";
constexpr auto WHITE_TEXT = "\033[1;37m";
constexpr auto BLACK_TEXT = "\033[1;30m";
constexpr auto BRIGHT_RED = "\033[1;91m";
constexpr auto BRIGHT_GREEN = "\033[1;92m";
constexpr auto BRIGHT_YELLOW = "\033[1;93m";
constexpr auto BRIGHT_BLUE = "\033[1;94m";
constexpr auto GREY_TEXT = "\033[38;5;240m";
constexpr auto REVERSE = "\033[7m";
constexpr auto CLEAR_SCREEN = "\033[2J";
constexpr auto BOLD = "\033[1m";
constexpr auto UNDERLINE = "\033[4m";
constexpr auto CLEAR_LINE = "\033[2K";
constexpr auto CLEAR_LINE_AND_RESET = "\033[2K\r";
constexpr auto CLEAR_LINE_AND_RESET_AND_MOVE_UP = "\033[2K\r\033[F";
constexpr auto CLEAR_LINE_AND_RESET_AND_MOVE_UP_AND_RESET = "\033[2K\r\033[F\r";
constexpr auto CLEAR_LINE_AND_RESET_AND_MOVE_UP_AND_RESET_AND_MOVE_UP =
    "\033[2K\r\033[F\r\033[F";
constexpr auto ERROR_COLOR = RED_TEXT;
constexpr auto WARNING_COLOR = YELLOW_TEXT;
constexpr auto SUCCESS_COLOR = GREEN_TEXT;
constexpr auto INFO_COLOR = BLUE_TEXT;
constexpr auto BOLD_RED_TEXT = "\033[1;31m";
constexpr auto BOLD_GREEN_TEXT = "\033[1;32m";
constexpr auto BOLD_YELLOW_TEXT = "\033[1;33m";
constexpr auto BOLD_BLUE_TEXT = "\033[1;34m";
constexpr auto BOLD_WHITE_TEXT = "\033[1;37m";