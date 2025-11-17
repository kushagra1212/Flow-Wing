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

#include "src/common/cli/CliColors.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/LogConfig.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>

namespace flow_wing {
namespace debug {

inline void prettyPrintTokens(
    const std::vector<std::unique_ptr<syntax::SyntaxToken>> &tokens) {

  // Define column widths for alignment
  const int kKindTextWidth = 25;
  const int kTextWidth = 30;

  // Print headers
  std::cout << WHITE_TEXT << "\n----- Token Stream -----\n"
            << RESET << std::endl;
  std::cout << std::left << std::setw(kKindTextWidth) << "Token Kind"
            << std::left << std::setw(kTextWidth) << "Text" << RESET << "\n";
  std::cout << std::string(kKindTextWidth + kTextWidth, '-') << "\n";

  const char *random_colors[] = {RED_TEXT,   GREEN_TEXT, YELLOW_TEXT, BLUE_TEXT,
                                 WHITE_TEXT, GRAY_TEXT,  BOLD_TEXT};
  const int kRandomColorsSize =
      sizeof(random_colors) / sizeof(random_colors[0]);

  srand(static_cast<unsigned int>(time(NULL)));
  int random_index = std::rand() % kRandomColorsSize;
  // Print token data
  for (const auto &token : tokens) {
    // Ensure token text doesn't contain unescaped newlines that break
    // formatting
    std::string text_to_print = token->getText();
    size_t pos = text_to_print.find('\n');
    if (pos != std::string::npos) {
      text_to_print.replace(pos, 1, "\\n");
    }

    random_index = std::rand() % kRandomColorsSize;
    std::cout << random_colors[random_index] << std::left
              << std::setw(kKindTextWidth)
              << lexer::toString(token->getTokenKind()) << std::left
              << std::setw(kTextWidth) << text_to_print << RESET << "\n";
  }

  std::cout << std::string(kKindTextWidth + kTextWidth, '-') << "\n"
            << std::endl;
}

} // namespace debug
} // namespace flow_wing
