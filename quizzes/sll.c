#include <stdio.h>
#include <assert.h>

#include "../ds/include/sll.h"

static void HasLoopTest();
static void FlipListTest();
static void FixLoopTest();



typedef struct node
{
	void *data;
	struct node *next;
	
} node_t;

static void printList(node_t *node);

int main()
{
	HasLoopTest();
	FlipListTest();
	FixLoopTest();
	
	return (0);
}

node_t *FlipList(node_t *head)
{
	node_t *prev_node = NULL;
	node_t *cur_node = head;
	node_t *nextmp_node = head;
	
	assert(head);

	while (NULL != nextmp_node)
	{
		cur_node = nextmp_node;
		nextmp_node = cur_node->next;
		cur_node->next = prev_node;		
		prev_node = cur_node;
	}
	
	return cur_node;
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

node_t * HasLoop(const node_t *head)
{
	node_t *step1 = (node_t *)head;
	node_t *step2 = (node_t *)head;
	
	assert(head);

	/* run until both meet if there's a loop in the list*/
	while (NULL != step2->next && NULL != step2->next->next)
	{
		step1 = step1->next;
		step2 = step2->next->next;
		
		if (step1 == step2)
		{
			return (step2);
		}
	}
	return (NULL);
}

static void HasLoopTest()
{
	int int_arr[] = {1, 5, 14, 64564, 85, 9, 15, 3, 40000, 0, -50, 900, 11, 5231};
	size_t i = 0;
	size_t arr_size = sizeof(int_arr) / sizeof(int_arr[0]);
	
	s_list_t *list = SLLCreate();
	s_list_iter_t iter = SLLBegin(list);
	node_t *saved_iter = NULL;
	node_t *head = (node_t *)SLLBegin(list);
	
	
	for (i = 0; i < arr_size ; ++i)
	{
		iter = SLLInsert(SLLEnd(list), (void *)(int_arr + i));
		if (SLLIsSameIter(iter, SLLEnd(list)))
		{
			printf("Insertion failed! at round %ld.\n", i + 1);
		}
		
		if (2 == i)
		{
			saved_iter = (node_t *)iter;
		}
	}	
	
	if (HasLoop(head))
	{
		printf("Loop found where loop shouldn't exist!\n");
	}
	
	((node_t *)iter)->next = saved_iter;	
	
	if (!HasLoop(head))
	{
		printf("Loop not found where loop should exist!\n");
	}	
	
	return;
}

void FixLoop(node_t *head)
{
	node_t *meeting_node = NULL;	
	node_t *head_step = head;
	
	assert(head);
	
	meeting_node = HasLoop(head);
	
	if (NULL == meeting_node)
	{
		return;
	}
	
	while (head_step != meeting_node)
	{
		head_step = head_step->next;
		meeting_node = meeting_node->next;		
	}
	
	while (meeting_node != head_step->next)
	{
		head_step = head_step->next;
	}
	
	head_step->next = NULL;
	
	return;
}
	
static void FixLoopTest()
{
	int int_arr[] = {1, 5, 14, 64564, 85, 9, 15, 3, 40000, 0, -50, 900, 11, 5231};
	size_t i = 0;
	size_t arr_size = sizeof(int_arr) / sizeof(int_arr[0]);
	
	s_list_t *list = SLLCreate();
	s_list_iter_t iter = SLLBegin(list);
	node_t *saved_iter = NULL;
	node_t *head = (node_t *)SLLBegin(list);

	for (i = 0; i < arr_size ; ++i)
	{
		iter = SLLInsert(SLLEnd(list), (void *)(int_arr + i));
		if (SLLIsSameIter(iter, SLLEnd(list)))
		{
			printf("Insertion failed! at round %ld.\n", i + 1);
		}
		
		if (2 == i)
		{
			saved_iter = (node_t *)iter;
		}
	}	
	
	((node_t *)iter)->next = saved_iter;	

	if (!HasLoop(head))
	{
		printf("Loop not found where loop should exist!\n");
	}	
	
	printList(head);

	FixLoop(head);

	printList(head);
	
	if (HasLoop(head))
	{
		printf("Loop found where loop shouldn't exist!\n");
	}
	
	return;	
}

static void printList(node_t *node)
{
	size_t i = 0;
	
    while (node != NULL && i < 20) 
    {
        printf("%d  ", *(int *)node->data);
        node = node->next;
        ++i;
    }
    
    printf("\n");
}
