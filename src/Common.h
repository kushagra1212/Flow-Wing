#ifndef COMMON_H
#define COMMON_H
#include <algorithm>
#include <any>
#include <chrono>
#include <csignal>
#include <cstdlib>  // For malloc
#include <cstring>  // For strlen and memcpy
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// TODO: Add support for Windows
// #include <windows.h>
#include <unistd.h>

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
#endif
