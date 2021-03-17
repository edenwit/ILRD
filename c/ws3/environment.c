#include <ctype.h> /*tolower */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strlen */


char **PrintEnv(char **env);

size_t CountEnvs(char **env);

char **AllocateStrings(char ** buffer, char **env, size_t env_count);

char *InsertEnvVarsToArr(char **buff, char **env);

char **FreeMem(char **buff, size_t n);

int main(int argc, char **argv, char **envp)


{
	
	char **env = envp;
	size_t env_count = CountEnvs(env) + 1;
	char **buffer = (char **)malloc(env_count * sizeof(char **));
		
	PrintEnv(env);
	
	assert(NULL != buffer);
		printf("\n\n\n----------------------------------\n\n\n");
	buffer = AllocateStrings(buffer, env, env_count);

	PrintEnv(buffer);
	buffer = FreeMem(buffer, env_count);
	
	return 0;
}

char **PrintEnv(char **env)
{
	char **orig_env = env;
	size_t i = 0;
	while (0 != *env)
	{
		printf("env %lu: %s\n",++i, *env);
		++env;
	}
	
	return orig_env;
}

size_t CountEnvs(char **env)
{
	size_t counter = 0;
	
	while (0 != *env)
	{
		++counter;
		++env;
	}
	
	return counter;
}


char **AllocateStrings(char ** buffer, char **env, size_t env_count)
{	
	char **orig_buffer = buffer;
	/*char **orig_env = env;*/
	size_t i = 0;
	size_t j = 0;
	size_t string_len = 0;
	
	for (i = 0; i < env_count - 1; ++i)
	{	
		string_len = strlen(*env) + 1;
		*buffer = (char *)malloc((string_len)* sizeof(char *));
		if (NULL == *buffer)
		{
			FreeMem(buffer, i);
		}		
		
		for (j = 0; j < string_len; ++j)
		{
			**(buffer) = tolower(**(env));
			/*printf("%c",**(buffer));*/
			++*buffer;
			++*env;
		}
		**buffer = '\0';
		*buffer = *buffer - string_len;
/*		printf("\nprinting %s", *buffer);*/
		++buffer;
		++env;
	}
	*buffer = NULL;
	
	return orig_buffer;
}

char **FreeMem(char **buff, size_t n)
{
	char **orig_buff = buff;
	size_t i = 0;
	
	for (i = 0; i< n; ++i)
	{
		printf("\n\n%lu\n\n",i);
		free(*buff);
		++buff;
	}
	free(orig_buff);
	
	return orig_buff;
}
