#include "flowwing_vector.h"

#ifdef __cplusplus
extern "C" {
#endif
// Int Vector Functions
SHARED_LIB IntVectorHandle *int_vector_new() {
  return new IntVectorHandle{new std::vector<int>()};
}

SHARED_LIB void int_vector_add(IntVectorHandle *handle, int element) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  vector->push_back(element);
}

SHARED_LIB int int_vector_get(IntVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index];
  }
  return 0; // Default value if out of range
}

SHARED_LIB void int_vector_remove(IntVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

SHARED_LIB size_t int_vector_size(IntVectorHandle *handle) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  return vector->size();
}

SHARED_LIB void int_vector_free(IntVectorHandle *handle) {
  delete static_cast<std::vector<int> *>(handle->vector);
  delete handle;
}

SHARED_LIB void int_vector_set(IntVectorHandle *handle, size_t index,
                               int value) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = value;
  }
}
// Bool Vector Functions
SHARED_LIB BoolVectorHandle *bool_vector_new() {
  return new BoolVectorHandle{new std::vector<bool>()};
}

SHARED_LIB void bool_vector_add(BoolVectorHandle *handle, bool element) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  vector->push_back(element);
}

SHARED_LIB bool bool_vector_get(BoolVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index];
  }
  return false; // Default value if out of range
}

SHARED_LIB void bool_vector_remove(BoolVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

SHARED_LIB size_t bool_vector_size(BoolVectorHandle *handle) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  return vector->size();
}

SHARED_LIB void bool_vector_free(BoolVectorHandle *handle) {
  delete static_cast<std::vector<bool> *>(handle->vector);
  delete handle;
}
SHARED_LIB void bool_vector_set(BoolVectorHandle *handle, size_t index,
                                bool value) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = value;
  }
}
// String Vector Functions
SHARED_LIB StringVectorHandle *string_vector_new() {
  return new StringVectorHandle{new std::vector<std::string>()};
}

SHARED_LIB void string_vector_add(StringVectorHandle *handle,
                                  const char *element) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  vector->emplace_back(element);
}

SHARED_LIB void string_vector_set(StringVectorHandle *handle, size_t index,
                                  const char *element) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = element;
  }
}

SHARED_LIB const char *string_vector_get(StringVectorHandle *handle,
                                         size_t index) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index].c_str();
  }
  return nullptr;
}

SHARED_LIB void string_vector_remove(StringVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

SHARED_LIB size_t string_vector_size(StringVectorHandle *handle) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  return vector->size();
}

SHARED_LIB void string_vector_free(StringVectorHandle *handle) {
  delete static_cast<std::vector<std::string> *>(handle->vector);
  delete handle;
}

// Double Vector Functions
SHARED_LIB DoubleVectorHandle *double_vector_new() {
  return new DoubleVectorHandle{new std::vector<double>()};
}

SHARED_LIB void double_vector_add(DoubleVectorHandle *handle, double element) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  vector->push_back(element);
}
SHARED_LIB void double_vector_set(DoubleVectorHandle *handle, size_t index,
                                  double element) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = element;
  }
}

SHARED_LIB double double_vector_get(DoubleVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index];
  }
  return 0.0; // Default value if out of range
}

SHARED_LIB void double_vector_remove(DoubleVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

SHARED_LIB size_t double_vector_size(DoubleVectorHandle *handle) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  return vector->size();
}

SHARED_LIB void double_vector_free(DoubleVectorHandle *handle) {
  delete static_cast<std::vector<double> *>(handle->vector);
  delete handle;
}
#ifdef __cplusplus
}
#endif
