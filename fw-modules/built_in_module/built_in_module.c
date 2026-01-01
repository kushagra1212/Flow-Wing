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
 #include <gc.h> // Boehm GC
 

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

char* fg_gi() {
    char* buffer = (char*)GC_MALLOC(1000001);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_gi");

    if (scanf("%1000000s", buffer) != 1) {
        buffer[0] = '\0';
    }
    return buffer;
}


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
     GC_INIT();
 }