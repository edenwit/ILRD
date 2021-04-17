#ifndef __C_EXAM_H__
#define __C_EXAM_H__

int FlipDigitsInNum(int num);
unsigned char ByteMirror(unsigned char byte);
int FlipBit(int val, unsigned int n);
size_t CountBitsInByte(unsigned char byte);
char RotateLeft(char byte, unsigned int nbits);
void SwapPointers(int **p1, int **p2);

size_t Strlen(const char *s);
int Strcmp(const char *s1, const char *s2);
char *Strcpy(char *dest, const char *src);
char *Strncpy(char *dest, const char *src, size_t n);
char *Strcat(char *dest, const char *src);

unsigned long GetNFibonacciElement(unsigned int n);

char *IntToString (int value, char *str);

long MultiPlyBy8(int num);

void Swap1(int *x, int *y);
void Swap2(int *x, int *y);
void Swap3(int *x, int *y);

#endif /*  __C_EXAM_H__ */
