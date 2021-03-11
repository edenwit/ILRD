#define _ILRD_STRINGS_H

#include <stdio.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h>

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrNCpy(char *dest, const char *src, size_t n);

int StrCaseCmp(const char *s1, const char *s2);

char *StrChr(const char *s, int c);

char *StrDup(const char *s);

char *StrCat(char *dest, const char *src);

char *StrNCat(char *dest, const char *src, size_t n);