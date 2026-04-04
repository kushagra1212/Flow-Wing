#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Forward declare GC_malloc if Flow-Wing manages memory via Garbage Collection.
// If you aren't using a GC for strings yet, replace GC_malloc with standard malloc.
extern void* GC_malloc(size_t size);

// Helper function to allocate memory for strings crossing the FFI boundary
static char* allocate_string(size_t length) {
    // Use GC_malloc so Flow-Wing's garbage collector cleans it up later.
    // Add +1 for the null terminator.
    return (char*)GC_malloc(length + 1); 
}

// 1. Length
int32_t strLength(const char* str1) {
    if (!str1) return 0;
    return (int32_t)strlen(str1);
}

// 2. To Upper
char* strToUpper(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* new_str = allocate_string(len);
    
    for (size_t i = 0; i < len; ++i) {
        new_str[i] = (char)toupper((unsigned char)str[i]);
    }
    new_str[len] = '\0';
    return new_str;
}

// 3. To Lower
char* strToLower(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* new_str = allocate_string(len);
    
    for (size_t i = 0; i < len; ++i) {
        new_str[i] = (char)tolower((unsigned char)str[i]);
    }
    new_str[len] = '\0';
    return new_str;
}

// 4. Reverse
char* strReverse(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* new_str = allocate_string(len);
    
    for (size_t i = 0; i < len; ++i) {
        new_str[i] = str[len - 1 - i];
    }
    new_str[len] = '\0';
    return new_str;
}

// 5. Trim (Removes leading and trailing whitespace)
char* strTrim(const char* str) {
    if (!str) return NULL;
    
    // Find the first non-whitespace character
    const char* start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    // If the string is all spaces, return an empty string
    if (*start == '\0') {
        char* empty_str = allocate_string(0);
        empty_str[0] = '\0';
        return empty_str;
    }
    
    // Find the last non-whitespace character
    const char* end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    // Calculate the new length and allocate
    size_t new_len = end - start + 1;
    char* new_str = allocate_string(new_len);
    
    // Copy the trimmed portion and add the null terminator
    strncpy(new_str, start, new_len);
    new_str[new_len] = '\0';
    
    return new_str;
}

// 6. Replace (Replaces all occurrences of 'target' with 'replacement')
char* strReplace(const char* str, const char* target, const char* replacement) {
    if (!str || !target || !replacement) return NULL;
    
    size_t target_len = strlen(target);
    if (target_len == 0) {
        // If target is empty, just duplicate the original string
        size_t len = strlen(str);
        char* dup = allocate_string(len);
        strcpy(dup, str);
        return dup;
    }
    
    size_t repl_len = strlen(replacement);
    
    // Pass 1: Count occurrences of 'target' to determine the size of the new string
    size_t count = 0;
    const char* tmp = str;
    while ((tmp = strstr(tmp, target)) != NULL) {
        count++;
        tmp += target_len;
    }
    
    // Pass 2: Allocate and build the new string
    size_t str_len = strlen(str);
    size_t new_len = str_len + count * (repl_len - target_len);
    char* new_str = allocate_string(new_len);
    
    char* dest = new_str;
    tmp = str;
    const char* next_match;
    
    while ((next_match = strstr(tmp, target)) != NULL) {
        // Copy characters before the match
        size_t prefix_len = next_match - tmp;
        memcpy(dest, tmp, prefix_len);
        dest += prefix_len;
        
        // Copy the replacement string
        memcpy(dest, replacement, repl_len);
        dest += repl_len;
        
        // Move tmp past the match in the original string
        tmp = next_match + target_len;
    }
    
    // Copy any remaining characters from the original string
    strcpy(dest, tmp);
    
    return new_str;
}