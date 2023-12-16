#include "CodeGenerationContext.h"

CodeGenerationContext ::CodeGenerationContext(
    DiagnosticHandler *diagnosticHandler, const std::string sourceFileName)
    : _sourceFileName(sourceFileName) {
  _context = std::make_unique<llvm::LLVMContext>();
  _builder = std::make_unique<llvm::IRBuilder<>>(*_context);
  _module = std::make_unique<llvm::Module>("FlowWing", *_context);

  _sourceFileName = sourceFileName;

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

  // Assign diagnosticHandler
  _diagnosticHandler = diagnosticHandler;

  // Initialize
  _typeMapper = std::make_unique<TypeMapper>(_context.get(), _builder.get());

  // Initialize  LLVM_Logger
  _llvmLogger = std::make_unique<LLVMLogger>(diagnosticHandler);

  // Initialize the named value chain
  _namedValueChain = std::make_unique<ValueChain>();
  _namedValueChain->addHandler(new NamedValueTable());

  // Initialize the alloca chain
  _allocaChain = std::make_unique<AllocaChain>();
  _allocaChain->addHandler(new AllocaTable());

  // Initialize the dynamic type
  _dynamicType = std::make_unique<StructTypeBuilder>(this);
  _dynamicType->buildType();
};

std::unique_ptr<llvm::IRBuilder<>> &CodeGenerationContext::getBuilder() {
  return _builder;
}

std::unique_ptr<llvm::Module> &CodeGenerationContext::getModule() {
  return _module;
}

std::unique_ptr<llvm::LLVMContext> &CodeGenerationContext::getContext() {
  return _context;
}

std::unique_ptr<TypeMapper> &CodeGenerationContext::getMapper() {
  return _typeMapper;
}

std::unique_ptr<LLVMLogger> &CodeGenerationContext::getLogger() {
  return _llvmLogger;
}

std::string CodeGenerationContext::getPrefixedName(std::string name) {
  return this->_sourceFileName + "_" + name;
}

const std::string &CodeGenerationContext::getSourceFileName() const {
  return this->_sourceFileName;
}

DiagnosticHandler *CodeGenerationContext::getDiagnosticHandler() const {
  return _diagnosticHandler;
}

std::unique_ptr<ValueChain> &CodeGenerationContext::getNamedValueChain() {
  return _namedValueChain;
}

std::unique_ptr<AllocaChain> &CodeGenerationContext::getAllocaChain() {
  return _allocaChain;
}

std::unique_ptr<StructTypeBuilder> &CodeGenerationContext::getDynamicType() {
  return _dynamicType;
}

std::stack<std::pair<Utils::type, int8_t>> &
CodeGenerationContext::getReturnAllocaStack() {
  return _returnAllocaStack;
}

std::map<std::string, BoundFunctionDeclaration *> &
CodeGenerationContext::getBoundedUserFunctions() {
  return _boundedUserFunctions;
}

std::unordered_map<std::string, uint64_t> &
CodeGenerationContext::getGlobalTypeMap() {
  return _globalTypeMap;
}

void CodeGenerationContext::addBoundedUserFunction(
    std::string name, BoundFunctionDeclaration *functionDeclaration) {
  _boundedUserFunctions[name] = functionDeclaration;
}
std::unordered_map<std::string, int8_t> &
CodeGenerationContext::getRecursiveFunctionsMap() {
  return _recursiveFunctionsMap;
}

llvm::Value *CodeGenerationContext::isCountZero(const std::string name,
                                                llvm::Type *ty) {
  return _builder->CreateICmpEQ(
      _builder->CreateLoad(ty, _module->getGlobalVariable(name)),
      llvm::ConstantInt::get(*_context, llvm::APInt(32, 0, true)));
}

void CodeGenerationContext::decrementCountIfNotZero(const std::string name) {

  llvm::BasicBlock *currentBlock = _builder->GetInsertBlock();
  llvm::BasicBlock *decrementBlock = llvm::BasicBlock::Create(
      *_context, "decrement_block", currentBlock->getParent());
  llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(
      *_context, "end_block", currentBlock->getParent());

  llvm::Value *isZero = isCountZero(name, llvm::Type::getInt32Ty(*_context));
  _builder->CreateCondBr(isZero, endBlock, decrementBlock);

  _builder->SetInsertPoint(decrementBlock);
  llvm::Value *count = _builder->CreateLoad(llvm::Type::getInt32Ty(*_context),
                                            _module->getGlobalVariable(name));

  llvm::Value *newCount = _builder->CreateSub(
      count, llvm::ConstantInt::get(*_context, llvm::APInt(32, 1, true)));
  _builder->CreateStore(newCount, _module->getGlobalVariable(name));
  _builder->CreateBr(endBlock);

  _builder->SetInsertPoint(endBlock);
}

void CodeGenerationContext::incrementCount(const std::string name) {
  llvm::Value *count = _builder->CreateLoad(llvm::Type::getInt32Ty(*_context),
                                            _module->getGlobalVariable(name));
  llvm::Value *newCount = _builder->CreateAdd(
      count, llvm::ConstantInt::get(*_context, llvm::APInt(32, 1, true)));
  _builder->CreateStore(newCount, _module->getGlobalVariable(name));
}

llvm::Constant *
CodeGenerationContext::createConstantFromValue(llvm::Value *myValue) {
  llvm::Type *valueType = myValue->getType();

  if (auto constant = llvm::dyn_cast<llvm::Constant>(myValue)) {
    return constant;
  }

  if (auto callInst = llvm::dyn_cast<llvm::CallInst>(myValue)) {

    this->getLogger()->LogError("Unsupported type for conversion to constant");
    return nullptr;
  }

  if (valueType->isIntegerTy(32)) {
    if (auto intConstant = llvm::dyn_cast<llvm::ConstantInt>(myValue)) {
      llvm::APInt intValue = intConstant->getValue();
      return llvm::ConstantInt::get(valueType, intValue);
    }
  } else if (valueType->isFloatTy() || valueType->isDoubleTy()) {
    if (auto floatConstant = llvm::dyn_cast<llvm::ConstantFP>(myValue)) {
      llvm::APFloat floatValue = floatConstant->getValueAPF();
      return llvm::ConstantFP::get(*_context, floatValue);
    }
  } else if (valueType->isPointerTy()) {
    if (auto ptrConstant = llvm::dyn_cast<llvm::ConstantPointerNull>(myValue)) {
      return llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(valueType));
    } else if (auto constArray =
                   llvm::dyn_cast<llvm::ConstantDataArray>(myValue)) {
      if (constArray->isCString()) {
        std::string str = constArray->getAsCString().str();
        llvm::Constant *strConstant =
            llvm::ConstantDataArray::getString(*_context, str, true);
        return strConstant;
      }
    }
  } else if (valueType->isIntegerTy(1)) { // Check if it's a boolean (i1).
    if (auto boolConstant = llvm::dyn_cast<llvm::ConstantInt>(myValue)) {
      return llvm::ConstantInt::get(valueType,
                                    boolConstant->getUniqueInteger());
    }
  }
  // Add more cases for other types if needed.

  // this->logError("Unsupported type for conversion to constant");

  return nullptr; // Return nullptr if the type is not recognized.
}

void CodeGenerationContext::callREF(const std::string &error) {
  // _llvmLogger->increaseErrorCount();
  _builder->CreateCall(
      _module->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
      {_builder->CreateGlobalStringPtr(this->getLogger()->getLLVMErrorMsg(
          error, this->getLogger()->getCurrentSourceLocation()))});
}
