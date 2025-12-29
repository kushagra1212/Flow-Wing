#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <gc.h> // Header for the Boehm Garbage Collector

// --- Function Declarations (Forward declarations) ---
void fg_pf(const char* str);
char* fg_cs(const char* str1, const char* str2);
int fg_sl(const char* str);
char* fg_itos(int num);
char* fg_dtos(double f);
char* fg_ftos(float f);
char* fg_gmosc(const char* str);
int fg_cmp(const char* str1, const char* str2);
bool fg_lt(const char* str1, const char* str2);
bool fg_lte(const char* str1, const char* str2);
bool fg_gt(const char* str1, const char* str2);
bool fg_gte(const char* str1, const char* str2);
bool fg_eq(const char* str1, const char* str2);
char* fg_gi();
int fg_sti(const char* str);
long long fg_stl(const char* str);
double fg_std(const char* str);
float fg_stf(const char* str);
char* fg_lltos(long long num);
char* fg_ctos(int c);

// Error Handling
void fg_panic(const char* fmt, const char* val);
void fg_re(const char* errorMsg); // Legacy/Generic handler

// --- Helper Implementation ---

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

void fg_pf(const char* str) {
    printf("%s", str); 
}

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

// --- SAFE CONVERSIONS (Replaced) ---

int fg_sti(const char* str) {
    if (str == NULL) fg_panic("Runtime Error: Cannot convert NULL to Int.", "");
    char* endptr;
    long val = strtol(str, &endptr, 10);
    if (str == endptr || *endptr != '\0') {
        fg_panic("Runtime Error: Invalid input for Int conversion.\n  ▶ Value: \"%s\"", str);
    }
    return (int)val;
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