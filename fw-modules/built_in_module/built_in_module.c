#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <gc.h> // Header for the Boehm Garbage Collector

// --- Function Declarations (Forward declarations) ---
void print(const char* str, bool newline);
char* concat_strings(const char* str1, const char* str2);
int string_length(const char* str);
char* itos(int num);
char* dtos(double f);
char* get_malloc_ptr_of_string_constant(const char* str);
int compare_strings(const char* str1, const char* str2);
bool less_than_strings(const char* str1, const char* str2);
bool less_than_or_equal_strings(const char* str1, const char* str2);
bool greater_than_strings(const char* str1, const char* str2);
bool greater_than_or_equal_strings(const char* str1, const char* str2);
bool equal_strings(const char* str1, const char* str2);
char* get_input();
int string_to_int(const char* str);
long long string_to_long(const char* str);
double string_to_double(const char* str);
void raise_exception(const char* errorMsg);


// --- Function Implementations ---

void print(const char* str, bool newline) {
    if (newline) {
        printf("%s\n", str);
    } else {
        printf("%s", str);
    }
}

char* concat_strings(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t totalLen = len1 + len2;

    // Use GC_MALLOC for garbage-collected memory
    char* concatStr = (char*)GC_MALLOC(totalLen + 1);
    if (concatStr == NULL) {
        raise_exception("Memory allocation failed in concat_strings");
    }

    memcpy(concatStr, str1, len1);
    memcpy(concatStr + len1, str2, len2);
    concatStr[totalLen] = '\0';

    return concatStr;
}

int string_length(const char* str) {
    return strlen(str);
}

char* itos(int num) {
    // Allocate a buffer that is large enough for any 32-bit integer.
    char* buffer = (char*)GC_MALLOC(12); // "-2147483648\0" is 12 chars
     if (buffer == NULL) {
        raise_exception("Memory allocation failed in itos");
    }
    snprintf(buffer, 12, "%d", num);
    return buffer;
}

char* dtos(double f) {
    // Allocate a sufficiently large buffer for double representation.
    char* buffer = (char*)GC_MALLOC(64);
     if (buffer == NULL) {
        raise_exception("Memory allocation failed in dtos");
    }
    // "%.14f" matches your LLVM IR format string
    snprintf(buffer, 64, "%.14f", f);
    return buffer;
}

char* get_malloc_ptr_of_string_constant(const char* str) {
    size_t len = strlen(str);
    char* strPtr = (char*)GC_MALLOC(len + 1);
     if (strPtr == NULL) {
        raise_exception("Memory allocation failed in get_malloc_ptr_of_string_constant");
    }
    memcpy(strPtr, str, len + 1);
    return strPtr;
}

int compare_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

bool less_than_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2) < 0;
}

bool less_than_or_equal_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2) <= 0;
}

bool greater_than_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2) > 0;
}

bool greater_than_or_equal_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2) >= 0;
}

bool equal_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

char* get_input() {
    // Allocate a large buffer for input.
    char* buffer = (char*)GC_MALLOC(1000001);
    if (buffer == NULL) {
        raise_exception("Memory allocation failed in get_input");
    }

    if (scanf("%1000000s", buffer) != 1) {
        // Handle potential input error, maybe return an empty string
        buffer[0] = '\0';
    }
    return buffer;
}

int string_to_int(const char* str) {
    return atoi(str);
}

long long string_to_long(const char* str) {
    return atoll(str);
}

double string_to_double(const char* str) {
    return atof(str);
}

void raise_exception(const char* errorMsg) {
    puts(errorMsg);
    exit(1);
}