#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "ex1.h"

static void TestMemset();
static void TestMemcpy();
static void TestMemmove();

int main()
{
	TestMemset();
	TestMemcpy();
	TestMemmove();
	
	return 0;
}

/* Approved by Maor */

static void TestMemset()
{
    char str_test[] = "abcdefghi test this code";
    char str_comp[] = "abcdefghi test this code";
    int nums_test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums_comp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int c = 'c';

    if (0 != memcmp(Memset(str_test + 7, c, 5), memset(str_comp + 7, c, 5), 17))
    {
        printf("Memset Failed: with input abcdefghi test this code\n");
    }
    if (0 != memcmp(Memset(nums_test, c, 5), memset(nums_comp, c, 5), 9))
    {
        printf("Memset Failed: with input [1, 2, 3, 4, 5, 6, 7, 8, 9]\n");
    }
    
    return;
}

/* Approved by Maor */

static void TestMemcpy()
{
    char str_test[] = "abcdefghi test this code";
    char str_comp1[25] = {0};
    char str_comp2[25] = {0};

    int nums_test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums_comp1[9] = {0};
    int nums_comp2[9] = {0};
        
    if (0 != memcmp(Memcpy(str_comp1 + 1, str_test + 1, 25), memcpy(str_comp2 + 1, str_test + 1, 25), 25))
    {
        printf("Memcpy Failed: with input abcdefghi test this code\n");
    }
    if (0 != memcmp(Memcpy(nums_comp1, nums_test, 9), memcpy(nums_comp2, nums_test, 9), 9))
    {
        printf("Memcpy Failed: with input [1, 2, 3, 4, 5, 6, 7, 8, 9]\n");
    }
    
    return;
}

static void TestMemmove()
{
    char str_test[] = "abcdefghi test this code";
    char str_comp1[25] = {0};
    char str_comp2[25] = {0};

    int nums_test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums_comp1[9] = {0};
    int nums_comp2[9] = {0};
        
    if (0 != memcmp(Memmove(str_comp1, str_test, 25), memmove(str_comp2, str_test, 25), 25))
    {
        printf("Memmove Failed: with input abcdefghi test this code\n");
    }
    if (0 != memcmp(Memmove(nums_comp1, nums_test, 9), memmove(nums_comp2, nums_test, 9), 9))
    {
        printf("Memmove Failed: with input [1, 2, 3, 4, 5, 6, 7, 8, 9]\n");
    }
    
    return;
}
