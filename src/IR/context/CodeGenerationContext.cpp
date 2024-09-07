#include "CodeGenerationContext.h"

CodeGenerationContext ::CodeGenerationContext(
    FLowWing::DiagnosticHandler *diagnosticHandler,
    const std::string sourceFileName)
    : _sourceFileName(sourceFileName) {
  _context = std::make_unique<llvm::LLVMContext>();
  _builder = std::make_unique<llvm::IRBuilder<>>(*_context);
  _module = std::make_unique<llvm::Module>(sourceFileName, *_context);

  _sourceFileName = sourceFileName;

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

#if defined(__APPLE__)
  _module->setTargetTriple(llvm::sys::getDefaultTargetTriple());
#elif defined(__LINUX__)
  _module->setTargetTriple(llvm::Triple::normalize("x86_64-unknown-linux-gnu"));
#endif

  //! TODO MOVE

  std::string Error;
  auto Target =
      llvm::TargetRegistry::lookupTarget(_module->getTargetTriple(), Error);

  if (Error.size() > 0) {
    this->_llvmLogger->LogError("Failed to lookup target: " + Error);
    exit(1);
    return;
  }

  auto CPU = "generic";
  auto Features = "";
  llvm::TargetOptions opt;
  _targetMachine =
      Target->createTargetMachine(_module->getTargetTriple(), CPU, Features,
                                  opt, std::optional<llvm::Reloc::Model>());

  _module->setDataLayout(_targetMachine->createDataLayout());
  //!

  // Assign diagnosticHandler
  _diagnosticHandler = diagnosticHandler;

  // Initialize
  _typeMapper = std::make_unique<TypeMapper>(_context.get(), _builder.get(),
                                             _module.get(), this);

  // Initialize  LLVM_Logger
  _llvmLogger = std::make_unique<LLVMLogger>(diagnosticHandler);

  // Initialize the named value chain
  _namedValueChain = std::make_unique<ValueChain>();
  _namedValueChain->addHandler(new NamedValueTable());

  // Initialize the alloca chain
  _allocaChain = std::make_unique<AllocaChain>();
  _allocaChain->addHandler(std::make_unique<AllocaTable>());

  // initialize the ArgsTypeHandler
  _argsTypeHandler = std::make_unique<ArgsTypeHandler>();

  // initialize the ReturnTypeHandler
  _returnTypeHandler = std::make_unique<ReturnTypeHandler>();

  //! Refactor this to a better place in future
  // Initialize the value stack handler
  _valueStackHandler = std::make_unique<ValueStackHandler>();

  // Initialize the dynamic type
  _dynamicType = std::make_unique<StructTypeBuilder>(this);
  _dynamicType->buildType();

  for (auto &function : BuiltInFunction::getBuiltInFunctions()) {
    _functionTypes[function->getFunctionNameRef()] =
        std::make_unique<FlowWing::Function>();

    _functionTypes[function->getFunctionNameRef()]->setFunctionName(
        function->getFunctionNameRef());
    _functionTypes[function->getFunctionNameRef()]->setReturnType(
        _typeMapper->mapCustomTypeToLLVMType(
            BuiltInFunction::getReturnType(function->getFunctionNameRef())),
        false);
  }
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

FLowWing::DiagnosticHandler *
CodeGenerationContext::getDiagnosticHandler() const {
  return _diagnosticHandler;
}

std::unique_ptr<ArgsTypeHandler> &CodeGenerationContext::getArgsTypeHandler() {
  return _argsTypeHandler;
}

std::unique_ptr<ReturnTypeHandler> &
CodeGenerationContext::getReturnTypeHandler() {
  return _returnTypeHandler;
}

std::unique_ptr<ValueChain> &CodeGenerationContext::getNamedValueChain() {
  return _namedValueChain;
}

std::unique_ptr<AllocaChain> &CodeGenerationContext::getAllocaChain() {
  return _allocaChain;
}

const std::unique_ptr<StructTypeBuilder> &
CodeGenerationContext::getDynamicType() {
  return _dynamicType;
}

std::stack<int8_t> &CodeGenerationContext::getReturnAllocaStack() {
  return _returnAllocaStack;
}
std::unordered_map<std::string, BoundFunctionDeclaration *> &
CodeGenerationContext::getBoundedUserFunctions() {
  return _boundedUserFunctions;
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

auto CodeGenerationContext::createVTableMapEntry(
    std::unordered_map<std::string,
                       std::tuple<llvm::FunctionType *, uint64_t, std::string>>
        &vTableElementsMap,
    std::string className, uint64_t &index) -> void {

  auto classVar = this->_classTypes[className];

  if (!classVar)
    return;

  if (classVar->hasParent()) {
    createVTableMapEntry(vTableElementsMap, classVar->getParentClassName(),
                         index);
  }

  for (auto &element : classVar->getClassMemberFunctionTypeMap()) {
    std::string fName = element.first;
    auto functionType = element.second;

    if (fName.find(".init") != std::string::npos)
      continue;

    fName = fName.substr(
        fName.find(FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX) + 1);

    if (vTableElementsMap.find(fName) == vTableElementsMap.end()) {

      std::get<1>(vTableElementsMap[fName]) = index;
      index++;
    }

    llvm::FunctionType *previousFunctionType =
        std::get<0>(vTableElementsMap[fName]);

    if (previousFunctionType) {
      if (previousFunctionType->getReturnType() !=
          functionType->getReturnType()) {
        this->getLogger()->LogError("Function " + fName +
                                    " has different return type in class " +
                                    className + " and its parent class " +
                                    classVar->getParentClassName());
        return;
      }

      if (previousFunctionType->getNumParams() !=
          functionType->getNumParams()) {
        this->getLogger()->LogError(
            "Function " + fName +
            " has different number of parameters in class " + className +
            " and its parent class " + classVar->getParentClassName());
        return;
      }

      for (int i = 0; i < functionType->getNumParams(); i++) {
        if (previousFunctionType->getParamType(i) !=
            functionType->getParamType(i)) {
          this->getLogger()->LogError(
              "Function " + fName + " has different parameter type in class " +
              className + " and its parent class " +
              classVar->getParentClassName());
          return;
        }
      }
    }

    std::get<0>(vTableElementsMap[fName]) = functionType;
    std::get<2>(vTableElementsMap[fName]) = className;
  }
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

void CodeGenerationContext::setMetadata(const std::string kind, llvm::Value *v,
                                        const std::string &metaData) {
  llvm::MDNode *metaNode = llvm::MDNode::get(
      *this->getContext(), llvm::MDString::get(*this->getContext(), metaData));

  // Add metadata to the instruction

  if (llvm::isa<llvm::GlobalVariable>(v)) {
    llvm::cast<llvm::GlobalVariable>(v)->setMetadata(kind, metaNode);
  } else if (llvm::isa<llvm::AllocaInst>(v)) {
    llvm::cast<llvm::AllocaInst>(v)->setMetadata(kind, metaNode);
  } else {
    this->getLogger()->LogError("Could not set metadata for " +
                                v->getName().str());
  }
}

void CodeGenerationContext::getMetaData(const std::string kind, llvm::Value *v,
                                        std::string &metaData) {

  if (!v) {
    return;
  }
  llvm::MDNode *metaNode = nullptr;

  if (llvm::isa<llvm::GlobalVariable>(v)) {
    metaNode = llvm::cast<llvm::GlobalVariable>(v)->getMetadata(kind);

  } else if (llvm::isa<llvm::AllocaInst>(v)) {
    metaNode = llvm::cast<llvm::AllocaInst>(v)->getMetadata(kind);
  } else if (llvm::isa<llvm::Function>(v)) {
    metaNode = llvm::cast<llvm::Function>(v)->getMetadata(kind);
  } else if (llvm::isa<llvm::LoadInst>(v)) {
    metaNode = llvm::cast<llvm::LoadInst>(v)->getMetadata(kind);
  }

  if (!metaNode) {
    // this->getLogger()->LogError("Could not find metadata for " +
    //                             v->getName().str());

    return;
  }

  metaData = llvm::cast<llvm::MDString>(metaNode->getOperand(0))->getString();
}

void CodeGenerationContext::setArraySizeMetadata(
    llvm::Value *array, const std::vector<uint64_t> &sizes) {
  std::string metaData = "";

  for (const auto &size : sizes) {
    metaData += std::to_string(size) + ":";
  }

  setMetadata("I", array, metaData);
}
void CodeGenerationContext::getArraySizeMetadata(llvm::Value *array,
                                                 std::vector<uint64_t> &sizes) {
  std::string metaData = "";

  getMetaData("I", array, metaData);

  std::vector<std::string> sizesStr;
  Utils::split(metaData, ":", sizesStr);

  for (const auto &sizeStr : sizesStr) {
    sizes.push_back(std::stoll(sizeStr));
  }
}

void CodeGenerationContext::setArrayElementTypeMetadata(
    llvm::Value *array, llvm::Type *elementType) {
  std::string metaData =
      std::to_string(getMapper()->mapLLVMTypeToCustomType(elementType));
  setMetadata("ET", array, metaData);
}
llvm::Type *
CodeGenerationContext::getArrayElementTypeMetadata(llvm::Value *array) {
  std::string metaData = "";
  getMetaData("ET", array, metaData);
  std::vector<std::string> sizesStr;
  Utils::split(metaData, ":", sizesStr);

  if (sizesStr.size() != 1) {
    this->getLogger()->LogError("Invalid metadata for array element type");
    return nullptr;
  }

  return getMapper()->mapCustomTypeToLLVMType(
      (SyntaxKindUtils::SyntaxKind)stoi(sizesStr[0]));
}

void CodeGenerationContext::getMultiArrayType(
    llvm::ArrayType *&arrayType, const std::vector<uint64_t> &actualSizes,
    llvm::Type *elementType) {
  for (int64_t i = actualSizes.size() - 1; i >= 0; i--) {
    if (arrayType == nullptr) {
      arrayType = llvm::ArrayType::get(elementType, actualSizes[i]);
    } else {
      arrayType = llvm::ArrayType::get(arrayType, actualSizes[i]);
    }
  }
}
int8_t CodeGenerationContext::verifyArrayType(llvm::ArrayType *lhsType,
                                              llvm::ArrayType *rhsType,
                                              std::string inExp) {
  std::vector<uint64_t> lhsSizes, rhsSizes;
  llvm::Type *lshEType = (lhsType), *rhsEType = (rhsType);
  this->createArraySizesAndArrayElementType(lhsSizes, lshEType);
  this->createArraySizesAndArrayElementType(rhsSizes, rhsEType);

  if (lshEType != rhsEType) {
    this->getLogger()->LogError(
        "Type mismatch " + inExp + ", expected " +
        this->getMapper()->getLLVMTypeName(lhsType) + " but found " +
        this->getMapper()->getLLVMTypeName(rhsType) + " ");
    return EXIT_FAILURE;
  }

  if (lhsSizes.size() != rhsSizes.size()) {
    this->getLogger()->LogError(
        "Dimension mismatch Expected " + std::to_string(lhsSizes.size()) +
        " but found " + std::to_string(rhsSizes.size()) + inExp);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < lhsSizes.size(); i++) {
    if (lhsSizes[i] < rhsSizes[i]) {
      this->getLogger()->LogError("Dimension mismatch Expected Dimension " +
                                  std::to_string(i) + " to be " +
                                  std::to_string(lhsSizes[i]) + " but found " +
                                  std::to_string(rhsSizes[i]));
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

int8_t CodeGenerationContext::verifyStructType(llvm::StructType *lhsType,
                                               llvm::StructType *rhsType,
                                               std::string inExp) {

  if (this->_classTypes.find(lhsType->getStructName().str()) !=
          this->_classTypes.end() &&
      this->_classTypes.find(rhsType->getStructName().str()) !=
          this->_classTypes.end()) {

    if (this->_classTypes[rhsType->getStructName().str()] &&
        this->_classTypes[rhsType->getStructName().str()]->isChildOf(
            lhsType->getStructName().str()))
      return EXIT_SUCCESS;
  }

  if (this->getMapper()->getLLVMTypeName(lhsType) !=
      this->getMapper()->getLLVMTypeName(rhsType)) {
    this->getLogger()->LogError(
        "Type mismatch Expected " +
        this->getMapper()->getLLVMTypeName(lhsType) + " but found " +
        this->getMapper()->getLLVMTypeName(rhsType) + inExp);
    return EXIT_FAILURE;
  }

  if (lhsType->getNumElements() != rhsType->getNumElements()) {
    this->getLogger()->LogError("Type mismatch " + inExp + " Expected " +
                                std::to_string(lhsType->getNumElements()) +
                                " but found " +
                                std::to_string(rhsType->getNumElements()));
    return EXIT_FAILURE;
  }

  if (lhsType->getStructName() != rhsType->getStructName()) {
    this->getLogger()->LogError("Type mismatch " + inExp + " Expected " +
                                lhsType->getStructName().str() + " but found " +
                                rhsType->getStructName().str());

    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int8_t
CodeGenerationContext::verifyType(const std::vector<llvm::Type *> &lhsTypes,
                                  const std::vector<llvm::Type *> &rhsTypes,
                                  const std::string &inExp) {

  if (lhsTypes.size() != rhsTypes.size()) {

    this->getLogger()->LogError("Type mismatch Expected " +
                                this->getMapper()->getLLVMTypeName(lhsTypes) +
                                inExp);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < lhsTypes.size(); i++) {
    if (this->verifyType(lhsTypes[i], rhsTypes[i], inExp) == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

int8_t CodeGenerationContext::verifyType(llvm::Type *lhsType,
                                         llvm::Type *rhsType,
                                         std::string inExp) {
  if (llvm::isa<llvm::ArrayType>(lhsType) &&
      llvm::isa<llvm::ArrayType>(rhsType))
    return verifyArrayType(llvm::cast<llvm::ArrayType>(lhsType),
                           llvm::cast<llvm::ArrayType>(rhsType), inExp);

  if (llvm::isa<llvm::StructType>(lhsType) &&
      llvm::isa<llvm::StructType>(rhsType))
    return verifyStructType(llvm::cast<llvm::StructType>(lhsType),
                            llvm::cast<llvm::StructType>(rhsType), inExp);

  if (lhsType != rhsType) {
    this->getLogger()->LogError(
        "Type mismatch Expected " +
        this->getMapper()->getLLVMTypeName(lhsType) + " but found " +
        this->getMapper()->getLLVMTypeName(rhsType) + inExp);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void CodeGenerationContext::getMultiArrayTypeForGlobal(
    llvm::ArrayType *&arrayType, llvm::Constant *&def,
    const std::vector<uint64_t> &actualSizes, llvm::Type *elementType) {
  for (int64_t i = actualSizes.size() - 1; i >= 0; i--) {
    if (arrayType == nullptr) {
      arrayType = llvm::ArrayType::get(elementType, actualSizes[i]);
    } else {
      arrayType = llvm::ArrayType::get(arrayType, actualSizes[i]);
    }

    def = llvm::ConstantArray::get(
        arrayType, std::vector<llvm::Constant *>(actualSizes[i], def));
  }
}

void CodeGenerationContext::getRetrunedArrayType(
    llvm::Function *F, llvm::ArrayType *&arrayType,
    llvm::Type *&arrayElementType, std::vector<uint64_t> &actualSizes) {
  std::string metaData = "";
  std::vector<std::string> strs;
  getMetaData("rt", F, metaData);
  if (metaData == "") {
    return;
  }
  Utils::split(metaData, ":", strs);
  if (strs.size() == 0) {
    return;
  }

  if (strs[2] == "ay") {
    arrayElementType = this->getFlowWingType(strs[3]).getType();

    if (!arrayElementType)
      arrayElementType = getMapper()->mapCustomTypeToLLVMType(
          (SyntaxKindUtils::SyntaxKind)stoi(strs[3]));

    for (int64_t i = 5; i < strs.size(); i++) {
      actualSizes.push_back(stoi(strs[i]));
    }

    llvm::Constant *def = llvm::cast<llvm::Constant>(
        this->getMapper()->getDefaultValue(arrayElementType));

    getMultiArrayType(arrayType, actualSizes, arrayElementType);
  } else if (strs[2] == "pr") {
    arrayElementType = getMapper()->mapCustomTypeToLLVMType(
        (SyntaxKindUtils::SyntaxKind)stoi(strs[3]));
  }
}

void CodeGenerationContext::getReturnedObjectType(
    llvm::Function *F, llvm::StructType *&objectType) {
  std::string metaData = "";
  std::vector<std::string> strs;
  getMetaData("rt", F, metaData);
  if (metaData == "") {
    return;
  }

  Utils::split(metaData, ":", strs);

  if (strs.size() == 0)
    return;

  if (strs[2] == "ob") {
    if (_classTypes.find(strs[3]) != _classTypes.end())
      objectType = _classTypes[strs[3]]->getClassType();
    else {

      if (!(this->getFlowWingType(strs[3]).getStructType())) {
        this->getLogger()->LogError("Expected a object of type " +
                                    Utils::getActualTypeName(strs[3]));
        return;
      }

      objectType = this->getFlowWingType(strs[3]).getStructType();
    }
  }
}
void CodeGenerationContext::getReturnedPrimitiveType(llvm::Function *F,
                                                     llvm::Type *&type) {
  std::string metaData = "";
  std::vector<std::string> strs;
  getMetaData("rt", F, metaData);
  if (metaData == "") {
    return;
  }
  Utils::split(metaData, ":", strs);
  if (strs[2] == "pr") {
    type = getMapper()->mapCustomTypeToLLVMType(
        (SyntaxKindUtils::SyntaxKind)stoi(strs[3]));
  }
}

llvm::Value *CodeGenerationContext::createMemoryGetPtr(
    llvm::Type *type, std::string variableName,
    BinderKindUtils::MemoryKind memoryKind, llvm::Constant *initialValue) {
  switch (memoryKind) {
  case BinderKindUtils::MemoryKind::Heap: {
    auto fun = this->_module->getFunction(INNERS::FUNCTIONS::MALLOC);

    llvm::CallInst *malloc_call = this->_builder->CreateCall(
        fun, llvm::ConstantInt::get(llvm::Type::getInt64Ty(*this->_context),
                                    this->getMapper()->getSizeOf(type)));
    malloc_call->setTailCall(false);

    // Cast the result of 'malloc' to a pointer to int
    return this->_builder->CreateBitCast(
        malloc_call,
        llvm::PointerType::getUnqual(llvm::Type::getInt32Ty(*this->_context)));
  }
  case BinderKindUtils::MemoryKind::Stack: {
    return this->_builder->CreateAlloca(type, nullptr, variableName);
  }
  case BinderKindUtils::MemoryKind::Global: {

    llvm::Value *global = this->_module->getNamedGlobal(variableName);

    if (global)
      return global;

    llvm::GlobalVariable *variable = new llvm::GlobalVariable(
        *this->_module, type, false,
        initialValue ? llvm::GlobalValue::LinkageTypes::PrivateLinkage
                     : llvm::GlobalValue::LinkageTypes::CommonLinkage,
        initialValue ? initialValue : llvm::Constant::getNullValue(type),
        variableName);
    variable->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Local);

    return variable;
  }

  default:
    this->getLogger()->LogError(
        "Unknown Memory Kind " + BinderKindUtils::to_string(memoryKind) +
        " for " + variableName + " in " + __PRETTY_FUNCTION__);
    return nullptr;
  }
}
auto CodeGenerationContext::getArrayTypeAsString(llvm::ArrayType *arrayType)
    -> std::string {
  llvm::Type *type = arrayType;
  std::vector<uint64_t> sizes;

  this->createArraySizesAndArrayElementType(sizes, type);
  std::string actualSizesStr = "";
  for (auto &size : sizes) {
    actualSizesStr += std::to_string(size) + ",";
  }

  return this->getMapper()->getLLVMTypeName(arrayType, false) + ":" +
         actualSizesStr;
}

void CodeGenerationContext::verifyFunction(llvm::Function *F,
                                           const std::string &FUNCTION_NAME) {
  std::string errorInfo;
  llvm::raw_string_ostream errorStream(errorInfo);
  if (llvm::verifyFunction(*F, &errorStream)) {
    errorStream.flush();
    this->getLogger()->LogError("Error verifying function " + FUNCTION_NAME +
                                errorInfo);
  } else {

    this->getLogger()->LogInfo("Function " + FUNCTION_NAME +
                               " verified successfully");
  }
}

void CodeGenerationContext::verifyModule(llvm::Module *M) {
  std::string errorInfo;
  llvm::raw_string_ostream errorStream(errorInfo);
  if (llvm::verifyModule(*M, &errorStream)) {
    errorStream.flush();
    this->getLogger()->LogError("Error verifying module " + errorInfo);
  } else {
    this->getLogger()->LogInfo("Module verified successfully");
  }
}
