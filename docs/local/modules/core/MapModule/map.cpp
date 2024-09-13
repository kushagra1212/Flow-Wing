// utils.cpp
#include <string>
#include <unordered_map>

extern "C" {

// Define a handle for the map.
typedef struct {
  void *map;
} MapHandle;

// Creates a new map and returns a handle to it.
MapHandle *map_new() {
  return new MapHandle{new std::unordered_map<std::string, std::string>()};
}

// Inserts a key-value pair into the map.
void map_insert(MapHandle *handle, const char *key, const char *value) {
  auto map =
      static_cast<std::unordered_map<std::string, std::string> *>(handle->map);
  (*map)[key] = value;
}

// Retrieves the value associated with a key. Returns nullptr if the key is not
// found.
const char *map_get(MapHandle *handle, const char *key) {
  auto map =
      static_cast<std::unordered_map<std::string, std::string> *>(handle->map);
  auto it = map->find(key);
  if (it != map->end()) {
    return it->second.c_str();
  }
  return nullptr;
}

// Removes a key-value pair from the map. Returns true if the key was removed,
// false if not.
bool map_remove(MapHandle *handle, const char *key) {
  auto map =
      static_cast<std::unordered_map<std::string, std::string> *>(handle->map);
  auto it = map->find(key);
  if (it != map->end()) {
    map->erase(it);
    return true;
  }
  return false;
}

// Checks if the map contains a given key. Returns true if the key exists, false
// otherwise.
bool map_contains(MapHandle *handle, const char *key) {
  auto map =
      static_cast<std::unordered_map<std::string, std::string> *>(handle->map);
  return map->find(key) != map->end();
}

// Returns the number of key-value pairs in the map.
size_t map_size(MapHandle *handle) {
  auto map =
      static_cast<std::unordered_map<std::string, std::string> *>(handle->map);
  return map->size();
}

// Frees the map and its associated resources.
void map_free(MapHandle *handle) {
  delete static_cast<std::unordered_map<std::string, std::string> *>(
      handle->map);
  delete handle;
}
}
