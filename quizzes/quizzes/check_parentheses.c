#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include <assert.h> /* assert */

#include "../ds/src/stack/stack.h"

void CheckBalancedParentheses(char *s);
void TestCheckBalancedParentheses();

int main()
{
	TestCheckBalancedParentheses();
	
	return 0;
}

void CheckBalancedParentheses(char *s)
{
	
	stack_t *stack = NULL;
	char stack_peek = '\0';
	
	assert(s);

	stack = StackCreate(strlen(s));
	
	while('\0' != *s)
	{
		if ((')' == *s) || (']' == *s) || ('}' == *s))	
		{
			if (StackIsEmpty(stack))
			{
				printf("Not Balanced!\n");					
				StackDestroy(stack);

				return;	
			}
			stack_peek = *(char *)StackPeek(stack);
			
			if (((')' == *s) && ('(' == stack_peek)) || 
				((']' == *s) && ('[' == stack_peek)) ||
				(('}' == *s) && ('{' == stack_peek)))
			{
				StackPop(stack);
			}				
			else
			{
				printf("Not Balanced!\n");					
				StackDestroy(stack);

				return;
			}
		}

		if (('(' == *s) || ('[' == *s) || ('{' == *s))
		{
			StackPush(stack, (void *)s);
		}
		
		++s;
	}
	
	if (StackIsEmpty(stack))
	{
		printf("Balanced!\n");
		StackDestroy(stack);
		return;					
	}
	
	StackDestroy(stack);

	printf("Not Balanced!\n");					

	return;
}

void TestCheckBalancedParentheses()
{
	char *str = "[()](){[()]()}";
	
	printf("String '%s' balance check: ", str);
	CheckBalancedParentheses(str);
	
	str = "[()](){[()](hi there check)}";
	printf("String '%s' balance check: \t\t", str);
	CheckBalancedParentheses(str);

	str = "";
	printf("String '%s' balance check: \t\t ", str);
	CheckBalancedParentheses(str);
	
	str = "'d'";
	printf("String '%s' balance check: \t\t ", str);
	CheckBalancedParentheses(str);
	
	str = "{d{d}}";
	printf("String '%s' balance check: \t\t ", str);
	CheckBalancedParentheses(str);

	str = "{d{d})}}";
	printf("String '%s' balance check: \t\t ", str);
	CheckBalancedParentheses(str);
		
	str = "))))))))))))";
	printf("String '%s' balance check: \t\t ", str);
	CheckBalancedParentheses(str);

	return;	
}
