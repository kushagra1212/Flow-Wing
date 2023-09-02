#include "JITCompiler.h"

JITCompiler::JITCompiler() {}

JITCompiler::~JITCompiler() {}

void JITCompiler::compile(std::vector<std::string> &text,
                          std::ostream &outputStream) {
  // Initialize the JIT compiler with a new module

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>();

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler());
    return;
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Syntactic)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get(),
                                        currentDiagnosticHandler.get()));

  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions);

    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());
    _evaluator->executeGeneratedCode();

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void JITCompiler::runTests(std::istream &inputStream,
                           std::ostream &outputStream) {

  std::string line;
  std::vector<std::string> text = std::vector<std::string>();
  while (std::getline(inputStream, line)) {
    text.push_back(line);
  }

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>();

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler());
    return;
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Syntactic)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get(),
                                        currentDiagnosticHandler.get()));

  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions);

    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());
    _evaluator->executeGeneratedCode();

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

#ifdef TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#else

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
    return 0;
  }

  // Opens the file using the provided file path
  std::ifstream file(argv[1]);

  // Check if the file was opened successfully
  if (!file.is_open()) {
    std::cerr << "Could not open the file." << std::endl;
    return 0;
  }

  std::string line;
  std::vector<std::string> text = std::vector<std::string>();
  while (std::getline(file, line)) {
    text.push_back(line);
  }
  // Close the file (imp)
  file.close();

  std::unique_ptr<JITCompiler> jitCompiler = std::make_unique<JITCompiler>();

  jitCompiler->compile(text, std::cout);

  return 0;
}

#endif
