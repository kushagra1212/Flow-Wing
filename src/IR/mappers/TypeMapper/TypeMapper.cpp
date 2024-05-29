#include "TypeMapper.h"

TypeMapper::TypeMapper(llvm::LLVMContext *context, llvm::IRBuilder<> *builder,
                       llvm::Module *module,
                       CodeGenerationContext *codeGenerationContext)
    : _context(context), _builder(builder), _module(module),
      _codeGenerationContext(codeGenerationContext) {
  _typeMappings = {
      {(llvm::Type *)llvm::Type::getInt1Ty(*context),
       SyntaxKindUtils::SyntaxKind::BoolKeyword},
      {(llvm::Type *)llvm::Type::getInt8Ty(*context),
       SyntaxKindUtils::SyntaxKind::Int8Keyword},
      {(llvm::Type *)llvm::Type::getInt32Ty(*context),
       SyntaxKindUtils::SyntaxKind::Int32Keyword},
      {(llvm::Type *)llvm::Type::getInt64Ty(*context),
       SyntaxKindUtils::SyntaxKind::Int64Keyword},
      {(llvm::Type *)llvm::Type::getDoubleTy(*context),
       SyntaxKindUtils::SyntaxKind::DeciKeyword},
      {(llvm::Type *)llvm::Type::getFloatTy(*context),
       SyntaxKindUtils::SyntaxKind::Deci32Keyword},
      {(llvm::Type *)llvm::Type::getInt8PtrTy(*context),
       SyntaxKindUtils::SyntaxKind::StrKeyword},
      {(llvm::Type *)llvm::Type::getVoidTy(*context),
       SyntaxKindUtils::SyntaxKind::NthgKeyword},
  };

  _reverseTypeMappings = {
      {SyntaxKindUtils::SyntaxKind::BoolKeyword,
       (llvm::Type *)llvm::Type::getInt1Ty(*context)},
      {SyntaxKindUtils::SyntaxKind::Int8Keyword,
       (llvm::Type *)llvm::Type::getInt8Ty(*context)},
      {SyntaxKindUtils::SyntaxKind::Int32Keyword,
       (llvm::Type *)llvm::Type::getInt32Ty(*context)},
      {SyntaxKindUtils::SyntaxKind::Int64Keyword,
       (llvm::Type *)llvm::Type::getInt64Ty(*context)},
      {SyntaxKindUtils::SyntaxKind::DeciKeyword,
       (llvm::Type *)llvm::Type::getDoubleTy(*context)},
      {SyntaxKindUtils::SyntaxKind::Deci32Keyword,
       (llvm::Type *)llvm::Type::getFloatTy(*context)},
      {SyntaxKindUtils::SyntaxKind::StrKeyword,
       (llvm::Type *)llvm::Type::getInt8PtrTy(*context)},
      {SyntaxKindUtils::SyntaxKind::NthgKeyword,
       (llvm::Type *)llvm::Type::getVoidTy(*context)},
  };
}

llvm::Type *
TypeMapper::mapCustomTypeToLLVMType(SyntaxKindUtils::SyntaxKind type) const {
  auto it = _reverseTypeMappings.find(type);
  if (it != _reverseTypeMappings.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

SyntaxKindUtils::SyntaxKind
TypeMapper::mapLLVMTypeToCustomType(llvm::Type *type) const {
  auto it = _typeMappings.find(type);
  if (it != _typeMappings.end()) {
    return it->second;
  } else {
    return SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE;
  }
}

const bool TypeMapper::isVoidType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::NthgKeyword;
}

const bool TypeMapper::isStringType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::StrKeyword;
}

const bool TypeMapper::isBoolType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::BoolKeyword;
}

const bool TypeMapper::isDoubleType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::DeciKeyword;
}

const bool TypeMapper::isInt32Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::Int32Keyword;
}

const bool TypeMapper::isInt64Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::Int64Keyword;
}

const bool TypeMapper::isInt8Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::Int8Keyword;
}

const bool TypeMapper::isPtrType(llvm::Type *type) const {
  return type->isPointerTy();
}
std::string TypeMapper::getLLVMTypeName(llvm::Type *type) const {
  SyntaxKindUtils::SyntaxKind customType = mapLLVMTypeToCustomType(type);
  if (customType == SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
    if (llvm::isa<llvm::StructType>(type)) {
      llvm::StructType *structType = llvm::cast<llvm::StructType>(type);
      if (_codeGenerationContext->_classTypes.find(
              structType->getName().str()) !=
          _codeGenerationContext->_classTypes.end()) {
        return COLORED_STRING::GET("<Class<" + structType->getName().str() +
                                       ">>",
                                   YELLOW_TEXT, RED_TEXT);
      }
      return COLORED_STRING::GET("<Object<" + structType->getName().str() +
                                     ">>",
                                 YELLOW_TEXT, RED_TEXT);
    } else if (llvm::isa<llvm::ArrayType>(type)) {
      llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);
      return COLORED_STRING::GET(
          "<Array" + getLLVMTypeName(arrayType->getElementType()) + ">",
          YELLOW_TEXT, RED_TEXT);
    }
  }

  return COLORED_STRING::GET("<" + getLLVMTypeName(customType) + ">",
                             YELLOW_TEXT, RED_TEXT);
}

std::string
TypeMapper::getLLVMTypeName(SyntaxKindUtils::SyntaxKind customType) const {
  switch (customType) {
  case SyntaxKindUtils::SyntaxKind::BoolKeyword:
    return "'Boolean'";
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
    return "'Integer64'";
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
    return "'Integer32'";
  case SyntaxKindUtils::SyntaxKind::Int8Keyword:
    return "'Integer8'";
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
    return "'Decimal64'";
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword:
    return "'Decimal32'";
  case SyntaxKindUtils::SyntaxKind::StrKeyword:
    return "'String'";
  case SyntaxKindUtils::SyntaxKind::NthgKeyword:
    return "'Nothing'";
  default:
    break;
  }

  return "Unknown";
}

