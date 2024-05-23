#ifndef CUSTOM_TYPE_ID_GENERATOR_H
#define CUSTOM_TYPE_ID_GENERATOR_H

#include <iostream>
#include <string>

namespace IDGenerator {
class CustomTypeIDGenerator {
public:
  static CustomTypeIDGenerator *instance();
  uint32_t next() { return _id++; }
  std::string nextString() { return std::to_string(_id++); }

public:
  CustomTypeIDGenerator() : _id(0) {}

  static CustomTypeIDGenerator *only_copy;
  uint32_t _id;
};
} // namespace IDGenerator

#endif