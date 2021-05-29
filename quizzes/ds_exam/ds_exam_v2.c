/*  Developer: Eden Wittenberg;									*
 *  Date Of Creation: 25.05.21;									*

 *  Description: Data Structure Exam;							*/


/* Question 1 */

/*section 1 */

/*fixed type names only */
void *FSAAlloc(fsa_t *fsa)
{
	fsa_block_header_t *block_ptr = NULL;
	
	assert(fsa);
	
	if (0 == fsa->next_free)
	{
		return (NULL);
	}
	
	block_ptr = (fsa_block_header_t *)((char *)fsa + fsa->next_free); /*fixed forgotten parentheses */
	fsa->next_free = ((fsa_t *)block_ptr)->next_free;
	
	return (block_ptr);
}

/*fixed type names only */
void FSAFree(fsa_t *fsa, void *mem_block) /* wrong place for star fixed*/
{
	assert(fsa);
	assert(mem_block);
	
	((fsa_block_header_t *)mem_block)->next_free = fsa->next_free; 
	fsa->next_free = (size_t)((char *)(mem_block) - (char *)fsa); /*fixed forgotten parentheses */
	
	return; /* added return */
}


/*section 2 */
#define BLOCK_SIZE (sizeof(vsa_block_header_t))
#define VSA_T_SIZE (sizeof(vsa_t))
void *VSAAlloc(vsa_t *vsa, size_t n_bytes)/* fixed place of star */
{
	vsa_block_header_t *ptr = NULL;
	size_t tot_count = 0;
	size_t keep_size = 0;
	
	assert(vsa);
	assert(0 < n_bytes);
	
	ptr = (vsa_block_header_t *)((char *)vsa + VSA_T_SIZE); /* fixed forgotten closing parentheses and pointer casting*/
	
	while (tot_count + n_bytes < vsa->pool_size)
	{
		if (ptr->chunk_size > (long)(n_bytes + BLOCK_SIZE)) /* forgot ending parentheses and long casting*/
		{
			keep_size = ptr->chunk_size;
			ptr->chunk_size = n_bytes * (-1);
			ptr = (vsa_block_header_t *)((char *)ptr + BLOCK_SIZE);  /* forgot opening parentheses */
			((vsa_block_header_t *)((char *)ptr + n_bytes))->chunk_size /* wrote "next free" instead of "chunk_size" */
			= (keep_size - n_bytes - BLOCK_SIZE); /* forgot opening parentheses */
			
			return (ptr);
		}
		
		if ((ptr->chunk_size == (long)n_bytes) || /* long casting */
		((ptr->chunk_size == (long)(n_bytes + BLOCK_SIZE)))) /* long casting */
		{
			ptr->chunk_size *= (-1); /* forgot to multiply original value */
			ptr = (vsa_block_header_t *)((char *)ptr + BLOCK_SIZE); /* forgot ending parentheses, assigined to chunk value instead of pointer */
			
			return (ptr);
		}
		tot_count += labs(ptr->chunk_size) + BLOCK_SIZE; /* changed ABS to labs */
		ptr = (vsa_block_header_t *)((char *)ptr + BLOCK_SIZE + labs(ptr->chunk_size)); /* forgot ending parentheses + star at casting, changed ABS to labs */
	}
	
	return (NULL);
}

/*fixed type names */
void VSAFree(void *mem_block)
{
	assert(mem_block);
	
	((vsa_block_header_t *)((char *)mem_block - BLOCK_SIZE))->chunk_size *= (-1); /* forgot closing parentheses */
	
	return;
}

/*section 3 */

