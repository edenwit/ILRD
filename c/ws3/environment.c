#include <ctype.h> /*tolower */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strlen */


size_t CountChars(char **env);
char *AllocateBuffer(size_t size);
char *InsertEnvVarsToArr(char *buff, char **env);

int main(int argc, char **argv, char **envp)
{
	char **env = envp;
	size_t size_to_allocate = CountChars(env);
	char *buffer = AllocateBuffer(size_to_allocate);

	assert(NULL != buffer);
	
	
	printf("Buffer size       : %lu\n", size_to_allocate);
	printf("Buffer adress from: %p\n", buffer);
	printf("Buffer adress to  : %p\n", buffer + size_to_allocate - 1);
	buffer = InsertEnvVarsToArr(buffer, env);
	
	printf("Buffer: \n%s\n", buffer);

	
	return 0;
}

size_t CountChars(char **env)
{
	size_t size_count = 0;
	
	for (; *env != 0; env++)
	{
		size_count = size_count + strlen(*env) + 1;
	}
	
	return size_count;
}

char *AllocateBuffer(size_t size)
{	
    char *buffer = (char *)malloc(size * sizeof(char));
	
	return buffer;
}

char *InsertEnvVarsToArr(char *buff, char **env)
{
	char *buff_loc = buff;
	size_t i = 0;
	size_t env_len = 0;
	
	for (; *env != 0; env++)
	{
		env_len = strlen(*env);
		printf("env: %s, len: %lu.\n", *env, env_len);
		for (i = 0; i < env_len; ++i)
		{
			*buff_loc = tolower(**(env + i));
			++buff_loc;
		}
		*buff_loc = ' ';
		++buff_loc;
	}
	*(buff_loc -1) = '\0';
	
	return buff;
	
	
}
