
typedef struct node
{
	void *data;
	struct node *next;
	} node_t;
};

node_t *Flip(node_t *head)
{
	node_t *prev = head;
	node_t *cur = head;
	node_t *next = NULL;
	
	assert(head);

	while (NULL != cur->next)
	{
		cur = prev->next;
		next = cur->next;
		cur->next = prev;		
		prev = cur;
	}
	head->next = NULL;
	
	return cur;
}

int HasLoop(const node_t *head)
{
	node_t step1 = head;
	node_t step2 = head;
	
	assert(head);

	while (NULL != step2->next && NULL != step2->next-next)
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
	node_t t_head1 = head1;
	node_t t_head2 = head2;
	
	size_t count1 = 0;
	size_t count2 = 0;
	size_t i = 0;
	
	assert(head1);
	assert(head2);
	
	while (NULL != t_head1)
	{
		++count1;
		t_head1 = t_head1->next;
	}
	while (NULL != t_head2)
	{
		++count2;
		t_head2 = t_head2->next;
	}
	
	if (t_head2 == t_head1)
	{
		t_head1 = head1;
		t_head2 = head2;
		
		if (count1 > count2)
		{
			for (i = 0; i < (count1 - count2); ++i)
			{
				t_head1 = t_head1->next;
			}	
		}
		else if (count2 > count1)
		{
			for (i = 0; i < (count2 - count1); ++i)
			{
				t_head2 = t_head2->next;
			}	
		while (t_head1 != t_head2)
			{
				t_head1 = t_head1->next;
				t_head2 = t_head2->next;
			}
			return t_head1;
		}
	}
	
	return NULL;	
}
