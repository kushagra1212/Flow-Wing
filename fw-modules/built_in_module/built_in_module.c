/*
 * FlowWing Runtime Library
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This file provides the C runtime support for the FlowWing compiler,
 * including memory management (GC), dynamic typing, string manipulation,
 * and standard I/O wrappers.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include <stdint.h>
 #include <math.h>
#include <time.h>
 #include <gc.h> // Boehm GC
 #ifdef _MSC_VER
 #  define FG_THREAD_LOCAL __declspec(thread)
 #else
 #  define FG_THREAD_LOCAL __thread
 #endif

 // ==========================================
 // Forward Declarations
 // ==========================================
 
 void fg_panic(const char* fmt, const char* val);
 void fg_re(const char* errorMsg);
 
 // String Utils
 char* fg_cs(const char* str1, const char* str2);
 char* fg_itos(int num);
 char* fg_lltos(long long num);
 char* fg_i8tos(int8_t num);
 char* fg_dtos(double f);
 char* fg_ftos(float f);
 char* fg_ctos(int c);
 
 // Index Out of Bounds
 void fg_idx_oob(long long index, long long size);

 // String Indexing
 int fg_str_idx(const char* s, long long idx);
 int fg_dyn_str_idx(long long value_storage, long long type_tag, long long idx);
 void fg_str_set(char* s, long long idx, int value);
 void fg_dyn_str_set(long long value_storage, long long type_tag, long long idx, int value);
 
 // ==========================================
 // Error Handling
 // ==========================================
 
void fg_panic(const char* fmt, const char* val) {
    fprintf(stderr, "\033[91m"); // Start Red Color
    fprintf(stderr, fmt, val);
    fprintf(stderr, "\033[0m\n"); // Reset Color
    exit(1);
}

void fg_re(const char* errorMsg) {
    fprintf(stderr, "\033[91m%s\033[0m\n", errorMsg);
    exit(1);
}


// --- Function Implementations ---


char* fg_cs(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t totalLen = len1 + len2;

    char* concatStr = (char*)GC_MALLOC(totalLen + 1);
    if (concatStr == NULL) fg_re("Memory allocation failed in fg_cs");

    memcpy(concatStr, str1, len1);
    memcpy(concatStr + len1, str2, len2);
    concatStr[totalLen] = '\0';

    return concatStr;
}

int fg_sl(const char* str) {
    return strlen(str);
}

char* fg_itos(int num) {
    char* buffer = (char*)GC_MALLOC(12);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_itos");
    snprintf(buffer, 12, "%d", num);
    return buffer;
}

char* fg_i8tos(int8_t num) {
    // -128 requires 4 chars + 1 null terminator = 5 bytes
    char* buffer = (char*)GC_MALLOC(5); 
    if (buffer == NULL) fg_re("Memory allocation failed in fg_i8tos");
    snprintf(buffer, 5, "%d", num);
    return buffer;
}

char* fg_lltos(long long num) {
    char* buffer = (char*)GC_MALLOC(24);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_lltos");
    snprintf(buffer, 24, "%lld", num);
    return buffer;
}

char* fg_ctos(int c) {
    // 1. Allocate 5 bytes (Max UTF-8 char is 4 bytes + 1 null terminator)
    char* buffer = (char*)GC_MALLOC(5);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_ctos");

    // 2. Encode 32-bit int 'c' into UTF-8 bytes
    if (c < 0x80) { 
        // 1 Byte (ASCII: 'a' -> 97)
        buffer[0] = (char)c;
        buffer[1] = '\0';
    } else if (c < 0x800) { 
        // 2 Bytes
        buffer[0] = (char)(0xC0 | (c >> 6));
        buffer[1] = (char)(0x80 | (c & 0x3F));
        buffer[2] = '\0';
    } else if (c < 0x10000) { 
        // 3 Bytes
        buffer[0] = (char)(0xE0 | (c >> 12));
        buffer[1] = (char)(0x80 | ((c >> 6) & 0x3F));
        buffer[2] = (char)(0x80 | (c & 0x3F));
        buffer[3] = '\0';
    } else { 
        // 4 Bytes (Emoji: '🚀')
        buffer[0] = (char)(0xF0 | (c >> 18));
        buffer[1] = (char)(0x80 | ((c >> 12) & 0x3F));
        buffer[2] = (char)(0x80 | ((c >> 6) & 0x3F));
        buffer[3] = (char)(0x80 | (c & 0x3F));
        buffer[4] = '\0';
    }

    return buffer;
}

// SMART FORMATTING: Double
char* fg_dtos(double f) {
    char* buffer = (char*)GC_MALLOC(64);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_dtos");

    double abs_f = fabs(f);

    if (abs_f > 0 && (abs_f < 1e-5 || abs_f >= 1e14)) {
        snprintf(buffer, 64, "%.15g", f);
    } else {
        snprintf(buffer, 64, "%.15f", f);
        // Trim zeros
        size_t len = strlen(buffer);
        char* end = buffer + len - 1;
        while (end > buffer && *end == '0') {
            *end = '\0';
            end--;
        }
        if (*end == '.') *end = '\0';
    }
    return buffer;
}

// SMART FORMATTING: Float
char* fg_ftos(float f) {
    char* buffer = (char*)GC_MALLOC(64);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_ftos");

    float abs_f = fabsf(f);

    if (abs_f > 0 && (abs_f < 1e-5 || abs_f >= 1e7)) {
        snprintf(buffer, 64, "%.7g", f);
    } else {
        snprintf(buffer, 64, "%.7f", f);
        // Trim zeros
        size_t len = strlen(buffer);
        char* end = buffer + len - 1;
        while (end > buffer && *end == '0') {
            *end = '\0';
            end--;
        }
        if (*end == '.') *end = '\0';
    }
    return buffer;
}

char* fg_gmosc(const char* str) {
    size_t len = strlen(str);
    char* strPtr = (char*)GC_MALLOC(len + 1);
    if (strPtr == NULL) fg_re("Memory allocation failed in fg_gmosc");
    memcpy(strPtr, str, len + 1);
    return strPtr;
}

int fg_cmp(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

bool fg_lt(const char* str1, const char* str2) { return strcmp(str1, str2) < 0; }
bool fg_lte(const char* str1, const char* str2) { return strcmp(str1, str2) <= 0; }
bool fg_gt(const char* str1, const char* str2) { return strcmp(str1, str2) > 0; }
bool fg_gte(const char* str1, const char* str2) { return strcmp(str1, str2) >= 0; }
bool fg_eq(const char* str1, const char* str2) { return strcmp(str1, str2) == 0; }




int fg_sti(const char* str) {
    if (str == NULL) fg_panic("Runtime Error: Cannot convert NULL to Int.", "");
    char* endptr;
    long val = strtol(str, &endptr, 10);
    if (str == endptr || *endptr != '\0') {
        fg_panic("Runtime Error: Invalid input for Int conversion.\n  ▶ Value: \"%s\"", str);
    }
    return (int)val;
}


int fg_stc(const char* str) {
    if (str == NULL) {
        fg_panic("Runtime Error: Cannot convert NULL to Char.", "");
    }
    
    // 1. Check for Empty String
    if (str[0] == '\0') {
        fg_panic("Runtime Error: Cannot convert empty string to Char.", "");
    }

    const unsigned char* bytes = (const unsigned char*)str;
    int code_point = 0;
    int num_bytes = 0;

    // 2. Decode UTF-8 to Code Point
    if (bytes[0] < 0x80) {
        // 1-byte sequence (0xxxxxxx) - Standard ASCII
        code_point = bytes[0];
        num_bytes = 1;
    } 
    else if ((bytes[0] & 0xE0) == 0xC0) {
        // 2-byte sequence (110xxxxx 10xxxxxx)
        code_point = ((bytes[0] & 0x1F) << 6) | 
                     (bytes[1] & 0x3F);
        num_bytes = 2;
    } 
    else if ((bytes[0] & 0xF0) == 0xE0) {
        // 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
        code_point = ((bytes[0] & 0x0F) << 12) | 
                     ((bytes[1] & 0x3F) << 6) | 
                     (bytes[2] & 0x3F);
        num_bytes = 3;
    } 
    else if ((bytes[0] & 0xF8) == 0xF0) {
        // 4-byte sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
        code_point = ((bytes[0] & 0x07) << 18) | 
                     ((bytes[1] & 0x3F) << 12) | 
                     ((bytes[2] & 0x3F) << 6) | 
                     (bytes[3] & 0x3F);
        num_bytes = 4;
    } 
    else {
        fg_panic("Runtime Error: Invalid UTF-8 sequence in String to Char conversion.\n  ▶ String: \"%s\"", str);
    }

    // 3. Strict Length Check
    // If there is any character data AFTER the first char, throw error.
    if (str[num_bytes] != '\0') {
        fg_panic("Runtime Error: String contains more than one character.\n  ▶ Cannot convert \"%s\" to a single Char.", str);
    }

    return code_point;
}


long long fg_stl(const char* str) {
    if (str == NULL) fg_panic("Runtime Error: Cannot convert NULL to Long.", "");
    char* endptr;
    long long val = strtoll(str, &endptr, 10);
    if (str == endptr || *endptr != '\0') {
        fg_panic("Runtime Error: Invalid input for Long conversion.\n  ▶ Value: \"%s\"", str);
    }
    return val;
}

double fg_std(const char* str) {
    if (str == NULL) fg_panic("Runtime Error: Cannot convert NULL to Decimal.", "");
    char* endptr;
    double val = strtod(str, &endptr);
    if (str == endptr || *endptr != '\0') {
        fg_panic("Runtime Error: Invalid input for Decimal(Double) conversion.\n  ▶ Value: \"%s\"", str);
    }
    return val;
}

float fg_stf(const char* str) {
    if (str == NULL) fg_panic("Runtime Error: Cannot convert NULL to Decimal32.", "");
    char* endptr;
    float val = strtof(str, &endptr);
    if (str == endptr || *endptr != '\0') {
        fg_panic("Runtime Error: Invalid input for Decimal32(Float) conversion.\n  ▶ Value: \"%s\"", str);
    }
    return val;
}
 // ==========================================
 // Public Print Functions
 // ==========================================
 
 void fg_pf(const char* str) {
     if (!str) printf("(null)");
     else printf("%s", str);
 }
 
 // Initializer for GC (Call this at start of main if needed, or rely on auto-init)

 void fg_init_runtime() {
    static bool initialized = false;
  if (!initialized) {
        GC_INIT();
        initialized = true;
    }
 }

 // ==========================================
// OBJECT PRINT CYCLE DETECTION (Thread-Safe)
// ==========================================

#define INITIAL_STACK_CAP 32
#define HARD_DEPTH_LIMIT 20000 
#define SHRINK_THRESHOLD 1024

// Thread-Local Storage for safety in concurrent environments
static FG_THREAD_LOCAL void** visited_stack = NULL;
static FG_THREAD_LOCAL int visited_capacity = 0;
static FG_THREAD_LOCAL int visited_count = 0;

void ensure_visit_stack_capacity() {
    if (visited_count >= visited_capacity) {
        int new_cap = (visited_capacity == 0) ? INITIAL_STACK_CAP : visited_capacity * 2;
        
        // Use realloc (Manual memory management). 
        // This memory is runtime infrastructure, not user garbage.
        void** new_stack = (void**)realloc(visited_stack, new_cap * sizeof(void*));
        
        if (!new_stack) {
            fg_panic("Runtime Error: Out of memory in printer cycle detection.", "");
        }
        
        visited_stack = new_stack;
        visited_capacity = new_cap;
    }
}

bool fg_print_enter_object(void* ptr) {
    if (ptr == NULL) {
        fg_pf("null");
        return false;
    }

    // 1. Cycle Check (Linear scan of current path)
    for (int i = 0; i < visited_count; i++) {
        if (visited_stack[i] == ptr) {
            fg_pf("<Cycle>");
            return false;
        }
    }

    // 2. Hard Depth Limit (Prevent Segfault)
    if (visited_count >= HARD_DEPTH_LIMIT) {
        fg_pf("<Stack Depth Limit>"); 
        return false;
    }

    // 3. Push to Stack
    ensure_visit_stack_capacity();
    visited_stack[visited_count++] = ptr;
    fg_pf("{ ");
    return true;
}

void fg_print_exit_object() {
    if (visited_count > 0) {
        visited_count--;
    }
    fg_pf(" }");

    // --- SMART SHRINK STRATEGY ---
    // If we are back at the top level (count == 0), check if we
    // are hoarding too much memory.
    if (visited_count == 0) {
        if (visited_capacity > SHRINK_THRESHOLD) {
            // Free excess memory to avoid ghost space
            free(visited_stack);
            visited_stack = NULL;
            visited_capacity = 0;
        }
        // Otherwise, keep the small buffer allocated for performance (Warm Cache)
    }
}

void fg_idx_oob(long long index, long long size) {
    char* msg = (char*)GC_MALLOC(256); 
    
    if (msg == NULL) {
        fprintf(stderr, "\033[91mFatal Error: OOM during Index Out of Bounds check.\033[0m\n");
        exit(1);
    }

    snprintf(msg, 256, 
        "Runtime Error: Array Index Out of Bounds.\n"
        "  \u25b6 Index: %lld\n"
        "  \u25b6 Bounds: [0 .. %lld)", 
        index, size
    );

    // 3. Delegate to your existing panic function
    // We pass "%s" as the fmt, so 'msg' is treated as the value to print.
    fg_panic("%s", msg);
}

// ==========================================
// String Indexing
// ==========================================

int fg_str_idx(const char* s, long long idx) {
    if (s == NULL) {
        fg_re("Runtime Error: Cannot index null string.");
    }
    long long len = (long long)strlen(s);
    if (idx < 0 || idx >= len) {
        char* msg = (char*)GC_MALLOC(256);
        if (msg == NULL) {
            fprintf(stderr, "\033[91mFatal Error: OOM during string index bounds check.\033[0m\n");
            exit(1);
        }
        snprintf(msg, 256,
            "Runtime Error: String Index Out of Bounds.\n"
            "  \u25b6 Index: %lld\n"
            "  \u25b6 Bounds: [0 .. %lld)",
            idx, len);
        fg_panic("%s", msg);
    }
    return (int)(unsigned char)s[idx];
}

// DynamicValueType::STRING == 5 (must match DynamicValueHandler.h)
#define FG_DYN_TAG_STRING 5

int fg_dyn_str_idx(long long value_storage, long long type_tag, long long idx) {
    if (type_tag != FG_DYN_TAG_STRING) {
        fg_re("Runtime Error: Cannot index a non-string dynamic value.");
    }
    // value_storage holds the char* pointer bit-cast to i64
    const char* s = (const char*)(uintptr_t)(unsigned long long)value_storage;
    return fg_str_idx(s, idx);
}

void fg_str_set(char* s, long long idx, int value) {
    if (s == NULL) {
        fg_re("Runtime Error: Cannot index null string.");
    }

    long long len = (long long)strlen(s);
    if (idx < 0 || idx >= len) {
        char* msg = (char*)GC_MALLOC(256);
        if (msg == NULL) {
            fprintf(stderr, "\033[91mFatal Error: OOM during string index bounds check.\033[0m\n");
            exit(1);
        }
        snprintf(msg, 256,
            "Runtime Error: String Index Out of Bounds.\n"
            "  \u25b6 Index: %lld\n"
            "  \u25b6 Bounds: [0 .. %lld)",
            idx, len);
        fg_panic("%s", msg);
    }

    s[idx] = (char)value;
}

void fg_dyn_str_set(long long value_storage, long long type_tag, long long idx, int value) {
    if (type_tag != FG_DYN_TAG_STRING) {
        fg_re("Runtime Error: Cannot index a non-string dynamic value.");
    }

    char* s = (char*)(uintptr_t)(unsigned long long)value_storage;
    fg_str_set(s, idx, value);
}


static char* fg_script_dir = NULL;

// New function to be called by the Engine (C++) during startup
void fg_set_script_anchor(const char* absolute_dir_path) {
    // No need to search for slashes; we trust the compiler sent the dir
    size_t len = strlen(absolute_dir_path);
    fg_script_dir = (char*)GC_MALLOC_ATOMIC(len + 1);
    memcpy(fg_script_dir, absolute_dir_path, len + 1);
    
}

// The API exposed to the .fg script (The equivalent of __dirname)
char* fg_get_script_dir() {
    if (fg_script_dir == NULL) {
        fg_re("Runtime Error: Script anchor not initialized.");
    }
    // Return a copy so the script can manipulate it without breaking the anchor
    return fg_script_dir; 
}

// ==========================================
// sys Module Runtime Support
// ==========================================

static int fg_argc = 0;
static char **fg_argv = NULL;

void fg_store_args(int argc, char **argv) {
    fg_argc = argc;
    fg_argv = argv;
}

int fg_get_arg_count(void) {
    return fg_argc;
}

char* fg_get_arg(int index) {
    if (fg_argv == NULL || index < 0 || index >= fg_argc) {
        return NULL;
    }
    return fg_argv[index];
}

void fg_exit(int code) {
    exit(code);
}

long long fg_timestamp(void) {
    return (long long)time(NULL);
}

void fg_runtime_error(const char* msg) {
    fg_re(msg);
}
