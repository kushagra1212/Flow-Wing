#ifndef __FLOWWING_BRING_STATEMENT_STRATEGY_H__
#define __FLOWWING_BRING_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundBringStatement/BoundBringStatement.h"
#include "../../../../utils/Utils.h"
#include "../ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "../CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../ModuleStatementGenerationStrategy/ModuleStatementGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"
#include "../VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"
class BringStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  BringStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
  llvm::Value *declare(BoundStatement *statement);
  auto inline deleteObjectFiles() -> void {
    std::vector<std::string> objectFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, ".o", false);
    for (const auto &objectFile : objectFiles) {
      std::filesystem::remove(objectFile);
    }
  }
};

#endif //__FLOWWING_BRING_STATEMENT_STRATEGY_H__
