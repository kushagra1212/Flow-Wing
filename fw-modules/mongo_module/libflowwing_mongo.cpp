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

/*
 * FlowWing Compiler - MongoDB Module Bridge
 *
 * Bridges the libmongoc C driver (built as a Flow-Wing dependency under
 * .fw_dependencies/install/) to Flow-Wing's `module [mongo]` API.
 *
 * Single-threaded model (vortex serves on one thread); handle tables hold
 * mongoc_client_t / mongoc_collection_t / mongoc_cursor_t pointers, keyed
 * by int64 with slot 0 reserved for "invalid". Thread-local string buffers
 * carry returned JSON and last-error text; caller does not free.
 */

#include <mongoc/mongoc.h>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

#define MAX_CLIENTS 64
static mongoc_client_t* _clients[MAX_CLIENTS] = {nullptr};

#define MAX_COLLECTIONS 256
static mongoc_collection_t* _collections[MAX_COLLECTIONS] = {nullptr};

static int64_t _alloc_collection_slot() {
    for (int64_t i = 1; i < MAX_COLLECTIONS; ++i) {
        if (_collections[i] == nullptr) return i;
    }
    return 0;
}

#define MAX_CURSORS 256
static mongoc_cursor_t* _cursors[MAX_CURSORS] = {nullptr};

static int64_t _alloc_cursor_slot() {
    for (int64_t i = 1; i < MAX_CURSORS; ++i) {
        if (_cursors[i] == nullptr) return i;
    }
    return 0;
}

thread_local std::string _last_error;
thread_local std::string _find_one_result;
thread_local std::string _cursor_next_result;

static std::once_flag _init_flag;
static void _ensure_init() {
    std::call_once(_init_flag, []() { mongoc_init(); });
}

static int64_t _alloc_client_slot() {
    for (int64_t i = 1; i < MAX_CLIENTS; ++i) {
        if (_clients[i] == nullptr) return i;
    }
    return 0;
}

