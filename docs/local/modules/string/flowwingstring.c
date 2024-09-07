
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Copy a string from src to dest
char *strCopy(char *dest, char *src) { return strcpy(dest, src); }

// Concatenate two strings (append src to dest)
char *strConcat(char *dest, const char *src) { return strcat(dest, src); }

// Compare two strings
int strCompare(const char *str1, const char *str2) {
  return strcmp(str1, str2);
}

// Find the length of a string
size_t strLength(const char *str) { return strlen(str); }

// Convert a string to uppercase
char *strToUpper(char *instr) {
  // Allocate memory for instr2 (length of instr + 1 for the null terminator)
  // char *instr2 = (char *)malloc((strlen(instr) + 1) * sizeof(char));

  // if (instr2 == NULL) {
  //   // Handle memory allocation failure
  //   return NULL;
  // }

  // // Copy the contents of instr to instr2
  // strcpy(instr2, instr);

  // // Convert instr2 to uppercase
  // int c = 0;
  // while (instr2[c] != '\0') {
  //   if ((instr2[c] >= 'a') && (instr2[c] <= 'z')) {
  //     instr2[c] = instr2[c] - ('a' - 'A'); // Convert to uppercase
  //   }
  //   c++;
  // }

  return instr;
}

// Convert a string to lowercase
char *strToLower(char *str) {
  for (char *p = str; *p; ++p) {
    *p = tolower((unsigned char)*p);
  }
  return str;
}

// Reverse a string
char *strReverse(char *str) {
  char *start = str;
  char *end = str + strlen(str) - 1;
  while (start < end) {
    char temp = *start;
    *start++ = *end;
    *end-- = temp;
  }
  return str;
}

// Trim leading and trailing whitespace from a string
char *strTrim(char *str) {
  char *end;

  // Trim leading space
  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0) // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  // Null-terminate after the last non-space character
  *(end + 1) = 0;

  return str;
}

// Find the first occurrence of a substring
char *strFind(const char *haystack, const char *needle) {
  return strstr(haystack, needle);
}

// Replace all occurrences of a substring with another substring
char *strReplace(char *str, const char *oldSub, const char *newSub) {
  char *pos;
  size_t oldLen = strlen(oldSub);
  size_t newLen = strlen(newSub);

  while ((pos = strstr(str, oldSub)) != NULL) {
    char temp[1024];
    size_t len = pos - str;
    strncpy(temp, str, len);
    temp[len] = '\0';
    strcat(temp, newSub);
    strcat(temp, pos + oldLen);
    strcpy(str, temp);
  }
  return str;
}

// Split a string into tokens based on a delimiter
char *strSplit(char *str, const char *delim) {
  static char *nextToken = NULL;

  if (str != NULL) {
    nextToken = str;
  }

  if (nextToken == NULL) {
    return NULL;
  }

  char *token = nextToken;
  nextToken = strpbrk(token, delim);

  if (nextToken != NULL) {
    *nextToken = '\0';
    nextToken++;
  }

  return token;
}

// Find the index of the first occurrence of a character (ch is a string of
// length 1)
int strFindChar(const char *str, const char *ch) {
  if (strlen(ch) != 1) {
    return -1; // Error: ch should be a single character
  }
  const char *ptr = strchr(str, ch[0]);
  if (ptr != NULL) {
    return ptr - str; // Calculate the index
  }
  return -1; // Character not found
}

// Get the character at a specified index and return it as a single-character
// string
char *strCharAt(const char *str, size_t index) {
  static char
      result[2]; // Buffer to hold the single character and null terminator

  if (index < strlen(str)) {
    result[0] = str[index]; // Get the character at the index
    result[1] = '\0';       // Null-terminate the string
    return result;
  }

  return NULL; // Index out of bounds
}