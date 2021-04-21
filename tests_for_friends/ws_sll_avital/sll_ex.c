#include <assert.h> /* assert */
#include <stddef.h>


#include "sll_ex.h"

node_t *Flip(node_t *head)
{
	node_t *prev_node = NULL;
	node_t *cur_node = head;
	node_t *next_node = head;
	
	assert(head);
	
	while(NULL != next_node)
	{
		cur_node = next_node;
		next_node = cur_node->next;		
		cur_node->next = prev_node;
		prev_node = cur_node;


	}

	return cur_node;
}
/* Approved by Eden W */
int HasLoop(const node_t *head)
{
	node_t *jump_one = NULL;	
	node_t *jump_two = NULL;
		
	assert(head);
	
	jump_one = (node_t *)head;		
	jump_two = (node_t *)head;
	
	while (NULL != jump_two->next && NULL != jump_two->next->next)
	{
		jump_one = jump_one->next;
		jump_two = jump_two->next->next;
		
		if (jump_two == jump_one)
		{
			return 1;
		}
	}
	
	return 0;
}

/* Approved By Eden */
node_t *FindIntersection(node_t *head1, node_t *head2)
{
	size_t count1 = 1;
	size_t count2 = 1;
	int gap_cmp = 0;
	
	node_t *find1 = head1;
	node_t *find2 = head2;
	
	assert(head1);
	assert(head2);
	
	while (NULL != find1->next)
	{
		++count1;
		find1 = find1->next;
	}
	
	while (NULL != find2->next)
	{
		++count2;
		find2 = find2->next;
	}
	
	if (find1 != find2)
	{
		return NULL; 
	}
	
	find1 = head1;
	find2 = head2;
	
	gap_cmp = count1 - count2;
	
	if (0 > gap_cmp)
	{
		gap_cmp *= -1;	
		
		while (gap_cmp > 0)
		{
			find2 = find2->next;
			--gap_cmp;
		}
	}
	else
	{
		while (gap_cmp > 0)
		{
			find1 = find1->next;
			--gap_cmp;
		}
	}
	
	while (find1 != find2)
	{
		find1 = find1->next;
		find2 = find2->next;
	}
	
	return find1;
}