llvm::Value *TypeMapper::getDefaultValue(SyntaxKindUtils::SyntaxKind type) {
  llvm::Value *_retVal = nullptr;

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
    _retVal = _builder->getInt32(0);
    break;
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
    _retVal = _builder->getInt64(0);
    break;
  case SyntaxKindUtils::SyntaxKind::Int8Keyword:
    _retVal = _builder->getInt8(0);
    break;
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
    _retVal = llvm::ConstantFP::get(*_context, llvm::APFloat(0.0));
    break;
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword:
    _retVal = llvm::ConstantFP::get(*_context,
                                    llvm::APFloat(static_cast<float>(0.0)));
    break;
  case SyntaxKindUtils::SyntaxKind::BoolKeyword:
    _retVal = _builder->getInt1(false);
    break;
  case SyntaxKindUtils::SyntaxKind::StrKeyword:
    _retVal = _builder->CreateGlobalStringPtr("");
    break;
  case SyntaxKindUtils::SyntaxKind::NthgKeyword:
    break;
  case SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE:
    break;
  default:
    break;
  }
  return _retVal;
}

llvm::Value *TypeMapper::getDefaultValue(llvm::Type *type) {
  SyntaxKindUtils::SyntaxKind kind = mapLLVMTypeToCustomType(type);
  if (kind == SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
    return llvm::Constant::getNullValue(type);
  }

  return getDefaultValue(kind);
}

const bool TypeMapper::isPrimitiveType(llvm::Type *type) const {
  return isBoolType(type) || isDoubleType(type) || isInt32Type(type) ||
         isStringType(type);
}

const bool TypeMapper::isPrimitiveType(SyntaxKindUtils::SyntaxKind type) const {
  return isPrimitiveType(mapCustomTypeToLLVMType(type));
}

const bool
TypeMapper::isEquivalentType(llvm::Type *type,
                             SyntaxKindUtils::SyntaxKind customType) const {
  return type == mapCustomTypeToLLVMType(customType);
}
const bool TypeMapper::isEquivalentType(SyntaxKindUtils::SyntaxKind customType,
                                        llvm::Type *type) const {
  return isEquivalentType(type, customType);
}
const bool TypeMapper::isEquivalentType(llvm::Type *type1,
                                        llvm::Type *type2) const {
  return type1 == type2;
}
const bool
TypeMapper::isEquivalentType(SyntaxKindUtils::SyntaxKind type1,
                             SyntaxKindUtils::SyntaxKind type2) const {
  return type1 == type2;
}
// llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);
// llvm::Type *elementType = arrayType->getElementType();
// llvm::Type *type = arrayType;
// std::vector<uint64_t> sizes;
// _codeGenerationContext->createArraySizesAndArrayElementType(sizes, type);
uint64_t TypeMapper::getSizeOf(llvm::Type *type) {

  if (type == llvm::Type::getInt32Ty(*_context))
    return sizeof(int32_t);

  if (type == llvm::Type::getInt64Ty(*_context))
    return sizeof(int64_t);

  if (type == llvm::Type::getInt8Ty(*_context))
    return sizeof(int8_t);

  if (type == llvm::Type::getDoubleTy(*_context))
    return sizeof(double);

  if (type == llvm::Type::getFloatTy(*_context))
    return sizeof(float);

  if (type == llvm::Type::getInt1Ty(*_context))
    return sizeof(bool);

  if (type == llvm::Type::getInt8PtrTy(*_context))
    return sizeof(int8_t);

  if (llvm::isa<llvm::ArrayType>(type)) {

    llvm::DataLayout *TD = new llvm::DataLayout(_module);

    llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);
    return TD->getTypeAllocSize(arrayType);
    llvm::Type *elementType = arrayType->getElementType();
    llvm::Type *type = arrayType;
    std::vector<uint64_t> sizes;
    while (llvm::ArrayType *arrayType = llvm::dyn_cast<llvm::ArrayType>(type)) {
      sizes.push_back(arrayType->getNumElements());
      type = arrayType->getElementType();
    }
    uint64_t elementSize = getSizeOf(type);
    uint64_t totalSize = elementSize;
    for (const int &size : sizes) {
      totalSize *= size;
    }
    return totalSize;
  }

  if (llvm::isa<llvm::StructType>(type)) {

    llvm::DataLayout *TD = new llvm::DataLayout(_module);

    llvm::StructType *structType = llvm::cast<llvm::StructType>(type);
    return TD->getTypeAllocSize(structType);
  }

  return 0;
}

uint64_t TypeMapper::getSizeOf(SyntaxKindUtils::SyntaxKind type) {

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
    return sizeof(int32_t);
    break;
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
    return sizeof(int64_t);
    break;
  case SyntaxKindUtils::SyntaxKind::Int8Keyword:
    return sizeof(int8_t);
    break;
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
    return sizeof(double);
    break;
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword:
    return sizeof(float);
    break;
  case SyntaxKindUtils::SyntaxKind::BoolKeyword:
    return sizeof(bool);
    break;
  case SyntaxKindUtils::SyntaxKind::StrKeyword:
    return sizeof(int8_t);
    break;
  case SyntaxKindUtils::SyntaxKind::NthgKeyword:
    break;
  case SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE:
    break;
  default:
    break;
  }
  return 0;
}