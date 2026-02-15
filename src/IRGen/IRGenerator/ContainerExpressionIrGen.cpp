/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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


#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/ADT/ArrayRef.h"
#include <cstdint>
namespace flow_wing::ir_gen {

void IRGenerator::visit(
    binding::BoundContainerExpression *container_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Container Expression", "IR GENERATION");

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto flow_type = container_expression->getType();
  auto llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(flow_type.get());

  auto fg_array_type = static_cast<types::ArrayType *>(flow_type.get());

  auto array_ptr = getTempArray(flow_type.get(), flow_type.get(), nullptr);

  auto elements_size = container_expression->getElements().size();

  for (size_t i = 0; i < elements_size; i++) {

    auto indices = container_expression->getElements()[i]->getIndices();

    std::vector<llvm::Value *> indices_values;
    indices_values.push_back(builder->getInt64(0));

    for (size_t j = 0; j < indices.size(); j++) {
      indices_values.push_back(
          builder->getInt64(static_cast<uint64_t>(indices[j])));
    }

    auto array_element_value =
        builder->CreateGEP(llvm_type, array_ptr, indices_values);

    container_expression->getElements()[i]->getExpression()->accept(this);

    auto *src_type = m_last_type;
    auto *src_value = m_last_value;

    std::shared_ptr<types::Type> target_slot_type =
        fg_array_type->getUnderlyingType();

    const auto &dimensions = fg_array_type->getDimensions();
    if (indices.size() < dimensions.size()) {
      // Collect remaining dimensions
      std::vector<size_t> sub_dims;
      for (size_t d = indices.size(); d < dimensions.size(); ++d) {
        sub_dims.push_back(dimensions[d]);
      }
      // Create the Sub-Array Type (e.g., dynamic[2])
      target_slot_type = std::make_shared<types::ArrayType>(
          fg_array_type->getUnderlyingType(), sub_dims);
    }

    CODEGEN_DEBUG_LOG("indices_values ", indices, "Underlying Type",
                      fg_array_type->getUnderlyingType()->getName(),
                      "Source Type", src_type->getName(), "dest type",
                      target_slot_type->getName());

    if (target_slot_type->getKind() == types::TypeKind::kArray &&
        src_type->getKind() == types::TypeKind::kArray) {

      CODEGEN_DEBUG_LOG("ARRAY-TO-ARRAY: Using emitArrayCopy for deep copy",
                        "IR GENERATION");

      // Load the array pointer if it's a variable
      llvm::Value *src_array_ptr = src_value;
      if (llvm::isa<llvm::AllocaInst>(src_value) ||
          llvm::isa<llvm::GlobalVariable>(src_value)) {
        auto *src_llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(src_type);
        src_array_ptr =
            builder->CreateLoad(src_llvm_type->getPointerTo(), src_value,
                                "load_array_ptr_for_copy");
      }

      auto *src_array_type = static_cast<types::ArrayType *>(src_type);
      auto *dest_array_type =
          static_cast<types::ArrayType *>(target_slot_type.get());

      // This will use memcpy for matching types or element-by-element for
      // conversions
      emitArrayCopy(array_element_value, dest_array_type, src_array_ptr,
                    src_array_type);

    } else {
      // For non-array types, use the normal path
      emitTypedStore(array_element_value, target_slot_type.get(), src_value,
                     src_type);
    }
    clearLast();
  }

  clearLast();
  m_last_value = array_ptr;
  m_last_type = flow_type.get();
}
} // namespace flow_wing::ir_gen