extern "C" {

int64_t _mongo_client_new(const char* uri) {
    _ensure_init();
    _last_error.clear();
    if (uri == nullptr || *uri == '\0') {
        _last_error = "mongo: empty uri";
        return 0;
    }
    bson_error_t err;
    mongoc_uri_t* parsed = mongoc_uri_new_with_error(uri, &err);
    if (parsed == nullptr) {
        _last_error = err.message;
        return 0;
    }
    mongoc_client_t* client = mongoc_client_new_from_uri(parsed);
    mongoc_uri_destroy(parsed);
    if (client == nullptr) {
        _last_error = "mongo: client construction failed";
        return 0;
    }
    int64_t h = _alloc_client_slot();
    if (h == 0) {
        mongoc_client_destroy(client);
        _last_error = "mongo: client handle table full";
        return 0;
    }
    _clients[h] = client;
    return h;
}

void _mongo_client_close(int64_t h) {
    if (h <= 0 || h >= MAX_CLIENTS || _clients[h] == nullptr) return;
    // Collections and cursors borrow the client pointer internally — once the
    // client is destroyed they dangle. v1 is single-client, so close-all is safe.
    // When multi-client lands later, track parent client per collection/cursor.
    for (int64_t i = 1; i < MAX_COLLECTIONS; ++i) {
        if (_collections[i] != nullptr) {
            mongoc_collection_destroy(_collections[i]);
            _collections[i] = nullptr;
        }
    }
    for (int64_t i = 1; i < MAX_CURSORS; ++i) {
        if (_cursors[i] != nullptr) {
            mongoc_cursor_destroy(_cursors[i]);
            _cursors[i] = nullptr;
        }
    }
    mongoc_client_destroy(_clients[h]);
    _clients[h] = nullptr;
}

int64_t _mongo_get_collection(int64_t client_h, const char* db, const char* coll) {
    _last_error.clear();
    if (client_h <= 0 || client_h >= MAX_CLIENTS || _clients[client_h] == nullptr) {
        _last_error = "mongo: invalid client handle";
        return 0;
    }
    if (db == nullptr || coll == nullptr) {
        _last_error = "mongo: null db or collection name";
        return 0;
    }
    mongoc_collection_t* c = mongoc_client_get_collection(_clients[client_h], db, coll);
    if (c == nullptr) {
        _last_error = "mongo: get_collection returned null";
        return 0;
    }
    int64_t h = _alloc_collection_slot();
    if (h == 0) {
        mongoc_collection_destroy(c);
        _last_error = "mongo: collection handle table full";
        return 0;
    }
    _collections[h] = c;
    return h;
}

int64_t _mongo_insert_one(int64_t coll_h, const char* json) {
    _last_error.clear();
    if (coll_h <= 0 || coll_h >= MAX_COLLECTIONS || _collections[coll_h] == nullptr) {
        _last_error = "mongo: invalid collection handle";
        return 0;
    }
    if (json == nullptr) {
        _last_error = "mongo: null json";
        return 0;
    }
    bson_error_t err;
    bson_t* doc = bson_new_from_json(reinterpret_cast<const uint8_t*>(json), -1, &err);
    if (doc == nullptr) {
        _last_error = std::string("mongo: bad json: ") + err.message;
        return 0;
    }
    bool ok = mongoc_collection_insert_one(_collections[coll_h], doc, nullptr, nullptr, &err);
    bson_destroy(doc);
    if (!ok) {
        _last_error = err.message;
        return 0;
    }
    return 1;
}

int64_t _mongo_insert_many(int64_t coll_h, const char* jsonArray) {
    _last_error.clear();
    if (coll_h <= 0 || coll_h >= MAX_COLLECTIONS || _collections[coll_h] == nullptr) {
        _last_error = "mongo: invalid collection handle";
        return 0;
    }
    if (jsonArray == nullptr) {
        _last_error = "mongo: null jsonArray";
        return 0;
    }
    bson_error_t err;
    bson_t* arr = bson_new_from_json(reinterpret_cast<const uint8_t*>(jsonArray), -1, &err);
    if (arr == nullptr) {
        _last_error = std::string("mongo: bad json array: ") + err.message;
        return 0;
    }
    std::vector<bson_t*> docs;
    bson_iter_t it;
    if (!bson_iter_init(&it, arr)) {
        bson_destroy(arr);
        _last_error = "mongo: bson_iter_init failed";
        return 0;
    }
    while (bson_iter_next(&it)) {
        if (!BSON_ITER_HOLDS_DOCUMENT(&it)) {
            for (auto* d : docs) bson_destroy(d);
            bson_destroy(arr);
            _last_error = "mongo: array element is not a document";
            return 0;
        }
        const uint8_t* buf = nullptr;
        uint32_t len = 0;
        bson_iter_document(&it, &len, &buf);
        docs.push_back(bson_new_from_data(buf, len));
    }
    std::vector<const bson_t*> ptrs;
    ptrs.reserve(docs.size());
    for (auto* d : docs) ptrs.push_back(d);

    bool ok = mongoc_collection_insert_many(
        _collections[coll_h], ptrs.data(), ptrs.size(), nullptr, nullptr, &err);

    for (auto* d : docs) bson_destroy(d);
    bson_destroy(arr);

    if (!ok) {
        _last_error = err.message;
        return 0;
    }
    return 1;
}

int64_t _mongo_count(int64_t coll_h, const char* filterJson) {
    _last_error.clear();
    if (coll_h <= 0 || coll_h >= MAX_COLLECTIONS || _collections[coll_h] == nullptr) {
        _last_error = "mongo: invalid collection handle";
        return -1;
    }
    const char* fj = (filterJson == nullptr || *filterJson == '\0') ? "{}" : filterJson;
    bson_error_t err;
    bson_t* filter = bson_new_from_json(reinterpret_cast<const uint8_t*>(fj), -1, &err);
    if (filter == nullptr) {
        _last_error = std::string("mongo: bad filter json: ") + err.message;
        return -1;
    }
    int64_t n = mongoc_collection_count_documents(
        _collections[coll_h], filter, nullptr, nullptr, nullptr, &err);
    bson_destroy(filter);
    if (n < 0) {
        _last_error = err.message;
        return -1;
    }
    return n;
}

const char* _mongo_find_one(int64_t coll_h, const char* filterJson) {
    _last_error.clear();
    _find_one_result.clear();
    if (coll_h <= 0 || coll_h >= MAX_COLLECTIONS || _collections[coll_h] == nullptr) {
        _last_error = "mongo: invalid collection handle";
        return _find_one_result.c_str();
    }
    const char* fj = (filterJson == nullptr || *filterJson == '\0') ? "{}" : filterJson;
    bson_error_t err;
    bson_t* filter = bson_new_from_json(reinterpret_cast<const uint8_t*>(fj), -1, &err);
    if (filter == nullptr) {
        _last_error = std::string("mongo: bad filter json: ") + err.message;
        return _find_one_result.c_str();
    }
    bson_t opts = BSON_INITIALIZER;
    BSON_APPEND_INT64(&opts, "limit", 1);
    mongoc_cursor_t* cur = mongoc_collection_find_with_opts(
        _collections[coll_h], filter, &opts, nullptr);
    bson_destroy(filter);
    bson_destroy(&opts);

    const bson_t* doc = nullptr;
    if (mongoc_cursor_next(cur, &doc)) {
        char* json = bson_as_relaxed_extended_json(doc, nullptr);
        if (json != nullptr) {
            _find_one_result = json;
            bson_free(json);
        }
    } else if (mongoc_cursor_error(cur, &err)) {
        _last_error = err.message;
    }
    // empty result = "" with no error
    mongoc_cursor_destroy(cur);
    return _find_one_result.c_str();
}

int64_t _mongo_find(int64_t coll_h, const char* filterJson, int64_t limit) {
    _last_error.clear();
    if (coll_h <= 0 || coll_h >= MAX_COLLECTIONS || _collections[coll_h] == nullptr) {
        _last_error = "mongo: invalid collection handle";
        return 0;
    }
    const char* fj = (filterJson == nullptr || *filterJson == '\0') ? "{}" : filterJson;
    bson_error_t err;
    bson_t* filter = bson_new_from_json(reinterpret_cast<const uint8_t*>(fj), -1, &err);
    if (filter == nullptr) {
        _last_error = std::string("mongo: bad filter json: ") + err.message;
        return 0;
    }
    bson_t opts = BSON_INITIALIZER;
    if (limit > 0) BSON_APPEND_INT64(&opts, "limit", limit);

    mongoc_cursor_t* cur = mongoc_collection_find_with_opts(
        _collections[coll_h], filter, &opts, nullptr);
    bson_destroy(filter);
    bson_destroy(&opts);

    int64_t h = _alloc_cursor_slot();
    if (h == 0) {
        mongoc_cursor_destroy(cur);
        _last_error = "mongo: cursor handle table full";
        return 0;
    }
    _cursors[h] = cur;
    return h;
}

const char* _mongo_cursor_next(int64_t cur_h) {
    _last_error.clear();
    _cursor_next_result.clear();
    if (cur_h <= 0 || cur_h >= MAX_CURSORS || _cursors[cur_h] == nullptr) {
        _last_error = "mongo: invalid cursor handle";
        return _cursor_next_result.c_str();
    }
    const bson_t* doc = nullptr;
    if (!mongoc_cursor_next(_cursors[cur_h], &doc)) {
        bson_error_t err;
        if (mongoc_cursor_error(_cursors[cur_h], &err)) {
            _last_error = err.message;
        }
        return _cursor_next_result.c_str();  // "" = end-of-stream OR error
    }
    char* json = bson_as_relaxed_extended_json(doc, nullptr);
    if (json != nullptr) {
        _cursor_next_result = json;
        bson_free(json);
    }
    return _cursor_next_result.c_str();
}

void _mongo_cursor_close(int64_t cur_h) {
    if (cur_h <= 0 || cur_h >= MAX_CURSORS) return;
    if (_cursors[cur_h] != nullptr) {
        mongoc_cursor_destroy(_cursors[cur_h]);
        _cursors[cur_h] = nullptr;
    }
}

const char* _mongo_last_error() { return _last_error.c_str(); }

} // extern "C"
