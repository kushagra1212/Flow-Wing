// utils.cpp
#include <string>
#include <unordered_map>

#if defined(_WIN32)
#define SHARED_LIB __stdcall __declspec(dllexport)
#else
#define SHARED_LIB
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Define a handle for the map.
typedef struct {
  void *map;
} MapHandle;

// Creates a new map and returns a handle to it.
SHARED_LIB MapHandle *map_new();

// Inserts a key-value pair into the map.
SHARED_LIB void map_insert(MapHandle *handle, const char *key,
                           const char *value);

// Retrieves the value associated with a key. Returns nullptr if the key is not
// found.
SHARED_LIB const char *map_get(MapHandle *handle, const char *key);

// Removes a key-value pair from the map. Returns true if the key was removed,
// false if not.
SHARED_LIB bool map_remove(MapHandle *handle, const char *key);

// Checks if the map contains a given key. Returns true if the key exists, false
// otherwise.
SHARED_LIB bool map_contains(MapHandle *handle, const char *key);

// Returns the number of key-value pairs in the map.
SHARED_LIB size_t map_size(MapHandle *handle);
// Frees the map and its associated resources.
SHARED_LIB void map_free(MapHandle *handle);
#ifdef __cplusplus
}
#endif
