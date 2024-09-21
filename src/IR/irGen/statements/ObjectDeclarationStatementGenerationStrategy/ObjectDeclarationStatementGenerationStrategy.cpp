#include "ObjectDeclarationStatementGenerationStrategy.h"

#include "../../expressions/BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../../expressions/ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../../expressions/FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"
ObjectDeclarationStatementGenerationStrategy::
    ObjectDeclarationStatementGenerationStrategy(CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ObjectDeclarationStatementGenerationStrategy::declare() {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _objectTypeExpr->getLocation());

  llvm::StructType *structType =
      _codeGenerationContext->getFlowWingType(_objectTypeExpr->getTypeName())
          .getStructType();

  if (!structType && _codeGenerationContext->_classTypes.find(
                         _objectTypeExpr->getTypeName()) !=
                         this->_codeGenerationContext->_classTypes.end()) {
    structType =
        _codeGenerationContext->_classTypes[_objectTypeExpr->getTypeName()]
            ->getClassType();
  }

  if (!structType) {
    _codeGenerationContext->getLogger()->LogError(
        "Object type " +
        Utils::getActualTypeName(_objectTypeExpr->getTypeName()) +
        " not found");
    return nullptr;
  }
  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  llvm::Value *ptr = nullptr;

  if (_codeGenerationContext->isValidClassType(structType)) {
    ptr = _codeGenerationContext->createMemoryGetPtr(
        llvm::Type::getInt8PtrTy(*TheContext), _variableName,
        _isGlobal ? BinderKindUtils::MemoryKind::Global
                  : BinderKindUtils::MemoryKind::Stack);
  } else {
    ptr = _codeGenerationContext->createMemoryGetPtr(
        structType, _variableName, _variableDeclExpr->getMemoryKind());

    assignmentStrategy->initDefaultValue(structType, ptr, *Builder);
  }

  _variableDeclExpr->setLLVMVariable({ptr, structType});

  if (_initializer && _initializer->getKind() ==
                          BinderKindUtils::BoundNodeKind::CallExpression) {

    BoundCallExpression *callExpression =
        static_cast<BoundCallExpression *>(_initializer);
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        callExpression->getLocation());

    if (Utils::isClassInit(callExpression->getCallerNameRef())) {
      callExpression->setArgumentAlloca(
          callExpression->getArgumentsRef().size(), {ptr, structType});
    } else if (_codeGenerationContext->funcPtr(
                   callExpression->getCallerNameRef()) &&
               (_codeGenerationContext->funcPtr(
                    callExpression->getCallerNameRef()))
                   ->isHavingReturnTypeAsParamater()) {
      callExpression->setArgumentAlloca(0, {ptr, structType});
    }
  }

  CODEGEN_DEBUG_LOG("Declared Object: " + _variableName);
  return nullptr;
}

llvm::Value *ObjectDeclarationStatementGenerationStrategy::declareLocal(
    BoundStatement *statement) {

  initialize(statement, BinderKindUtils::MemoryKind::Stack);
  _isGlobal = false;
  return this->declare();
}
llvm::Value *ObjectDeclarationStatementGenerationStrategy::declareGlobal(
    BoundStatement *statement) {

  initialize(statement, BinderKindUtils::MemoryKind::Global);
  _isGlobal = true;
  return this->declare();
}

