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
 #include <vector>
 #include <gc/gc.h>
 #include <algorithm>
 #include <cstring>
 
 // Dynamic Tags from your runtime
 #define DYN_TAG_INT8    0
 #define DYN_TAG_INT32   1
 #define DYN_TAG_INT64   2
 #define DYN_TAG_FLOAT32 3
 #define DYN_TAG_FLOAT64 4
 #define DYN_TAG_STRING  5
 #define DYN_TAG_BOOLEAN 6
 #define DYN_TAG_NIRAST  7
 #define DYN_TAG_CHAR    8
 
 extern "C" {
     struct DynamicValue {
         int32_t tag;
         int64_t value;
     };
 }
 
 namespace {
     struct VecHandle {
         std::vector<DynamicValue> *values;
     };
 
     void finalizeVecHandle(void *raw_handle, void *) {
         auto *handle = static_cast<VecHandle *>(raw_handle);
         delete handle->values;
         handle->values = nullptr;
     }
 
     VecHandle *allocateVecHandle() {
         auto *handle = static_cast<VecHandle *>(GC_MALLOC(sizeof(VecHandle)));
         if (handle == nullptr) return nullptr;
 
         handle->values = new std::vector<DynamicValue>();
         GC_register_finalizer(handle, finalizeVecHandle, nullptr, nullptr, nullptr);
         return handle;
     }
 
     std::vector<DynamicValue> *getVec(int64_t raw_handle) {
         void* ptr = reinterpret_cast<void*>(raw_handle);
         auto *handle = static_cast<VecHandle *>(ptr);
         return handle == nullptr ? nullptr : handle->values;
     }
 
     // Helper: Safely extract numbers for comparison
     double getAsDouble(const DynamicValue& v) {
         if (v.tag == DYN_TAG_FLOAT64) {
             double d; std::memcpy(&d, &v.value, sizeof(double)); return d;
         }
         if (v.tag == DYN_TAG_FLOAT32) {
             float f; std::memcpy(&f, &v.value, sizeof(float)); return static_cast<double>(f);
         }
         return static_cast<double>(v.value);
     }
 
     // Helper: Compare two dynamic values for Sorting
     bool compareDynAsc(const DynamicValue& a, const DynamicValue& b) {
         bool a_num = (a.tag >= 0 && a.tag <= 4) || a.tag == DYN_TAG_CHAR;
         bool b_num = (b.tag >= 0 && b.tag <= 4) || b.tag == DYN_TAG_CHAR;
         
         if (a_num && b_num) return getAsDouble(a) < getAsDouble(b);
         
         if (a.tag == b.tag && a.tag == DYN_TAG_STRING) {
             const char* sa = reinterpret_cast<const char*>(a.value);
             const char* sb = reinterpret_cast<const char*>(b.value);
             if (!sa) return true;
             if (!sb) return false;
             return std::strcmp(sa, sb) < 0;
         }
         // If types are totally different, sort by tag ID to group types together
         return a.tag < b.tag;
     }
 
     // Helper: Check equality for indexOf
     bool equalsDyn(const DynamicValue& a, const DynamicValue& b) {
         bool a_num = (a.tag >= 0 && a.tag <= 4) || a.tag == DYN_TAG_CHAR;
         bool b_num = (b.tag >= 0 && b.tag <= 4) || b.tag == DYN_TAG_CHAR;
         
         if (a_num && b_num) return getAsDouble(a) == getAsDouble(b);
         
         if (a.tag == b.tag) {
              if (a.tag == DYN_TAG_STRING) {
                   const char* sa = reinterpret_cast<const char*>(a.value);
                   const char* sb = reinterpret_cast<const char*>(b.value);
                   if (!sa && !sb) return true;
                   if (!sa || !sb) return false;
                   return std::strcmp(sa, sb) == 0;
              }
              return a.value == b.value;
         }
         return false;
     }
 } // namespace
 
 // --- EXPORTED FFI API ---
 extern "C" {
     int64_t dyn_list_new() {
         return reinterpret_cast<int64_t>(allocateVecHandle());
     }
 
     void dyn_list_push(int64_t raw_handle, DynamicValue* value) {
         if (value && getVec(raw_handle)) getVec(raw_handle)->push_back(*value);
     }
 
     void dyn_list_pop(DynamicValue *ret_slot, int64_t raw_handle) {
         if (!ret_slot) return;
         auto *vec = getVec(raw_handle);
         if (vec && !vec->empty()) {
             *ret_slot = vec->back();
             vec->pop_back();
         } else {
             *ret_slot = DynamicValue{DYN_TAG_NIRAST, 0};
         }
     }
 
     void dyn_list_get(DynamicValue *ret_slot, int64_t raw_handle, int32_t index) {
         if (!ret_slot) return;
         auto *vec = getVec(raw_handle);
         if (vec && index >= 0 && index < vec->size()) {
             *ret_slot = (*vec)[index];
         } else {
             *ret_slot = DynamicValue{DYN_TAG_NIRAST, 0};
         }
     }
 
     void dyn_list_set(int64_t raw_handle, int32_t index, DynamicValue* value) {
         auto *vec = getVec(raw_handle);
         if (value && vec && index >= 0 && index < vec->size()) {
             (*vec)[index] = *value;
         }
     }
 
     void dyn_list_insert(int64_t raw_handle, int32_t index, DynamicValue* value) {
         auto *vec = getVec(raw_handle);
         if (value && vec && index >= 0 && index <= vec->size()) {
             vec->insert(vec->begin() + index, *value);
         }
     }
 
     void dyn_list_remove_at(DynamicValue *ret_slot, int64_t raw_handle, int32_t index) {
         if (!ret_slot) return;
         auto *vec = getVec(raw_handle);
         if (vec && index >= 0 && index < vec->size()) {
             *ret_slot = (*vec)[index];
             vec->erase(vec->begin() + index);
         } else {
             *ret_slot = DynamicValue{DYN_TAG_NIRAST, 0};
         }
     }
 
     int32_t dyn_list_size(int64_t raw_handle) {
         auto *vec = getVec(raw_handle);
         return vec ? static_cast<int32_t>(vec->size()) : 0;
     }
 
     void dyn_list_clear(int64_t raw_handle) {
         if (auto *vec = getVec(raw_handle)) vec->clear();
     }
 
     // --- NEW ALGORITHMS ---
 
     // SORT: Uses highly optimized Introsort
     void dyn_list_sort(int64_t raw_handle, bool ascending) {
         if (auto *vec = getVec(raw_handle)) {
             if (ascending) {
                 std::sort(vec->begin(), vec->end(), compareDynAsc);
             } else {
                 // Lambda for descending sort
                 std::sort(vec->begin(), vec->end(), [](const DynamicValue& a, const DynamicValue& b) {
                     return compareDynAsc(b, a);
                 });
             }
         }
     }
 
     // REVERSE: $O(N)$ in-place array reversal
     void dyn_list_reverse(int64_t raw_handle) {
         if (auto *vec = getVec(raw_handle)) {
             std::reverse(vec->begin(), vec->end());
         }
     }
 
     // INDEX OF: $O(N)$ linear search. Fallback is passed BY VALUE to avoid asterisks
     int32_t dyn_list_index_of(int64_t raw_handle, DynamicValue* target) {
        if (target == nullptr) return -1;
        
        if (auto *vec = getVec(raw_handle)) {
            for (size_t i = 0; i < vec->size(); ++i) {
                // Dereference target pointer for the comparison
                if (equalsDyn((*vec)[i], *target)) {
                    return static_cast<int32_t>(i);
                }
            }
        }
        return -1; // Not found
    }
 }