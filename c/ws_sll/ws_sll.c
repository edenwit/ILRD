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

node_t *FindIntersection(node_t *head1, node_t *head2)
{
	node_t *p1 = head1;
	node_t *p2 = head2;
	size_t counter1 = 0;
	size_t counter2 = 0;
	
	assert(head1);
	assert(head2);
	
	while (NULL != p1->next) /* checked pointer instead of next alement */
	{
		++counter1;
		p1 = p1->next;
	}
	
	while (NULL != p2->next) /* checked pointer instead of next alement */
	{
		++counter2;
		p2 = p2->next;
	}
	
	if (p1 != p2)
	{
		return (NULL);
	}
	
	p1 = head1;
	p2 = head2;
	
	while (counter1 > counter2)
	{
		p1 = p1->next;
		--counter1;
	}
	
	while (counter2 > counter1)
	{
		p2 = p2->next;
		--counter2;
	}
	
	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	
	return (p1);
}
