#include <stdio.h> /* printf */
#include <stdlib.h> /* realloc */
#include <string.h> /* strlen */
#include <assert.h> /* assert */

#include "ex1.h"


#define ARR_SIZE 9

typedef struct element element_t;

struct element
{
	void *data;
	int (*add)(element_t *val, int to_add);
	void (*print)(const element_t *val);
	void (*clean)(element_t *val);
};


static int InitAll(element_t *element_arr);
static void InitInt(int *data, element_t *arr_start, element_t *arr_end);
static int InitFloat(float *data, element_t *arr_start, element_t *arr_end);
static int InitString(char *data[], element_t *arr_start, element_t *arr_end);
static void AddToAll(element_t *element_arr, size_t size, int to_add);
static void PrintAll(element_t *element_arr, size_t size);
static void CleanAll(element_t *element_arr, size_t size);
static int AddToInt(element_t *val, int to_add);
static int AddToFloat(element_t *val, int to_add);
static int AddToString(element_t *val, int to_add);
static void PrintInt(const element_t *val);
static void PrintFloat(const element_t *val);
static void PrintString(const element_t *val);
static void CleanNothing(element_t *val);
static void CleanHeap(element_t *val);

static size_t CountsDigits(int num);



/* start */
void Manage()
{
	int num = 10;
	element_t element_arr[ARR_SIZE] = {0};
	InitAll(element_arr);
	PrintAll(element_arr, ARR_SIZE);
	AddToAll(element_arr, ARR_SIZE, num);
	PrintAll(element_arr, ARR_SIZE);
	CleanAll(element_arr, ARR_SIZE);
	
	return;
}

/* init array */
static int InitAll(element_t *element_arr)
{
	static int int_elem[] = {5, 10, -40};
	static float float_elem[] = {2.5, 8.56, -4.1};
	char *str_elem[] = {"shir", "Test", "Hello"};
	
	assert(element_arr);
	
	InitInt(int_elem, element_arr, element_arr+ 2);
	InitFloat(float_elem, element_arr + 3, element_arr + 5);
	InitString(str_elem, element_arr + 6, element_arr + 8);
	return 0;
}

static void InitInt(int *data, element_t *arr_start, element_t *arr_end)
{
	size_t i = 0;
	
	assert(data);
	assert(arr_start);
	assert(arr_end);
	
	while (arr_start <= arr_end)
	{
		arr_start->data = &data[i];
		arr_start->add = AddToInt;
		arr_start->print = PrintInt;
		arr_start->clean = CleanNothing;	
	
		++i;
		++arr_start;
	}
	
	return;
}

static int InitFloat(float *data, element_t *arr_start, element_t *arr_end)
{
	size_t i = 0;
	
	assert(data);
	assert(arr_start);
	assert(arr_end);
	
	while (arr_start <= arr_end)
	{
		arr_start->data = &data[i];
		arr_start->add = AddToFloat;
		arr_start->print = PrintFloat;
		arr_start->clean = CleanNothing;	
		
		++i;
		++arr_start;
	}
	return 0;
}

static int InitString(char *data[], element_t *arr_start, element_t *arr_end)
{
	size_t len_str = 0;
	size_t i = 0;
	size_t clean_mem = 0;
	
	assert(arr_start);
	assert(arr_end);
	assert(data);

	while (arr_start <= arr_end)
	{
		len_str = strlen(data[i]);
		
		arr_start->data = calloc(len_str + 1, sizeof(char));
		
		if(NULL == arr_start->data)
		{
			printf("Problem with memory access!");
			
			for (clean_mem = 0; clean_mem < i; ++clean_mem)
			{
        		arr_start[clean_mem].clean(&arr_start[clean_mem]);
			}
		
			return 1;
		}
		strcpy((char*)arr_start->data, data[i]);
		
		arr_start->add = AddToString;
		arr_start->print = PrintString;
		arr_start->clean = CleanHeap;	
		
		++i;
		++arr_start;
	}
	return 0;
}


/* Add, print and clean to all with a loop */

static void AddToAll(element_t *element_arr, size_t size, int to_add)
{
	size_t i = 0;
	
	assert(element_arr);
	
	for (i = 0; i < size; ++i)
	{
        element_arr[i].add(element_arr + i, to_add);
	}
	return;
}

static void PrintAll(element_t *element_arr, size_t size)
{
	size_t i = 0;
	
	assert(element_arr);
	
	printf("---> start PrintAll\n");
	for (i = 0; i < size; ++i)
	{
        element_arr[i].print(&element_arr[i]);
	}
	printf("---> end PrintAll\n");
	return;
}



static void CleanAll(element_t *element_arr, size_t size)
{
	size_t i = 0;
	
	assert(element_arr);
	
	for (i = 0; i < size; ++i)
	{
        element_arr[i].clean(&element_arr[i]);
	}
	return;
}



/* add funcs */

static int AddToInt(element_t *val, int to_add)
{
	assert(val);
	
	*(int*)(val->data) += to_add;/* add 'to_add' to data */
	
	return 0;
}

static int AddToFloat(element_t *val, int to_add)
{
	assert(val);
	
	*(float*)(val->data) += (float)to_add;
	
	return 0;
}


static int AddToString(element_t *val, int to_add)
{
	size_t num_of_digs = 0;
	size_t len_str = 0;
	size_t i = 0;
	char *new_val = NULL;
	
	assert(val);
	
	len_str = strlen((char*)val->data);
	num_of_digs = CountsDigits(to_add);
	
	new_val = (char*)realloc(val->data, sizeof(char) * (len_str + num_of_digs + 1));
	
	
	if(NULL == new_val)
	{
		printf("Realloc failed!");
		for (i = 0; i < ARR_SIZE; ++i)
		{
        	val[i].clean(&val[i]);
		}
		
		return 1;
	}
	
	val->data = new_val; /* in case that realloc copy the data to another place */
	
	sprintf((char*)(val->data) + len_str, "%d", to_add);
	
	return 0;
}

static size_t CountsDigits(int num)
{
	size_t count_digs = 0;
	
	
	while (0 != num)
	{
		num = num/10;
		++count_digs;
	}
	
	return count_digs;
}



/* print */

static void PrintInt(const element_t *val)
{
	assert(val);
	
	printf("PrintInt: %d\n", *((int*)val->data));
	return;
}

static void PrintFloat(const element_t *val)
{
	assert(val);
	
	printf("PrintFloat: %f\n", *((float*)val->data));
	return;
}

static void PrintString(const element_t *val)
{
	assert(val);
	
	printf("PrintString: %s\n", (char*)val->data);
	return;
}


/* clean */

static void CleanNothing(element_t *val)
{
	(void)val;
	return;
}

static void CleanHeap(element_t *val)
{
	assert(val);
	
	free(val->data);
	val->data = NULL;
	return;
}





