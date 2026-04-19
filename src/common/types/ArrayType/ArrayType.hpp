
#pragma once

#include "src/common/types/Type.hpp"
#include <cstddef>
#include <memory>
#include <vector>

namespace flow_wing {
namespace types {

class ArrayType : public Type {
public:
  ArrayType(std::shared_ptr<Type> underlying_type,
            const std::vector<size_t> &dimensions);

  bool operator==(const Type &other) const override;
  bool operator<=(const Type &other) const override;

  const std::vector<size_t> &getDimensions() const;
  std::shared_ptr<Type> getUnderlyingType() const;

private:
  std::shared_ptr<Type> m_underlying_type;
  std::vector<size_t> m_dimensions;

  std::string buildArrayTypeName(std::shared_ptr<Type> underlying_type,
                                 const std::vector<size_t> &dimensions);
};

} // namespace types
} // namespace flow_wing