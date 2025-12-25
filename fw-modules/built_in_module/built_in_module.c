#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
void fg_re(const char* errorMsg);
char* fg_lltos(long long num); // For int64
char* fg_ctos(char c);         // For int8 (char)


// --- Function Implementations ---

void fg_pf(const char* str) {
        printf("%s", str);
}

char* fg_cs(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t totalLen = len1 + len2;

    // Use GC_MALLOC for garbage-collected memory
    char* concatStr = (char*)GC_MALLOC(totalLen + 1);
    if (concatStr == NULL) {
        fg_re("Memory allocation failed in fg_cs");
    }

    memcpy(concatStr, str1, len1);
    memcpy(concatStr + len1, str2, len2);
    concatStr[totalLen] = '\0';

    return concatStr;
}

int fg_sl(const char* str) {
    return strlen(str);
}

char* fg_itos(int num) {
    // Allocate a buffer that is large enough for any 32-bit integer.
    char* buffer = (char*)GC_MALLOC(12); // "-2147483648\0" is 12 chars
     if (buffer == NULL) {
        fg_re("Memory allocation failed in fg_itos");
    }
    snprintf(buffer, 12, "%d", num);
    return buffer;
}


// 1. Long Long to String (for Int64)
char* fg_lltos(long long num) {
    char* buffer = (char*)GC_MALLOC(24); // Enough for 64-bit int
    if (buffer == NULL) fg_re("Memory allocation failed in fg_lltos");
    snprintf(buffer, 24, "%lld", num);
    return buffer;
}

// 2. Char to String (for Int8)
char* fg_ctos(char c) {
    char* buffer = (char*)GC_MALLOC(2); // 1 char + null terminator
    if (buffer == NULL) fg_re("Memory allocation failed in fg_ctos");
    buffer[0] = c;
    buffer[1] = '\0';
    return buffer;
}


char* fg_dtos(double f) {
    // 64 bytes is plenty for %g (max length is usually ~24 chars)
    char* buffer = (char*)GC_MALLOC(64);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_dtos");
    
    // %.15g automatically chooses the best format and precision for Double
    snprintf(buffer, 64, "%.15g", f); 
    return buffer;
}

char* fg_ftos(float f) {
    char* buffer = (char*)GC_MALLOC(64);
    if (buffer == NULL) fg_re("Memory allocation failed in fg_ftos");
    
    // %.7g is the correct precision limit for Float
    snprintf(buffer, 64, "%.7g", f); 
    return buffer;
}

char* fg_gmosc(const char* str) {
    size_t len = strlen(str);
    char* strPtr = (char*)GC_MALLOC(len + 1);
     if (strPtr == NULL) {
        fg_re("Memory allocation failed in fg_gmosc");
    }
    memcpy(strPtr, str, len + 1);
    return strPtr;
}

int fg_cmp(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

bool fg_lt(const char* str1, const char* str2) {
    return strcmp(str1, str2) < 0;
}

bool fg_lte(const char* str1, const char* str2) {
    return strcmp(str1, str2) <= 0;
}

bool fg_gt(const char* str1, const char* str2) {
    return strcmp(str1, str2) > 0;
}

bool fg_gte(const char* str1, const char* str2) {
    return strcmp(str1, str2) >= 0;
}

bool fg_eq(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

char* fg_gi() {
    // Allocate a large buffer for input.
    char* buffer = (char*)GC_MALLOC(1000001);
    if (buffer == NULL) {
        fg_re("Memory allocation failed in fg_gi");
    }

    if (scanf("%1000000s", buffer) != 1) {
        // Handle potential input error, maybe return an empty string
        buffer[0] = '\0';
    }
    return buffer;
}

int fg_sti(const char* str) {
    return atoi(str);
}

long long fg_stl(const char* str) {
    return atoll(str);
}

double fg_std(const char* str) {
    return strtod(str, NULL);
}

float fg_stf(const char* str) {
    return strtof(str, NULL);
}

void fg_re(const char* errorMsg) {
    puts(errorMsg);
    exit(1);
}