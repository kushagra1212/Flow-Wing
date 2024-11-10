#pragma once

#include <cstring> // For std::strlen and std::strcpy
#include <string>
#include <vector>

#if defined(_WIN32)
#define SHARED_LIB __stdcall __declspec(dllexport)
#else
#define SHARED_LIB
#endif

#ifdef __cplusplus
extern "C" {
#endif
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
SHARED_LIB IntVectorHandle *int_vector_new();

SHARED_LIB void int_vector_add(IntVectorHandle *handle, int element);

SHARED_LIB int int_vector_get(IntVectorHandle *handle, size_t index);

SHARED_LIB void int_vector_remove(IntVectorHandle *handle, size_t index);

SHARED_LIB size_t int_vector_size(IntVectorHandle *handle);
SHARED_LIB void int_vector_free(IntVectorHandle *handle);

SHARED_LIB void int_vector_set(IntVectorHandle *handle, size_t index,
                               int value);
// Bool Vector Functions
SHARED_LIB BoolVectorHandle *bool_vector_new();

SHARED_LIB void bool_vector_add(BoolVectorHandle *handle, bool element);

SHARED_LIB bool bool_vector_get(BoolVectorHandle *handle, size_t index);

SHARED_LIB void bool_vector_remove(BoolVectorHandle *handle, size_t index);

SHARED_LIB size_t bool_vector_size(BoolVectorHandle *handle);

SHARED_LIB void bool_vector_free(BoolVectorHandle *handle);
SHARED_LIB void bool_vector_set(BoolVectorHandle *handle, size_t index,
                                bool value);
// String Vector Functions
SHARED_LIB StringVectorHandle *string_vector_new();

SHARED_LIB void string_vector_add(StringVectorHandle *handle,
                                  const char *element);

SHARED_LIB void string_vector_set(StringVectorHandle *handle, size_t index,
                                  const char *element);

SHARED_LIB const char *string_vector_get(StringVectorHandle *handle,
                                         size_t index);

SHARED_LIB void string_vector_remove(StringVectorHandle *handle, size_t index);

SHARED_LIB size_t string_vector_size(StringVectorHandle *handle);

SHARED_LIB void string_vector_free(StringVectorHandle *handle);

// Double Vector Functions
SHARED_LIB DoubleVectorHandle *double_vector_new();

SHARED_LIB void double_vector_add(DoubleVectorHandle *handle, double element);
SHARED_LIB void double_vector_set(DoubleVectorHandle *handle, size_t index,
                                  double element);

SHARED_LIB double double_vector_get(DoubleVectorHandle *handle, size_t index);

SHARED_LIB void double_vector_remove(DoubleVectorHandle *handle, size_t index);

SHARED_LIB size_t double_vector_size(DoubleVectorHandle *handle);

SHARED_LIB void double_vector_free(DoubleVectorHandle *handle);

#ifdef __cplusplus
}
#endif