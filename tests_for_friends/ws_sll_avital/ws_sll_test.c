#include <stddef.h> /* NULL */
#include <stdio.h> /* printf */

#include "sll_ex.h"

static void FlipTest();
static void HasLoopTest();
static void FindIntersectionTest();

static void PrintList(node_t *head);

int main()
{
	FlipTest();
	HasLoopTest();
	FindIntersectionTest();
	
	return 0;

}

static void FlipTest()
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
	
	tester = Flip(tester);
			
	if (tester != &elem_5)
	{
		printf("Flip Test Failed! head is: %d, expected: %d.\n", *(int *)(tester->data), *(int *)elem_5.data);
	}
	
	tester = Flip(tester);	
	
	if (tester != &elem_1)
	{
		printf("Flip Test Failed! head is: %d, expected: %d.\n", *(int *)(tester->data), *(int *)elem_1.data);
	}

	tester = Flip(&elem_5);	
	
	if (tester != &elem_5)
	{
		printf("Flip Test Failed! head is: %d, expected: %d.\n", *(int *)(tester->data), *(int *)elem_5.data);
	}
	
	return;
}

static void HasLoopTest()
{
	int arr[] = {1, 2, 3, 4, 5};

	node_t *head = NULL;
	
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
	
	elem_5.next = &elem_2;
	elem_4.next = &elem_5;
	elem_3.next = &elem_4;
	elem_2.next = &elem_3;
	elem_1.next = &elem_2;
	
	head = &elem_1;
	
	if (!HasLoop(head))
	{
		printf("List has loop and test failed!\n");
	}

	elem_5.next = NULL;
	
	if (HasLoop(head))
	{
		printf("List does not have loop!\n");
	}

	return;
}

static void FindIntersectionTest()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	node_t elem_1 = {NULL, NULL};
	node_t elem_2 = {NULL, NULL};
	node_t elem_3 = {NULL, NULL};
	node_t elem_4 = {NULL, NULL};
	
	node_t elem_5 = {NULL, NULL};
	node_t elem_6 = {NULL, NULL};
	
	node_t elem_7 = {NULL, NULL};
	node_t elem_8 = {NULL, NULL};
	node_t elem_9 = {NULL, NULL};

	
	elem_1.data = arr;
	elem_2.data = (arr + 1);
	elem_3.data = (arr + 2);
	elem_4.data = (arr + 3);
	elem_5.data = (arr + 4);
	
	elem_6.data = (arr + 5);
	elem_7.data = (arr + 6);
	elem_8.data = (arr + 7);
	elem_9.data = (arr + 8);

	elem_9.next = NULL;
	elem_8.next = &elem_9;
	elem_7.next = &elem_8;

	elem_6.next = &elem_7;
	elem_5.next = &elem_6;

	elem_4.next = &elem_7;
	elem_3.next = &elem_4;
	elem_2.next = &elem_3;
	elem_1.next = &elem_2;
	

	if (&elem_7 != FindIntersection(&elem_1, &elem_5))
	{
		printf("FindIntersection has faild! found: %d , expected: %d.\n", *(int *)elem_7.data,  *(int *)(FindIntersection(&elem_1, &elem_5)->data));
	}
	
	if (&elem_7 != FindIntersection(&elem_4, &elem_5))
	{
		printf("FindIntersection has faild! found: %d , expected: %d.\n", *(int *)elem_7.data, *(int *)(FindIntersection(&elem_4, &elem_5)->data));
	}

	if (&elem_7 != FindIntersection(&elem_3, &elem_5))
	{
		printf("FindIntersection has faild! found: %d , expected: %d.\n", *(int *)elem_7.data,  *(int *)(FindIntersection(&elem_3, &elem_5)->data));
	}

	if (&elem_7 != FindIntersection(&elem_7, &elem_7))
	{
		printf("FindIntersection has faild! found: %d , expected: %d.\n", *(int *)elem_7.data,  *(int *)(FindIntersection(&elem_7, &elem_7)->data));
	}

	if (&elem_9 != FindIntersection(&elem_9, &elem_9))
	{
		printf("FindIntersection has faild! found: %d , expected: %d.\n", *(int *)elem_9.data, *(int *)(FindIntersection(&elem_9, &elem_9)->data));
	}

	elem_4.next = NULL;

	if (NULL != FindIntersection(&elem_1, &elem_5))
	{
		printf("FindIntersection has faild! found: %d , expected: NULL.\n", *(int *)(FindIntersection(&elem_1, &elem_5)->data));
	}	
	

	return;
}


static void PrintList(node_t *head)
{
	while (NULL != head)
	{
		printf("%d ", *(int *)(head->data));
		head = head->next;
	}
	printf("\n");
	
	return;
}