llvm::Value *ObjectDeclarationStatementGenerationStrategy::assignExpression() {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableDeclExpr->getLocation());

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  auto [ptr, type] = _variableDeclExpr->getLLVMVariable();

  llvm::StructType *structType = llvm::cast<llvm::StructType>(type);

  // if (_codeGenerationContext->isValidClassType(structType)) {

  //   std::string className = (structType->getStructName().str());
  //   llvm::Value *init = nullptr;
  //   llvm::Value *classPtr = nullptr;

  //   if (_variableDeclExpr->getInitializerPtr().get() &&
  //       _variableDeclExpr->getInitializerPtr().get()->getKind() ==
  //           BinderKindUtils::CallExpression) {
  //     BoundCallExpression *callExpression = static_cast<BoundCallExpression
  //     *>(
  //         _variableDeclExpr->getInitializerPtr().get());

  //     if (callExpression->getCallerNameRef().find(
  //             FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init") !=
  //         std::string::npos) {
  //       className = callExpression->getCallerNameRef();

  //       className = className.substr(
  //           0, className.find(
  //                  FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
  //                  std::to_string(callExpression->getArgumentsRef().size())));

  //       if (_codeGenerationContext->_classTypes.find(className) !=
  //           _codeGenerationContext->_classTypes.end()) {

  //         classPtr = _codeGenerationContext->createMemoryGetPtr(
  //             _codeGenerationContext->_classTypes[className]->getClassType(),
  //             "", BinderKindUtils::MemoryKind::Heap);

  //         assignmentStrategy->initDefaultValue(
  //             _codeGenerationContext->_classTypes[className]->getClassType(),
  //             classPtr);

  //       } else {
  //         _codeGenerationContext->getLogger()->LogError("Class " + className
  //         +
  //                                                       " not found");
  //         return nullptr;
  //       }
  //     }
  //   }

  //   if (classPtr == nullptr) {
  //     classPtr = _codeGenerationContext->createMemoryGetPtr(
  //         _codeGenerationContext->_classTypes[className]->getClassType(),
  //         _variableName, BinderKindUtils::MemoryKind::Heap);

  //     assignmentStrategy->initDefaultValue(
  //         _codeGenerationContext->_classTypes[className]->getClassType(),
  //         classPtr);
  //   }

  //   if (_variableDeclExpr->getInitializerPtr().get() &&
  //       _variableDeclExpr->getInitializerPtr().get()->getKind() ==
  //           BinderKindUtils::CallExpression) {
  //     _codeGenerationContext->getValueStackHandler()->push(
  //         "", classPtr, "struct", structType);
  //   }
  //   {
  //     llvm::Value *ptrPtr = Builder->CreateStructGEP(
  //         _codeGenerationContext->_classTypes[className]->getClassType(),
  //         classPtr, 0);
  //     Builder->CreateStore(
  //         TheModule->getOrInsertGlobal(
  //             _codeGenerationContext->_classTypes[className]->getVTableName(),
  //             _codeGenerationContext->_classTypes[className]->getVTableType()),
  //         ptrPtr);

  //     _codeGenerationContext->_classTypes[className]->populateVTable(
  //         Builder, TheModule, TheContext, ptrPtr);
  //   }

  //   if (_variableDeclExpr->getInitializerPtr().get()) {
  //     init = assignmentStrategy->handleAssignExpression(
  //         classPtr, structType, _variableName,
  //         _variableDeclExpr->getInitializerPtr().get());
  //   }

  //   Builder->CreateStore(classPtr, ptr);
  //   _codeGenerationContext->getAllocaChain()->setPtr(_variableName,
  //                                                    {ptr, structType});

  //   if (!_initializer)
  //     return ptr;

  //   return init;
  // }

  _codeGenerationContext->getAllocaChain()->setPtr(_variableName,
                                                   {ptr, structType});

  if (!_initializer)
    return ptr;

  return assignmentStrategy->handleAssignExpression(
      ptr, structType, _variableName, _initializer);
}

void ObjectDeclarationStatementGenerationStrategy::initialize(
    BoundStatement *statement, BinderKindUtils::MemoryKind memoryKind) {
  _variableDeclExpr = static_cast<BoundVariableDeclaration *>(statement);

  // set memory kind
  if (_variableDeclExpr->getMemoryKind() == BinderKindUtils::MemoryKind::None) {
    _variableDeclExpr->setMemoryKind(memoryKind);
  }

  _variableName = _variableDeclExpr->getVariableName();
  _initializer = _variableDeclExpr->getInitializerPtr().get();
  _objectTypeExpr = static_cast<BoundObjectTypeExpression *>(
      _variableDeclExpr->getTypeExpression().get());
  _memoryKind = _variableDeclExpr->getMemoryKind();
}

llvm::Value *ObjectDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  initialize(statement);

  return this->assignExpression();
}

llvm::Value *
ObjectDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}
