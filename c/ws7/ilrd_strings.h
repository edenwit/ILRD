#ifndef __ILRD_STRINGS_H__
#define _ILRD_STRINGS_H

#include <stdio.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h>
#include <ctype.h>

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrnCpy(char *dest, const char *src, size_t n);

int StrCaseCmp(const char *s1, const char *s2);

char *StrChr(const char *s, int c);

char *StrDup(const char *s);

char *StrCat(char *dest, const char *src);

char *StrnCat(char *dest, const char *src, size_t n);

char *StrStr(const char *haystack, const char *needle);

size_t StrSpn(const char *s, const char *accept);

int IsPalindrome(const char *str);

#endif /* __ILRD_STRINGS_H__ */
