/*#include "stack.h"*/
#include "recursion.h"
#include <string.h>
#include <stdio.h>

static void RecursiveFibonacciTest();
static void IterativeFibonacciTest();

static void FlipListTest();

static void StrlenTest();
static void StrcmpTest();
static void StrcpyTest();
static void StrcatTest();
static void StrStrTest();

static void StackSortTest();

struct node
{
	void *data;
	struct node *next;
};

int main()
{

	IterativeFibonacciTest();
	RecursiveFibonacciTest();

	FlipListTest();

	StrlenTest();
	StrcmpTest();
	StrcpyTest();
	StrcatTest();
	StrStrTest();

	StackSortTest();

	return (0);
}

static void FlipListTest()
{
	int arr[] = {1, 2, 3, 4, 5};

	node_t *tester = NULL;

	node_t elem_1 = {NULL, NULL};
	node_t elem_2 = {NULL, NULL};
	node_t elem_3 = {NULL, NULL};
	node_t elem_4 = {NULL, NULL};
	node_t elem_5 = {NULL, NULL};

	elem_1.data = &arr[0];
	elem_2.data = &arr[1];
	elem_3.data = &arr[2];
	elem_4.data = &arr[3];
	elem_5.data = &arr[4];

	elem_5.next = NULL;
	elem_4.next = &elem_5;
	elem_3.next = &elem_4;
	elem_2.next = &elem_3;
	elem_1.next = &elem_2;

	tester = &elem_1;

	tester = FlipList(tester);

	if (tester != &elem_5)
	{
		printf("Flip Test Failed! head is: %d, expected: %d.\n", *(int *)(tester->data), *(int *)elem_5.data);
	}

	tester = FlipList(tester);

	if (tester != &elem_1)
	{
		printf("Flip Test Failed! head is: %d, expected: %d.\n", *(int *)(tester->data), *(int *)elem_1.data);
	}

	tester = FlipList(&elem_5);

	if (tester != &elem_5)
	{
		printf("Flip Test Failed! head is: %d, expected: %d.\n", *(int *)(tester->data), *(int *)elem_5.data);
	}

	return;
}

static void StrlenTest()
{
	const char *test_strs[] = {"123abgjfl;jdlhlc", "abcde", "", "0", "abcdef"};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (StrLen(test_strs[i]) != strlen(test_strs[i]))
		{
			printf("Strlen Test #%ld failed. tested: '%s', actual: %ld, expacted: %ld.\n", i + 1, test_strs[i], StrLen(test_strs[i]), strlen(test_strs[i]));
		}
	}

	return;
}

static void StrcmpTest()
{
	const char *test_strs1[] = {"abcdaaaaaaaa", "abcde", "", "0", "abcdef", "abcDe"};
	const char *test_strs2[] = {"gdabcdaaaaazaa", "Abcde", "", "0", "abcAdef", "abcD"};
	size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (StrCmp(test_strs1[i], test_strs2[i]) != strcmp(test_strs1[i], test_strs2[i]))
		{
			printf("Strcmp Test #%ld failed. tested: '%s' = '%s', actual: %d, expacted: %d.\n", i + 1, test_strs1[i], test_strs2[i], StrCmp(test_strs1[i], test_strs2[i]), strcmp(test_strs1[i], test_strs2[i]));
		}
	}

	return;
}

static void StrcpyTest()
{
	const char *test_strs[] = {"abcdaaaaaaaa", "abcde", "", "0", "abcdef"};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	char arr_to_cpy[50] = {0};
	char *cpy_str_p = NULL;

	for (i = 0; i < arr_size; ++i)
	{
		cpy_str_p = StrCpy(arr_to_cpy, test_strs[i]);
		if (cpy_str_p != arr_to_cpy || 0 != StrCmp(arr_to_cpy, test_strs[i]))
		{
			printf("Strcpy Test #%ld failed.\n", i + 1);
		}
	}
	return;
}

static void StrcatTest()
{
	char test_strs1[][20] = {"abc", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "", ""};
	const char *test_strs2[] = {"defg", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "", ""};
	const size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;
	char *cpy_str_p = NULL;

	for (i = 0; i < arr_size; ++i)
	{
		cpy_str_p = StrCat(test_strs1[i], test_strs2[i]);

		if (0 != StrCmp(cpy_str_p, strcat(test_strs1[i], test_strs2[i])))
		{
			printf("Strncpy Test #%ld failed.\n", i + 1);
		}
	}

	return;
}

static void StrStrTest()
{
	const char arr_str[][20] = {"shellyshl", "Hipompopostr", "Hipopotamus ", "Hipopopodria", "History "};
	char *actual = NULL;
	char *expected = NULL;

	size_t i = 0;

	/*printf("\nTest for the function :\n\n");*/

	actual = (char *)StrStr(arr_str[i], "shl");
	expected = (char *)strstr(arr_str[i], "shl");

	if (actual != expected)
	{
		printf("something is wrong with strstrr!, expected :%s , you got %s\n", expected, actual);
	}
	for (i = 1; i < 4; i++)
	{
		actual = (char *)StrStr(arr_str[i], "popo");
		expected = (char *)strstr(arr_str[i], "popo");

		if (actual != expected)
		{
			printf("something is wrong with strstrr!, expected :%s , you got %s\n", expected, actual);
			continue;
		}

		/* if (0 != strcmp(actual,expected))
        {
            printf("\nTEST StrStr FAILED\n");
            printf("%s",actual);
            printf("%s",expected);
        }
*/
	}
	return;
}
static void IterativeFibonacciTest()
{
	int test_arr[] = {1, 2, 3, 4, 5, 6, 10, 20, 30, 40};
	int exp_arr[] = {1, 1, 2, 3, 5, 8, 55, 6765, 832040, 102334155};
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t i = 0;
	int recur_res = 0;

	for (i = 0; i < arr_size; ++i)
	{
		recur_res = IterativeFibonacci(test_arr[i]);

		if (recur_res != exp_arr[i])
		{
			printf("GetNFibonacciElement Test #%ld failed. n: %d, actual: %d.\n", i + 1, test_arr[i], recur_res);
		}
	}

	return;
}

static void RecursiveFibonacciTest()
{
	int test_arr[] = {1, 2, 3, 4, 5, 6, 10, 20, 30, 40};
	int exp_arr[] = {1, 1, 2, 3, 5, 8, 55, 6765, 832040, 102334155};
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t i = 0;
	int recur_res = 0;

	for (i = 0; i < arr_size; ++i)
	{
		recur_res = (long)RecursiveFibonacci(test_arr[i]);

		if (recur_res != exp_arr[i])
		{
			printf("GetNFibonacciElement Test #%ld failed. n: %d, actual: %d.\n", i + 1, test_arr[i], recur_res);
		}
	}

	return;
}

static void StackSortTest()
{
	/*int test_arr[] = {14, 31, 2, 5, 18, 19, 21, 30, 50, 13};*/
	int test_arr[] = {18, 14, 31, 2};
	int exp_arr[] = {31, 18, 14, 2};

	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	stack_t *stack = StackCreate(arr_size);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		StackPush(stack, (void *)(test_arr + i));
	}

	StackSort(stack);

	for (i = 0; i < arr_size; ++i)
	{
		if (*(int *)StackPeek(stack) != exp_arr[i])
		{
			printf("wrong things! expected: %d, actual: %d\n", *(exp_arr + i), *(int *)StackPeek(stack));
		}

		StackPop(stack);
	}

	StackDestroy(stack);
}