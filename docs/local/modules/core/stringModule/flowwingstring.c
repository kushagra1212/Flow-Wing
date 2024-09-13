
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Copy a string from src to dest
void strCopy(char *dest, char *src) {
  strcpy(dest, src);
  return;
}

// Compare two strings
int strCompare(const char *str1, const char *str2) {
  return strcmp(str1, str2);
}

// Find the length of a string
size_t strLength(const char *str) { return strlen(str); }

// Convert a string to uppercase
char *strToUpper(char *instr) {
  int c = 0;
  while (instr[c] != '\0') {
    if ((instr[c] >= 'a') && (instr[c] <= 'z')) {
      instr[c] = instr[c] - ('a' - 'A');
    }
    c++;
  }

  return instr;
}

// Convert a string to lowercase
char *strToLower(char *str) {
  for (char *p = str; *p; ++p) {
    *p = tolower((unsigned char)*p);
  }
  return str;
}

// Convert an int to a string
char *int8ToStr(int8_t num, char *str) {
  sprintf(str, "%c", num);
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

char *strCharAt(const char *str, size_t index) {
  static char result[2];

  if (index < strlen(str)) {
    result[0] = str[index];
    result[1] = '\0';
    return result;
  }

  return NULL;
}