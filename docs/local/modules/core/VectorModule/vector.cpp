#include <cstring> // For std::strlen and std::strcpy
#include <string>
#include <vector>

extern "C" {
typedef struct {
  std::vector<int> *vector;
} IntVectorHandle;

typedef struct {
  std::vector<bool> *vector;
} BoolVectorHandle;

typedef struct {
  std::vector<std::string> *vector;
} StringVectorHandle;

typedef struct {
  std::vector<double> *vector;
} DoubleVectorHandle;

// Int Vector Functions
IntVectorHandle *int_vector_new() {
  return new IntVectorHandle{new std::vector<int>()};
}

void int_vector_add(IntVectorHandle *handle, int element) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  vector->push_back(element);
}

int int_vector_get(IntVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index];
  }
  return 0; // Default value if out of range
}

void int_vector_remove(IntVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

size_t int_vector_size(IntVectorHandle *handle) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  return vector->size();
}

void int_vector_free(IntVectorHandle *handle) {
  delete static_cast<std::vector<int> *>(handle->vector);
  delete handle;
}

void int_vector_set(IntVectorHandle *handle, size_t index, int value) {
  auto vector = static_cast<std::vector<int> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = value;
  }
}
// Bool Vector Functions
BoolVectorHandle *bool_vector_new() {
  return new BoolVectorHandle{new std::vector<bool>()};
}

void bool_vector_add(BoolVectorHandle *handle, bool element) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  vector->push_back(element);
}

bool bool_vector_get(BoolVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index];
  }
  return false; // Default value if out of range
}

void bool_vector_remove(BoolVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

size_t bool_vector_size(BoolVectorHandle *handle) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  return vector->size();
}

void bool_vector_free(BoolVectorHandle *handle) {
  delete static_cast<std::vector<bool> *>(handle->vector);
  delete handle;
}
void bool_vector_set(BoolVectorHandle *handle, size_t index, bool value) {
  auto vector = static_cast<std::vector<bool> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = value;
  }
}
// String Vector Functions
StringVectorHandle *string_vector_new() {
  return new StringVectorHandle{new std::vector<std::string>()};
}

void string_vector_add(StringVectorHandle *handle, const char *element) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  vector->emplace_back(element);
}

void string_vector_set(StringVectorHandle *handle, size_t index,
                       const char *element) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = element;
  }
}

const char *string_vector_get(StringVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index].c_str();
  }
  return nullptr;
}

void string_vector_remove(StringVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

size_t string_vector_size(StringVectorHandle *handle) {
  auto vector = static_cast<std::vector<std::string> *>(handle->vector);
  return vector->size();
}

void string_vector_free(StringVectorHandle *handle) {
  delete static_cast<std::vector<std::string> *>(handle->vector);
  delete handle;
}

// Double Vector Functions
DoubleVectorHandle *double_vector_new() {
  return new DoubleVectorHandle{new std::vector<double>()};
}

void double_vector_add(DoubleVectorHandle *handle, double element) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  vector->push_back(element);
}
void double_vector_set(DoubleVectorHandle *handle, size_t index,
                       double element) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  if (index < vector->size()) {
    (*vector)[index] = element;
  }
}

double double_vector_get(DoubleVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  if (index < vector->size()) {
    return (*vector)[index];
  }
  return 0.0; // Default value if out of range
}

void double_vector_remove(DoubleVectorHandle *handle, size_t index) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  if (index < vector->size()) {
    vector->erase(vector->begin() + index);
  }
}

size_t double_vector_size(DoubleVectorHandle *handle) {
  auto vector = static_cast<std::vector<double> *>(handle->vector);
  return vector->size();
}

void double_vector_free(DoubleVectorHandle *handle) {
  delete static_cast<std::vector<double> *>(handle->vector);
  delete handle;
}
}
