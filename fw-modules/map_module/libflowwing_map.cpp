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


#include <cstdint>
#include <cstring>
#include <gc/gc.h>
#include <string>
#include <unordered_map>

extern "C" {
    // Make sure this matches your runtime exactly
    struct DynamicValue {
        int32_t tag;
        int64_t value;
    };
}

namespace {
    template <typename Value>
    struct TypedMapHandle {
        using map_type = std::unordered_map<std::string, Value>;
        map_type *values;
    };

    using DynMapHandle = TypedMapHandle<DynamicValue>;

    template <typename Handle>
    void finalizeHandle(void *raw_handle, void *) {
        auto *handle = static_cast<Handle *>(raw_handle);
        delete handle->values;
        handle->values = nullptr;
    }

    template <typename Handle>
    Handle *allocateHandle() {
        auto *handle = static_cast<Handle *>(GC_MALLOC(sizeof(Handle)));
        if (handle == nullptr) return nullptr;

        handle->values = new typename Handle::map_type();
        GC_register_finalizer(handle, finalizeHandle<Handle>, nullptr, nullptr, nullptr);
        return handle;
    }

    std::string toString(const char *value) {
        return value == nullptr ? "" : value;
    }

    template <typename Handle>
    typename Handle::map_type *getMap(void *raw_handle) {
        auto *handle = static_cast<Handle *>(raw_handle);
        return handle == nullptr ? nullptr : handle->values;
    }

    template <typename Handle, typename Value>
    void mapSet(void *raw_handle, const char *key, const Value &value) {
        if (auto *map = getMap<Handle>(raw_handle)) {
            (*map)[toString(key)] = value;
        }
    }

    template <typename Handle, typename Value>
    Value mapGetOr(void *raw_handle, const char *key, const Value &fallback) {
        auto *map = getMap<Handle>(raw_handle);
        if (map == nullptr) return fallback;

        const auto iterator = map->find(toString(key));
        if (iterator == map->end()) return fallback;

        return iterator->second;
    }
} // namespace

// --- EXPORTED FFI API ---
extern "C" {
  int64_t dyn_map_new() { 
    // Cast the memory address to a 64-bit integer
    return reinterpret_cast<int64_t>(allocateHandle<DynMapHandle>()); 
}

void dyn_map_set(int64_t raw_handle, const char *key, DynamicValue* value) {
    void* map_handle = reinterpret_cast<void*>(raw_handle);
    if (value != nullptr) {
        mapSet<DynMapHandle>(map_handle, key, *value);
    }
}

void dyn_map_get_or(DynamicValue *ret_slot, int64_t raw_handle, const char *key, DynamicValue *fallback) {
    if (ret_slot == nullptr) return;
    void* map_handle = reinterpret_cast<void*>(raw_handle);
    
    DynamicValue fb = (fallback != nullptr) ? *fallback : DynamicValue{7, 0}; 
    *ret_slot = mapGetOr<DynMapHandle>(map_handle, key, fb);
}

bool dyn_map_remove(int64_t raw_handle, const char *key) {
    void* map_handle = reinterpret_cast<void*>(raw_handle);
    auto *map = getMap<DynMapHandle>(map_handle);
    return map != nullptr && map->erase(toString(key)) > 0;
}

bool dyn_map_contains(int64_t raw_handle, const char *key) {
    void* map_handle = reinterpret_cast<void*>(raw_handle);
    auto *map = getMap<DynMapHandle>(map_handle);
    return map != nullptr && map->find(toString(key)) != map->end();
}

int32_t dyn_map_size(int64_t raw_handle) {
    void* map_handle = reinterpret_cast<void*>(raw_handle);
    auto *map = getMap<DynMapHandle>(map_handle);
    return map == nullptr ? 0 : static_cast<int32_t>(map->size());
}

void dyn_map_clear(int64_t raw_handle) { 
    void* map_handle = reinterpret_cast<void*>(raw_handle);
    auto *map = getMap<DynMapHandle>(map_handle);
    if (map) map->clear();
}
}