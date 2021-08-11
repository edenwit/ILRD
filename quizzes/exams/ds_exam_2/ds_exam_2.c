/*  Developer: Eden Wittenberg;									*
 *  Date Of Creation: 28.07.21;									*

 *  Description: Data Structure Exam 2;							*/

#include <stdio.h>	/* printf */
#include <limits.h> /* INT_MIN */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "stack.h"
#include "bst.h"

#define CHARS (256)

void Swap(char *x, char *y);

typedef struct node
{
	void *data;
	struct node *next;

} node_t;

typedef struct bst_node
{
	void *data;
	struct bst_node *left;
	struct bst_node *right;
	struct bst_node *parent;

} bst_node_t;

struct bst
{
	bst_node_t dummy;
	int (*cmp_func)(void *data1, void *data2, void *param);
	void *param;
};

/* Question 1 */

/*section 1 */

node_t *FlipIterative(node_t *head)
{
	node_t *prev = NULL;
	node_t *next = NULL;

	assert(head);

	while (NULL != head)
	{
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}

	return (prev);
}

/*section 2 */
node_t *FlipRecursive(node_t *head)
{
	node_t *node = NULL;

	assert(head);

	if ((NULL != head) || (NULL == head->next))
	{
		return (head);
	}

	node = FlipRecursive(head->next);

	head->next->next = head;
	head->next = NULL;

	return (node);
}

/* Question 2 */
long LargestSumInArray(int *arr, size_t arr_size, size_t *start, size_t *end)
{
	long max_local = 0;
	long max_total = INT_MIN;
	size_t i = 0;
	size_t j = 0;

	assert(arr);

	for (i = 0; i < arr_size; ++i)
	{
		max_local = arr[i];

		if (max_local > max_total)
		{
			max_total = max_local;
			*start = j;
			*end = i;
		}

		else
		{
			max_local = 0;
			j = i + 1;
		}
	}

	return (max_total);
}

/* Question 3 */

int SortStack(stack_t *stack)
{
	stack_t *stackush = NULL;
	int val = 0;

	stackush = StackCreate(StackGetCapacity(stack));

	if (NULL == stackush)
	{
		return (1);
	}

	while (!StackIsEmpty(stack))
	{
		val = (int)(long)(StackPeek(stack));
		StackPop(stack);

		while ((!StackIsEmpty(stackush)) && ((int)(long)StackPeek(stackush) > val))
		{
			StackPush(stack, StackPeek(stackush));
			StackPop(stackush);
		}

		StackPush(stackush, (void *)(long)val);
	}

	while (!StackIsEmpty(stackush))
	{
		StackPush(stack, StackPeek(stackush));
		StackPop(stackush);
	}

	StackDestroy(stackush);

	return (0);
}

/* Question 4 */

int SortCharsInFile(const char *filename, char *result)
{
	size_t char_counts[CHARS] = {0};
	size_t i = 0;
	int ch = 0;
	FILE *file_ptr = NULL;
	FILE *res_file_ptr = NULL;

	assert(filename);
	assert(result);

	file_ptr = fopen(filename, "r");

	if (NULL == file_ptr)
	{
		return (1);
	}

	res_file_ptr = fopen(result, "a");

	if (NULL == res_file_ptr)
	{
		fclose(file_ptr);
		return (1);
	}

	for (ch = fgetc(file_ptr); EOF != ch; ch = fgetc(file_ptr))
	{
		++char_counts[ch];
	}

	for (i = 0; i < CHARS; ++i)
	{
		while (0 < char_counts[i])
		{
			fputc((char)i, res_file_ptr);
			--char_counts[i];
		}
	}

	fclose(file_ptr);
	fclose(res_file_ptr);

	return (0);
}

int main()
{
	SortCharsInFile("src_file.txt", "dest_file.txt");

	return (0);
}


/* Question 5 */

bst_node_t *IterativeBstInsert(bst_node_t *tree, int val)
{
	bst_node_t *root = NULL;
	bst_node_t *node = NULL;
	void *val_ptr = (void *)(long)val;

	assert(tree);

	root = (bst_node_t *)tree;
	node = (bst_node_t *)malloc(sizeof(bst_node_t));

	if (NULL == node)
	{
		return (NULL);
	}

	node->data = val_ptr;
	node->left = NULL;
	node->right = NULL;

	while (NULL != root)
	{
		if (root->data < val_ptr)
		{
			if (root->right)
			{
				root = root->right;
			}
			else
			{
				node->parent = root;
				root->right = node;

				return (node);
			}
		}
		else
		{
			if (root->left)
			{
				root = root->left;
			}
			else
			{
				node->parent = root;
				root->left = node;

				return (node);
			}
		}
	}

	return (root);
}

bst_node_t *RecursiveBstInsert(bst_node_t *root, int val)
{
	bst_node_t *node = NULL;
	void *val_ptr = (void *)(long)val;

	assert(root);

	if (NULL == root)
	{
		node = (bst_node_t *)malloc(sizeof(bst_node_t));

		if (NULL == node)
		{
			return (NULL);
		}

		node->data = val_ptr;
		node->left = NULL;
		node->right = NULL;

		return (node);
	}

	if ((int)(long)(root->data) < (int)(long)val_ptr)
	{
		root->right = RecursiveBstInsert(root->right, val);
	}

	else
	{
		root->left = RecursiveBstInsert(root->left, val);
	}

	return (root);
}

void BstArrInsert(int *arr, size_t index_to_insert, int val)
{
	size_t parent_index = 0;
	size_t current_index = index_to_insert;
	int temp = 0;

	assert(arr);

	arr[index_to_insert] = val;

	while (current_index > 0)
	{
		parent_index = (current_index - 1) / 2;
		if (arr[current_index] < arr[parent_index])
		{
			temp = arr[current_index];
			arr[current_index] = arr[parent_index];
			arr[parent_index] = temp;
			current_index = parent_index;
		}
		else
		{
			return;
		}
	}

	return;
}

/* Question 7 */
void FlipString(char *str, size_t from, size_t to)
{
	if (from < to)
	{
		Swap(str + from, str + to);

		FlipString(str, from + 1, to - 1);
	}

	return;
}


void Swap(char *x, char *y)
{
	char temp = 0;

	assert(x);
	assert(y);

	temp = *x;
	*x = *y;
	*y = temp;

	return;
}

/* Question 8 */

void Permute(char *str, size_t l, size_t r)
{
	size_t i = 0;

	assert(str);

	if (l == r)
	{
		printf("%s\n", str);
	}
	else
	{
		for (i = l; i <= r; i++)
		{
			Swap((str + l), (str + i));
			Permute(str, l + 1, r);
			Swap((str + l), (str + i));
		}
	}

	return;
}

/* Question 10 */
void RecStackInsert(stack_t *stack, int val)
{
	int temp = 0;

	if (StackIsEmpty(stack) || (int)(long)StackPeek(stack) > val)
	{
		StackPush(stack, (void *)(long)val);

		return;
	}

	else
	{
		temp = (int)(long)StackPeek(stack);
		StackPop(stack);
		RecStackInsert(stack, val);
		StackPush(stack, (void *)(long)temp);
	}

	return;
}