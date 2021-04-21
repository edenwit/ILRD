#include <stddef.h> /* NULL */
#include <assert.h> /* assert */

#include "ws_sll.h"

/* Approved by Nir */
node_t *Flip(node_t *head)
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

/* Approved by Nir */
int HasLoop(const node_t *head)
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
			return 1;
		}
	}
	return 0;
}

/* Approved by Maor */
node_t *FindIntersection(node_t *head1, node_t *head2)
{
	node_t *tmp_head1 = head1;
	node_t *tmp_head2 = head2;
	
	size_t count1 = 1;
	size_t count2 = 1;
	
	assert(head1);
	assert(head2);
	
	while (NULL != tmp_head1->next)
	{
		++count1;
		tmp_head1 = tmp_head1->next;
	}
	while (NULL != tmp_head2->next)
	{
		++count2;
		tmp_head2 = tmp_head2->next;
	}
	
	if (tmp_head2 == tmp_head1)
	{
		tmp_head1 = head1;
		tmp_head2 = head2;
		
		if (count1 > count2)
		{
			while (count1 > count2)
			{
				tmp_head1 = tmp_head1->next;
				--count1;
			}	
		}
		else if (count2 > count1)
		{
			while (count2 > count1)
			{
				tmp_head2 = tmp_head2->next;
				--count2;
			}	
		}	
			
		while (tmp_head1 != tmp_head2)
			{
				tmp_head1 = tmp_head1->next;
				tmp_head2 = tmp_head2->next;
			}
			
			return tmp_head1;

	}
	
	return NULL;	
}