/*Replaced all impl with section 1 solution */
void *VSAAlloc(*vsa_t vsa, size_t n_bytes)/* wrong place for star */
{
	vsa_chunk_t *ptr = NULL;
	size_t tot_count = 0;
	size_t keep_size = 0;
	
	assert(vsa);
	assert(0 < n_bytes);
	
	ptr = (vsa_chunk_t)((char *)vsa + VSA_T_SIZE;
	
	while (tot_count + n_bytes < vsa_pool_size)
	{
		if (ptr->chunk_size > ((n_bytes + BLOCK_SIZE) /* forgot ending parentheses */
		{
			keep_size = ptr->chunk_size;
			ptr->chunk_size = n_bytes * (-1);
			ptr = (vsa_chunk_t *)(char *)ptr + BLOCK_SIZE);  /* forgot opening parentheses */
			(vsa_chunk_t *)(char *)ptr + n_bytes)->next_free
			= (keep_size - n_bytes - BLOCK_SIZE); /* forgot opening parentheses */
			
			return (ptr);
		}
		
		if ((ptr->chunk_size == n_bytes) ||
		((ptr->chunk_size == n_bytes + BLOCK_SIZE)))
		{
			ptr->chunk_size = (-1);
			ptr->chunk_size = (vsa_chunk_t *)((char *)ptr + BLOCK_SIZE; /* forgot ending parentheses */
			
			return (ptr);
		}
		tot_count += ABS(ptr->chunk_size) + BLOCK_SIZE;
		ptr = (vsa_chunk_t)((char *)ptr + BLOCK_SIZE + ABS(ptr->chunk_size); /* forgot ending parentheses + star at casting */
	}
	
	return (NULL);
}

void VSAFree(void *mem_block)
{
	assert(mem_block);
	
	(vsa_chunk_t *)((char *)mem_block - BLOCK_SIZE)->chunk_size *= (-1);
	
	return;
}

/* Question 2 */

/* works without fixes */
node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *cur = head;
	node_t *next = head;
	
	assert(head);
	
	while (NULL != next)
	{
		cur = next;
		next = cur->next;
		cur->next = prev;
		prev = cur;
	}
	
	return (cur);
}

/* Question 3 */

/*section 1  - complexity question */

/*section 2 */

/* works without fixes */
node_t *HasLoop(node_t *head)
{
	node_t *fast = head;
	node_t *slow = head;

	assert(head);
	
	while (NULL != fast->next && NULL != fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		
		if (fast == slow)
		{
			return (fast);
		}
	}
	
	return (NULL);
}

/* works without fixes */
void FixLoop(node_t *head)
{
	node_t *looper = NULL;
	node_t *walker = head;
	
	assert(head);
	
	looper = HasLoop(head);
	
	if (NULL == looper)
	{
		return;
	}
	
	while (looper != walker)
	{
		looper = looper->next;
		walker = walker->next;
	}
	
	while (looper->next != walker)
	{
		looper = looper->next;	
	}
	
	looper->next = NULL;
		
	return; /* added return; */
}

/*section 3 */
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
	{s
		p1 = p1->next;
		p2 = p2->next;
	}
	
	return (p1);
}

void OpenIntersection(node_t *head1, node_t *head2)
{
	node_t *node = NULL;
	
	assert(head1);
	assert(head2;
	
	node = HasIntersection(head1, head2);
	
	if (NULL == node)
	{
		return;
	}
	
	while (node != head1->next)
	{
		head1 = head1->next;
	}
	
	head1->next = NULL;
	
	return ; /* added return; */
}

/* Question 4 */

/*fixed type names */
s_list_iter_t SLLRemove(s_list_iter_t iter)
{
	s_list_iter_t tmp = iter->next;
	
	assert(iter);
	
	iter->data = tmp->data;
	iter->next = iter->next->next;
	
	if (NULL == iter->next)
	{
		((s_list_t *)(iter->data))->tail = iter; /* forgot semi-colon and closing parentheses */
	}
	
	free(tmp);
	
	return (iter);
}
/* Question 5 */

/*fixed type names */
d_list_iter_t DLLInsert(d_list_iter_t where, void *data)
{
	d_list_iter_t iter = NULL;
	
	assert(where);
	
	iter = (d_list_iter_t)malloc(sizeof(struct d_list_node)); /*\ added struct word */
	
	if (NULL == iter)
	{
		while (NULL != where->next)
		{
			where = where->next;
		}
		
		return (where);
	}
	
	iter->data = data;
	where->prev->next = iter;
	iter->prev = where->prev;
	where->prev = iter;
	iter->next = where;
	
	return (iter);	
}

/*fixed type names */
d_list_iter_t DLLRemove(d_list_iter_t iter)
{

	d_list_iter_t tmp = iter;
	
	assert(iter);

	tmp = iter->next;
	
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;  
	
	iter->next = NULL;	/*forgot do clean next val*/
	iter->prev = NULL;	/*forgot do clean prev val*/
	iter->data = NULL;  /*forgot do clean data*/
	
	free(iter);
	
	return (tmp);
}

/* Question 6 */

unsigned int FindMissingNumber(const int arr[], const size_t arr_size)
{
	unsigned int n_sum = 0;
	unsigned int arr_sum = 0;
	size_t i = 0;

    assert(NULL != arr);

    for (i = 0; i < arr_size; ++i)
    {
        arr_sum += arr[i];
    }

	n_sum = (((arr_size + 1) * (arr_size + 2)) / 2);

    return (n_sum - arr_sum);
}


/* Question 7 */
int IsInsideShape(int *bitmap, size_t rows, size_t colls, size_t point_x, size_t point_y)
{
	size_t i = 0;
	size_t cross_count = 0;
	size_t inner_count = 0;
	
	assert(bitmap);
	
	if (1 == *(bitmap + (point_y * colls) + point_x))
	{
		return (0);
	}
	
	for (i = 0; i < (point_x); ++i)
	{
		if (1 == *(bitmap + (point_y * colls) + i) && 1 != *(bitmap + (point_y * colls) + i + 1))
		{
			++cross_count;
		}
	}
	
	if (IsPair(cross_count))
	{
		return (0);
	}
	
	cross_count = 0;

	for (i = point_x + 1; i < colls ; ++i) 
	{
		if (1 == *(bitmap + (point_y * colls) + i) && 1 != *(bitmap + (point_y * colls) + i + 1))
		{
			++cross_count;
		}
		++inner_count;
	}	

	if (IsPair(cross_count))
	{
		return (0);
	}
	
	cross_count = 0;
	
	for (i = 0; i < (point_y); ++i) 
	{
		if (1 == *(bitmap + point_x + (i * colls)) && 1 != *(bitmap + point_x + ((i + 1) * rows)))
		{
			++cross_count;
		}
	}	

	if (IsPair(cross_count))
	{
		return (0);
	}	

	cross_count = 0;
	
	for (i = point_y + 1; i < rows; ++i) 
	{
		if (1 == *(bitmap + (i * colls) + point_x) && 1 != *(bitmap + point_x + ((i + 1) * rows)))
		{
			++cross_count;
		}
		++inner_count;
	}	

	if (IsPair(cross_count))
	{
		return (0);
	}	

	return (1);	
}

static int IsPair(size_t num)
{
	return (0 == (num % 2));
}

/* Question 8 */

int PushChar(struct Queue *q, char ch) /* should create typedef for struct Queue */
{
	size_t loc = 0;
	
	assert(q);
	
	if (QSIZE == q->m_elements_in_q)
	{
		return (1);
	}
	/* changed direction of queueu to work with size_t values. */
	loc = (q->m_first_element + q->m_elements_in_q) % QSIZE;
	
	q->m_queue[loc] = ch;
	++q->m_elements_in_q;
	
	return (0);
}

char PopChar(struct Queue *q)
{
	char tmp = '0';
	
	assert(q);
	assert(0 < q->m_elements_in_q); /* changed check to assersion */
	
	tmp = q->m_queue[q->m_first_element];
	
	/* changed direction of queueu to work with size_t values. */	
	q->m_first_element = (q->m_first_element + 1) % QSIZE;
	
	--q->m_elements_in_q; /* order of expression not as conventions */
	
	return (tmp);
}
