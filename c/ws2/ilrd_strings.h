#define _ILRD_STRINGS_H

#include <stdio.h> /* size_t */
#include <stdio.h> /* size_t */
#include <assert.h> /* assert */

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrNCpy(char *dest, const char *src, size_t n);
