#include "CustomTypeIDGenerator.h"
namespace IDGenerator {
CustomTypeIDGenerator *CustomTypeIDGenerator::instance() {
  if (!only_copy) {
    only_copy = new CustomTypeIDGenerator();
  }
  return only_copy;
}

CustomTypeIDGenerator *CustomTypeIDGenerator::only_copy = nullptr;

} // namespace IDGenerator