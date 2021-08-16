#include <stdio.h> /* printf */
 #include <string.h> /* memcpy */
#include <assert.h> /* assert */

#define WORD_SIZE (sizeof(size_t))


void *MemCpy(void *dest, const void *src, size_t n);
static void TestMemcpy();

int main()
{
	TestMemcpy();
	
	return 0;
}


void *MemCpy(void *dest, const void *src, size_t n)
{
	unsigned char  *temp_src = NULL;
	unsigned char *temp_dest = NULL;
	
	assert(dest);
	assert(src);
	
	temp_src = (unsigned char *)src;
	temp_dest = (unsigned char *)dest;
	
	while ((0 != ((size_t)temp_dest % WORD_SIZE)) && (0 < n))
	{
		*temp_dest = *temp_src;
		++temp_dest;
		++temp_src;
		n -= 1;
	}

	while (n > WORD_SIZE)
	{
		*(size_t *)temp_dest = *(size_t *)temp_src;
		temp_dest += WORD_SIZE;
		temp_src += WORD_SIZE;
		n -= WORD_SIZE;
	}

	while (0 < n)
	{
		*temp_dest = *temp_src;
		++temp_dest;
		++temp_src;
		n -= 1;
	}
	
	return dest;
}

static void TestMemcpy()
{
    char str_test[] = "abcdefghi test this code";
    char str_comp1[25] = {0};
    char str_comp2[25] = {0};

    int nums_test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums_comp1[9] = {0};
    int nums_comp2[9] = {0};
        
    if (0 != memcmp(MemCpy(str_comp1 + 1, str_test + 1, 25), memcpy(str_comp2 + 1, str_test + 1, 25), 25))
    {
        printf("Memcpy Failed: with input abcdefghi test this code\n");
    }
    if (0 != memcmp(MemCpy(nums_comp1, nums_test, 9), memcpy(nums_comp2, nums_test, 9), 9))
    {
        printf("Memcpy Failed: with input [1, 2, 3, 4, 5, 6, 7, 8, 9]\n");
    }
    
    return;
}

