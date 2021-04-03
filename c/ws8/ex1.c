
#include <stdio.h> /* printf */
#include <limits.h>
#include "ex1.h"
#include <assert.h> /* assert */
#include <stdlib.h> /* free */
#include <string.h> /* strlen */
#include <math.h> /* log10 */ 

#define UNUSED(X) ((void) X)

#define ARR_SIZE 10
#define INT_TO_ADD INT_MAX

#define TODATA(val) (*(void **)&val)
#define TOINT(val) (*(int *)&val)
#define TOFLOAT(val) (*(float *)&val)

typedef struct elem element_t;

static int InitAll(element_t *element_arr);
static int InitInt(element_t *element, int val);
static int InitFloat(element_t *element, float val);
static int InitString(element_t *element, char *val, size_t ind);

static int AddToAll(element_t *element_arr, size_t size, int to_add);
static int AddToInt(element_t *data, int to_add);
static int AddToFloat(element_t *data, int to_add);
static int AddToString(element_t *data, int to_add);

static void PrintAll(element_t *element_arr, size_t size);
static void PrintInt(const element_t *data);
static void PrintFloat(const element_t *data);
static void PrintString(const element_t *data);

static void CleanAll(element_t *element_arr, size_t size);
static void CleanNothing(element_t *data);
static void CleanHeap(element_t *data);

struct elem
{
	void *data;
	int (*add)(element_t *data, int to_add);
	void (*print)(const element_t *data);
	void (*clean)(element_t *data);
};

void Manage()
{
	int success = 0;
	
	element_t arr_element[ARR_SIZE];
	success = InitAll(arr_element);
	
	if( 0 == success)
	{
		printf ("InitAll failed. Memory freed and program done.\n");
		return;
	}
	PrintAll(arr_element, ARR_SIZE);
	success = AddToAll(arr_element, ARR_SIZE, INT_TO_ADD);	
	if( 0 == success)
	{
		printf ("AddToAll failed. Memory freed and program done.\n");
		return;
	}
	PrintAll(arr_element, ARR_SIZE);
	CleanAll(arr_element, ARR_SIZE);

	return;
}

static int InitAll(element_t *element_arr)
{
	int success = 0;	
	
	if (NULL == element_arr)
	{
		return 0;
	}
	
	InitInt(element_arr + 0 ,5);
	success = InitString(element_arr + 1 ,"First String", 1);
	if (success == 0)
	{
		return 0;
	}
	InitInt(element_arr + 2 ,2500000);
	InitFloat(element_arr + 3 ,-254.456);	
	success = InitString(element_arr + 4 ,"Second String", 4);	
	if (success == 0)
	{
		return 0;
	}
	InitFloat(element_arr + 5 ,-2851323.012314);	
	success = InitString(element_arr + 6 ,"Third String", 6);	
	if (success == 0)
	{
		return 0;
	}
	InitFloat(element_arr + 7 ,1000000.1);	
	InitFloat(element_arr + 8 ,2851323.012314);	
	success = InitString(element_arr + 9 ,"Fourth and final String. Our story begins in a farfar away kingdom...", 9);	
	if (success == 0)
	{
		return 0;
	}
	
	return 1;
}

static int InitInt(element_t *element, int val)
{
	
	if (NULL == element)
	{
		return 0;
	}
	element->data = TODATA(val);
	element->add = AddToInt;
	element->print = PrintInt;
	element->clean = CleanNothing;
	
	return 1;
}

static int InitFloat(element_t *element, float val)
{

	if (NULL == element)
	{
		return 0;
	}
	element->data = TODATA(val);
	element->add = AddToFloat;
	element->print = PrintFloat;
	element->clean = CleanNothing;
	
	return 1;
}

static int InitString(element_t *element, char *val, size_t ind)
{
	if (NULL == element)
	{
		return 0;
	}
	
	element->data = malloc(strlen(val) + 1);
	
	if (NULL == element->data)
	{
		printf("Failed to init %s to element in index %lu. Cleaning all.\n", val, ind);
		CleanAll(element, ind);
		return 0;
	}	
	
	strcpy(element->data, val);
	element->add = AddToString;
	element->print = PrintString;
	element->clean = CleanHeap;
	
	return 1;
}

static int AddToAll(element_t *element_arr, size_t size, int to_add)
{
	int success = 0;
	size_t i = 0;
	
	assert(element_arr);
	
	for (i = 0; i < size; ++i)
	{
		success = element_arr[i].add((element_arr + i), to_add);	
		if (success == 0)
		{
			printf("Failed to add %d to element. Cleaning all.\n", to_add);
			CleanAll(element_arr, ARR_SIZE);
		}
	}
	
	return 1;
}

static int AddToInt(element_t *data, int to_add)
{
	long temp = 0;
	
	if (NULL == data)
	{
		return 0;
	}
	temp = TOINT(data->data) + to_add;
	data->data = TODATA(temp);

	return 1;
}
static int AddToFloat(element_t *data, int to_add)
{
	float temp = 0;
	
	if (NULL == data)
	{
		return 0;
	}
	temp = TOFLOAT(data->data) + to_add;
	data->data = TODATA(temp);

	return 1;
}
static int AddToString(element_t *data, int to_add)
{
	char digit_as_string[10] = {0};
	sprintf(digit_as_string, "%d", to_add);
	
	if (NULL == data)
	{
		return 0;
	}
	
	data->data = realloc(data->data, strlen(data->data) + strlen(digit_as_string) + 1);

	if (NULL == data->data)
	{
		return 0;
	}	

	strcat(data->data, digit_as_string);
	
	return 1;
}

static void PrintAll(element_t *element_arr, size_t size)
{
	size_t i = 0;
	
	assert(element_arr);

	for (i = 0; i < size; ++i)
	{
		element_arr[i].print((element_arr + i));

	}
	
	return;
}

static void PrintInt(const element_t *data)
{
	assert(data);
	printf("%d\n", TOINT(data->data));
	
	return;
}

static void PrintFloat(const element_t *data)
{
	assert(data);
	printf("%f\n", TOFLOAT(data->data));
	
	return;
}

static void PrintString(const element_t *data)
{
	assert(data);
	printf("%s\n", (char *)(data->data));
	
	return;
}

static void CleanAll(element_t *element_arr, size_t size)
{
	size_t i = 0;
	
	assert(element_arr);
	
	for (i = size; i > 0; --i)
	{
		element_arr[i - 1].clean(element_arr + i - 1);
	}
	
	return;
}

static void CleanNothing(element_t *data)
{
	UNUSED(data);
	return;
}

static void CleanHeap(element_t *data)
{
	assert(data);
	free(data->data);

	return;	
}
