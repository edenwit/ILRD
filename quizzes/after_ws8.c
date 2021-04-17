#include <stdio.h>

#define MAX2(a, b) ((a) > (b)) ? (a) : (b)
#define MAX3(a, b, c) ((((a) > (b))) ? MAX2((a), (c)) : MAX2((b), (c)))
#define TO_LOWER(a) (('A' <= (a)) && ('Z' >= (a)) ? (a) + ('a' - 'A') : (a))
#define OFFSET(s, f) ((size_t)&(((s*)0)->f))

typedef struct stack
{
    size_t top;
    void **elements;
    size_t capacity;
} stackk;

int main()
{
	printf("Max 3: 1, 15, 63: %d\n", MAX3(1, 15, 63));
	printf("TO_LOWER: 'A' : '%c', '5': '%c', 'b': '%c'.\n", TO_LOWER('A'),TO_LOWER('5'),TO_LOWER('b'));
	printf("OFFSET: %ld.\n", OFFSET(stackk, capacity));	
	
	return 0;
}
