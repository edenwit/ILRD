#include <stdio.h> /* printf */
#include <ctype.h> /* isspace */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */

static void ReverseWholeWord(char *start, char *end);
void ReverseWords(char* s);
static void ReverseWordsTest();

int main()
{
	ReverseWordsTest();

	return 0;
}

void ReverseWords(char *s)
{
    char *word_start = NULL;
    char *str_temp = s;
 
 	assert(s);
 	
    while (*str_temp)
    {
        if ((NULL == word_start) && !isspace(*str_temp))
        {
            word_start = str_temp;
        }
        if ((word_start && isspace(*(str_temp + 1))) || (!isspace(*(str_temp)) && '\0' == (*(str_temp + 1))))
        {
            ReverseWholeWord(word_start, str_temp);
            word_start = NULL;
        }
        str_temp++;
    } 
    
    ReverseWholeWord(s, str_temp - 1);
    
    return;
}

static void ReverseWholeWord(char *start, char *end)
{
    char temp = 0;
    
   	assert(start);
 	assert(end);
    
    while (start < end)
    {
        temp = *end;
        *end = *start;
        *start = temp;
        ++start;
        --end;
    }
    
    return;
}

static void ReverseWordsTest()
{
	char test_strs[][80] = {"happy",
				"mentor is king.", 
				"", 
				" ", 
				"like", 
				"very happy to tell you i'm gonna see my girlfriend today"};

	char exp_strs[][80] = {"happy",
				"king. is mentor", 
				"", 
				" ", 
				"like", 
				"today girlfriend my see gonna i'm you tell to happy very"};
				
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		ReverseWords(test_strs[i]);
		
		if (strcmp(test_strs[i], exp_strs[i]))
		{
			printf("Failure at test #%ld: expected: '%s', actual: '%s'\n", i + 1, exp_strs[i], test_strs[i]);
		}
	}
	
}

