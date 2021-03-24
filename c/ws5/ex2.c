#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include "ex2.h"

#define UNUSED(X) ((void) X)
#define STR_MAX 256
#define STRUCT_SIZE 5
#define TEMP ".tmp"

typedef enum {FAIL = -1, SUCCESS = 0, EXIT = 1} status_type;

struct str_ops
{
	char *str_trigger;
	status_type (*cmp_func)(const char *input, const char *trigger);
	status_type (*action_func)(const char *input, const char *trigger);
};

static status_type ChainOfResponsibility(const char *str, const char *file_name, const struct str_ops *struct_arr);

static status_type CompareWholeStr(const char *str, const char *trigger);
static status_type IsPrepend(const char *str, const char *trigger);

static status_type GetSuccess(const char *str, const char *file_name);
static status_type RemoveFile(const char *str, const char *file_name);
static status_type ExitProg(const char *str, const char *file_name);
static status_type AddAtBeginning(const char *str, const char *file_name);
static status_type CountRows(const char *str, const char *file_name);
static status_type AppendStr(const char *str, const char *file_name);


void Log(const char *file_name)
{
	char str[STR_MAX] = {'\0'};
	status_type finished = SUCCESS;
	static const struct str_ops struct_arr[STRUCT_SIZE] = 
	{
		{"-remove", CompareWholeStr, RemoveFile},
		{"-count", CompareWholeStr, CountRows},
		{"-exit", CompareWholeStr, ExitProg},
		{"<", IsPrepend, AddAtBeginning},
		{"", GetSuccess, AppendStr}
	};

	assert(file_name);

	printf("Enter string (up to %d characters):\n", STR_MAX);
	
	while (EXIT != finished)
	{
		fgets(str, STR_MAX, stdin); 
		finished = ChainOfResponsibility(str, file_name, struct_arr);		
	}
}

static status_type ChainOfResponsibility(const char *str, const char *file_name, const struct str_ops *struct_arr)
{
	size_t i = 0;
	status_type operate = SUCCESS;
	
	while (i < STRUCT_SIZE)
	{	
		operate = struct_arr[i].cmp_func(str, struct_arr[i].str_trigger);

		if (SUCCESS == operate)
		{
			return struct_arr[i].action_func(str, file_name);
		}
		++i;
	}
	return FAIL;
}

static status_type CompareWholeStr(const char *str, const char *trigger)
{
	assert(str);
	assert(trigger);	
	
	return (0 == strncmp(trigger, str, strlen(str)-1)) ? SUCCESS : FAIL;
}

static status_type GetSuccess(const char *str, const char *file_name)
{
	UNUSED(str);
	UNUSED(file_name);
	
	return SUCCESS;
}

static status_type IsPrepend(const char *str, const char *trigger)
{
	assert(str);
	assert(trigger);
	
	return (*str == *trigger) ? SUCCESS : FAIL;
}


static status_type RemoveFile(const char *str, const char *file_name)
{
	UNUSED(str);
	
	if(NULL == file_name)
	{
		printf("File %s does not exist!\n",file_name);
		return FAIL;
	}
	else if (0 == remove(file_name))
	{
		printf("File %s removed successfully.\n",file_name);
		return SUCCESS;
	}	
	else
	{
		printf("File %s could not be removed.\n",file_name);
		return FAIL;
	}

}

static status_type ExitProg(const char *str, const char *file_name)
{
	UNUSED(str);
	UNUSED(file_name);
	
	puts("Exiting Program.\n");

	return EXIT;
}

static status_type AddAtBeginning(const char *str, const char *file_name)
{
    FILE *fp = NULL; 
    char buffer[STR_MAX] = {'\0'};
    
    assert(str);
	assert(file_name);
	
	fp = fopen(file_name, "a");
	if (NULL == fp)
	{
		printf("Can't open file '%s'.\n", file_name);
		return FAIL;
	}

	++str;
	
	if (FAIL == AppendStr(str, TEMP))
	{
		printf("Can't write to temp file.\n");
		return FAIL;
	}
    
    while (NULL != fgets(buffer, STR_MAX, fp))
    {
    	if (EXIT == AppendStr(buffer, TEMP))
    	{
    		printf("Can't write old file content to temp file.\n");
    		return EXIT;
    	}
    }
        
    if (0 != rename(TEMP, file_name))
    {
    	printf("Renaming file from %s to %s failed.\n", TEMP, file_name);
    	return FAIL;
    }
    
    if (0 != fclose(fp))
    {
       	printf("Closing file from %s failed.\n", file_name);
    	return FAIL;
    }

    return SUCCESS;
}

static status_type CountRows(const char *str, const char *file_name)
{
    FILE *fp = NULL; 
    size_t count = 0;
    char ch = '\0';
	
	UNUSED(str);  
	
	fp = fopen(file_name, "r"); 

	if (NULL == fp) 
	{ 
		printf("Could not open file %s.\n", file_name); 
		return FAIL;
	} 
	
	ch = fgetc(fp);
	
	while (EOF != ch)
	{
		if ('\n' == ch)
		{
			++count;
		}
		ch = fgetc(fp);
	}
	
    if (0 != fclose(fp))
    {
       	printf("Closing file from %s failed.\n", file_name);
    	return FAIL;
    }
    
	printf("The file %s has %lu lines.\n ", file_name, count); 
  
	return SUCCESS; 
} 

static status_type AppendStr(const char *str, const char *file_name)
{
	FILE *fp = NULL;
	
	assert(file_name);
	assert(str);
	
	fp = fopen(file_name, "a");

	if (NULL == fp)
	{
		printf("Can't write to file.\n");
		return EXIT;
	}
    
    if (EOF == fputs(str, fp))
	{
		printf("Can't write to file.\n");
		return FAIL;
	}
	
    if (0 != fclose(fp))
    {
       	printf("Closing file from %s failed.\n", file_name);
    	return FAIL;
    }
	
	return SUCCESS;
}
