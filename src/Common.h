#ifndef COMMON_H
#define COMMON_H
#include <algorithm>
#include <any>
#include <chrono>
#include <csignal>
#include <cstdlib> // For malloc
#include <cstring> // For strlen and memcpy
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

// ANSI color codes
constexpr auto RESET = "\033[0m";
constexpr auto RED = "\033[31m";
constexpr auto GREEN = "\033[32m";
constexpr auto YELLOW = "\033[33m";
constexpr auto BLUE = "\033[34m";
constexpr auto RED_TEXT = "\033[1;31m";
constexpr auto YELLOW_TEXT = "\033[1;33m";
constexpr auto GREEN_TEXT = "\033[1;32m";
constexpr auto BLUE_TEXT = "\033[1;34m";
#endif
