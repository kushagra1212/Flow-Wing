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

#include "Compiler.h"
#include "src/ASTBuilder/ASTBuilder.h"
#include "src/IR/IRGenerator.h"
#include "src/SemanticAnalyzer/SemanticAnalyzer.h"
#include "src/common/commandLineOptions/commandLineOptions.h"
#include "src/compiler/CompilerUtils.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/Colors.h"
#include "src/utils/Utils.h"
#include <fstream>

Compiler::Compiler(std::string filePath)
    : _filePath(filePath),
      llFileSaveStrategy(std::make_unique<LLFileSaveStrategy>(nullptr)),
      _currentDiagnosticHandler(
          std::make_unique<FlowWing::DiagnosticHandler>(filePath)),
      executionEngine(nullptr) {

  if (FlowWing::Cli::cmdl && (FlowWing::Cli::isParam::outputFile() ||
                              FlowWing::Cli::isParam::shortOutputFile())) {
    _outputFilePath = (FlowWing::Cli::isParam::outputFile()
                           ? FlowWing::Cli::Get::outputFile()
                           : FlowWing::Cli::Get::shortOutputFile());
  }
}

void Compiler::compile(std::vector<std::string> &text,
                       std::ostream &outputStream) {
  std::unique_ptr<FlowWing::DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<FlowWing::DiagnosticHandler>(
          Utils::getAbsoluteFilePath(this->_filePath));

  currentDiagnosticHandler->setOutputFilePath(_outputFilePath);
  FlowWing::Compiler::logNoErrorJSONIfAsked(_outputFilePath);
  std::unique_ptr<ASTBuilder> parser =
      std::make_unique<ASTBuilder>(text, currentDiagnosticHandler.get());

  if (Utils::getExtension(_outputFilePath) == ".json") {
    JSON jsonObject = Utils::outJSON(parser->getTokenListRef());
    Utils::logJSON(jsonObject, _outputFilePath.substr(
                                   0, _outputFilePath.find_last_of(".")) +
                                   ".tokens.json");
  }

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        std::cerr, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(
        new FlowWing::DiagnosticHandler(this->_filePath));
    return;
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      (parser->createCompilationUnit());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Syntactic)) {
    currentDiagnosticHandler->logDiagnostics(
        std::cerr, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });
    currentDiagnosticHandler.reset(
        new FlowWing::DiagnosticHandler(this->_filePath));

    return;
  }

#ifdef DEBUG

  std::cout << BLUE << ".............." << YELLOW << "Tree Start" << BLUE
            << ".............." << RESET << std::endl;
  Utils::prettyPrint(compilationUnit.get());
  std::cout << BLUE << ".............." << YELLOW << " Tree End " << BLUE
            << " .............." << RESET << std::endl;

#endif
  if (Utils::getExtension(_outputFilePath) == ".json") {
    JSON jsonObject = Utils::outJSON(compilationUnit.get());
    Utils::logJSON(jsonObject, _outputFilePath);
  }
  std::unique_ptr<BoundGlobalScope> globalScope =
      (SemanticAnalyzer::analyzeGlobalScope(nullptr, compilationUnit.get(),
                                            currentDiagnosticHandler.get()));

  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        std::cerr, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(
        new FlowWing::DiagnosticHandler(this->_filePath));

    return;
  }

#ifdef DEBUG

  std::cout << BLUE << ".............." << YELLOW << "Tree Start" << BLUE
            << ".............." << RESET << std::endl;
  Utils::prettyPrint(globalScope->globalStatement.get());
  std::cout << BLUE << ".............." << YELLOW << " Tree End " << BLUE
            << " .............." << RESET << std::endl;

#endif

  if (Utils::getExtension(_outputFilePath) == ".json") {
    //! Disable for now
    // JSON jsonObject = Utils::outJSON(globalScope->globalStatement.get(),
    // false); Utils::logJSON(jsonObject, _outputFilePath);

  } else if (FlowWing::Cli::isFlag::format() ||
             FlowWing::Cli::isFlag::shortFormat()) {
    //? format and Save to file
    std::ofstream file(currentDiagnosticHandler->getAbsoluteFilePath(),
                       std::ios::out);

    // Check if the file is opened successfully
    if (!file.is_open()) {
      _currentDiagnosticHandler->printDiagnostic(
          std::cerr,
          Diagnostic(
              "Error opening file: formatting failed " +
                  currentDiagnosticHandler->getAbsoluteFilePath(),
              DiagnosticUtils::DiagnosticLevel::Error,
              DiagnosticUtils::DiagnosticType::Linker,
              DiagnosticUtils::SourceLocation(
                  0, 0, 0, currentDiagnosticHandler->getAbsoluteFilePath())));
      return;
    }

    // Replace the content of the file with text
    file << parser->getFormattedSourceCode();
    return;
  } else if (FlowWing::Cli::isFlag::formatPrint() ||
             FlowWing::Cli::isFlag::ShortFormatPrint()) {
    std::cout << parser->getFormattedSourceCode() << std::endl;
    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions, _outputFilePath);

    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());

    if (!_evaluator->hasErrors()) {
      FlowWing::Compiler::logNoErrorJSONIfAsked(_outputFilePath);

      this->execute();
    }
    outputStream << std::endl;
  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void Compiler::runTests([[maybe_unused]] std::istream &inputStream,
                        std::ostream &outputStream) {
  std::unique_ptr<FlowWing::DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<FlowWing::DiagnosticHandler>();

  std::unique_ptr<ASTBuilder> parser =
      std::make_unique<ASTBuilder>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(
        new FlowWing::DiagnosticHandler(this->_filePath));
    return;
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      (parser->createCompilationUnit());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Syntactic)) {

    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });

    currentDiagnosticHandler.reset(
        new FlowWing::DiagnosticHandler(this->_filePath));

    return;
  }

  std::unique_ptr<BoundGlobalScope> globalScope =
      (SemanticAnalyzer::analyzeGlobalScope(nullptr, compilationUnit.get(),
                                            currentDiagnosticHandler.get()));

  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(
        new FlowWing::DiagnosticHandler(this->_filePath));

    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions, _outputFilePath);
    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());

    if (!_evaluator->hasErrors()) {
      this->execute();
    }
  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}
