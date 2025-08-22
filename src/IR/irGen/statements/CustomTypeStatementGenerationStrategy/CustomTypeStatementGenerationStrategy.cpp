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

#include "CustomTypeStatementGenerationStrategy.h"

#include "src/IR/irGen/LLVMTypeGeneration/LLVMTypeGenerationStrategy.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

CustomTypeStatementGenerationStrategy::CustomTypeStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *CustomTypeStatementGenerationStrategy::generateStatement(
    [[maybe_unused]] BoundStatement *expression) {
  return nullptr;
}

llvm::Value *CustomTypeStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}

llvm::Value *CustomTypeStatementGenerationStrategy::generateCustomType(
    BoundStatement *statement) {
  BoundCustomTypeStatement *boundCustomTypeStatement =
      static_cast<BoundCustomTypeStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundCustomTypeStatement->getLocation());

  std::vector<llvm::Type *> structElements = {};
  int64_t index = 0;

  const std::string KEY_PRIFIX =
      boundCustomTypeStatement->getTypeNameAsString();

  for (auto &[boundLiteralExpression, bTE] :
       boundCustomTypeStatement->getKeyPairs()) {
    const std::string propertyName =
        std::any_cast<std::string>(boundLiteralExpression->getValue());

    llvm::Type *type = _typeGenerationFactory->createStrategy(bTE->getKind())
                           ->getType(bTE.get());

    const std::string key = KEY_PRIFIX + "." + propertyName;

    structElements.push_back(type);
    _codeGenerationContext->_typesMap[key] = FlowWing::Type::TypeBuilder()
                                                 .setName(key)
                                                 .setType(type)
                                                 .setIndex((index))
                                                 .build();

    index++;
  }
  DEBUG_LOG("CustomType Statement",
            "Declaring CustomType: " +
                boundCustomTypeStatement->getTypeNameAsString());
  llvm::StructType *structType =
      llvm::StructType::create(*TheContext, structElements,
                               boundCustomTypeStatement->getTypeNameAsString());

  DEBUG_LOG("CustomType Statement",
            "Declaring CustomType: " + structType->getStructName().str());
  _codeGenerationContext
      ->_typesMap[boundCustomTypeStatement->getTypeNameAsString()] =
      FlowWing::Type::TypeBuilder()
          .setName(boundCustomTypeStatement->getTypeNameAsString())
          .setType(structType)
          .setCustomType(boundCustomTypeStatement)
          .build();

  return nullptr;
}

// llvm::Type *CustomTypeStatementGenerationStrategy::getType(
//     BoundTypeExpression *bTE) {
//   switch (bTE->getKind()) {
//     case BinderKindUtils::BoundObjectTypeExpression: {
//       //! Might Have to Revert it
//       // BoundObjectTypeExpression *bOT =
//       //     static_cast<BoundObjectTypeExpression *>(bTE);

//       // BoundLiteralExpression<std::any> *bLE =
//       //     bOT->getObjectTypeIdentifier().get();

//       // _codeGenerationContext->getLogger()->setCurrentSourceLocation(
//       //     bOT->getLocation());
//       // std::string typeName = std::any_cast<std::string>(bLE->getValue());

//       // llvm::StructType *type = nullptr;
//       // if (_codeGenerationContext->_classTypes.find(typeName) !=
//       //     _codeGenerationContext->_classTypes.end()) {

//       //   type =
//       _codeGenerationContext->_classTypes[typeName]->getClassType();
//       // } else if ((_codeGenerationContext->getFlowWingType(typeName)
//       //                 .getStructType())) {

//       //   type =
//       (_codeGenerationContext->_typesMap[typeName].getStructType());
//       // } else {
//       //   _codeGenerationContext->getLogger()->LogError(
//       //       "Expected an object type," +
//       Utils::getActualTypeName(typeName));
//       //   return nullptr;
//       // }

//       // if (!type) {
//       //   _codeGenerationContext->getLogger()->LogError(
//       //       "Expected an object type, " +
//       Utils::getActualTypeName(typeName)
//       //       + " in type statement ");

//       //   return nullptr;
//       // }

//       // if (!type) {
//       //   _codeGenerationContext->getLogger()->LogError(
//       //       "Type " + typeName + " is not defined in Type Statement" +
//       //       Utils::getActualTypeName(typeName));

//       //   return nullptr;
//       // }
//       // return type;
//       // break;
//     }
//     default: {
//       _codeGenerationContext->getLogger()->LogError(
//           "Invalid type expression in type statement");

//       return nullptr;
//     }
//   }
// }
