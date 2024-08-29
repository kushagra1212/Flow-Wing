#include "BoolTypeConverter.h"

BoolTypeConverter::BoolTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *BoolTypeConverter::convertExplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateICmpNE(value,
                                  llvm::ConstantInt::get(value->getType(), 0));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return _builder->CreateFCmpONE(
        value, llvm::ConstantFP::get(_builder->getDoubleTy(), 0.0));
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return _builder->CreateFCmpONE(
        value, llvm::ConstantFP::get(_builder->getFloatTy(), 0.0));
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {

    llvm::BasicBlock *currentBlock = _builder->GetInsertBlock();
    llvm::BasicBlock *nullBlock =
        llvm::BasicBlock::Create(value->getContext(), "BoolTC::NullBlock",
                                 _builder->GetInsertBlock()->getParent());
    llvm::BasicBlock *notNullBlock =
        llvm::BasicBlock::Create(value->getContext(), "BoolTC::NotNullBlock",
                                 _builder->GetInsertBlock()->getParent());
    llvm::BasicBlock *mergeBlock =
        llvm::BasicBlock::Create(value->getContext(), "BoolTC::MergeBlock",
                                 _builder->GetInsertBlock()->getParent());

    _builder->CreateCondBr(_builder->CreateIsNull(value), nullBlock,
                           notNullBlock);

    _builder->SetInsertPoint(nullBlock);

    llvm::Value *resultFromNullBlock = _builder->getFalse();

    _builder->CreateBr(mergeBlock);

    _builder->SetInsertPoint(notNullBlock);
    std::unique_ptr<StringTypeConverter> stringConverter =
        std::make_unique<StringTypeConverter>(this->_codeGenerationContext);

    llvm::Value *strLen = _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_LENGTH),
        {stringConverter->convertExplicit(value)});

    llvm::Value *strLenIsZero =
        _builder->CreateICmpEQ(strLen, _builder->getInt32(0));

    llvm::Value *resultFromNotNullBlock = _builder->CreateSelect(
        strLenIsZero, llvm::ConstantInt::get(_builder->getInt1Ty(), 0),
        llvm::ConstantInt::get(_builder->getInt1Ty(), 1));

    _builder->CreateBr(mergeBlock);

    _builder->SetInsertPoint(mergeBlock);
    llvm::PHINode *conditionPHI = _builder->CreatePHI(_builder->getInt1Ty(), 2);
    conditionPHI->addIncoming(resultFromNullBlock, nullBlock);
    conditionPHI->addIncoming(resultFromNotNullBlock, notNullBlock);

    return conditionPHI;
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to bool"));

  return nullptr;
}

llvm::Value *BoolTypeConverter::convertImplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    this->_logger->LogError(("Implicit conversion from int32 to bool is not "
                             "supported for variable with predefined type"));
  }
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    this->_logger->LogError(("Implicit conversion from int64 to bool is not "
                             "supported for variable with predefined type"));
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    this->_logger->LogError(("Implicit conversion from int8 to bool is not "
                             "supported for variable with predefined type"));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    this->_logger->LogError(("Implicit conversion from deci to bool "
                             "is not supported for variable with "
                             "predefined type"));
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    this->_logger->LogError(("Implicit conversion from deci32 to bool "
                             "is not supported for variable with "
                             "predefined type"));
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    this->_logger->LogError(("Implicit conversion from string to bool is "
                             "not supported for variable with predefined "
                             "type"));
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to bool"));

  return res;
}