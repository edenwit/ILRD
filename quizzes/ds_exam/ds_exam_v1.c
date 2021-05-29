/*  Developer: Eden Wittenberg;									*
 *  Date Of Creation: 25.05.21;									*

 *  Description: Data Structure Exam;							*/


/* Question 1 */

/*section 1 */
void *FSAAlloc(fsa_t *fsa)
{
	fsa_head_t *block_ptr = NULL;
	
	assert(fsa);
	
	if (0 == fsa->next_free)
	{
		return (NULL);
	}
	
	block_ptr = (fsa_header_t *)(char *)fsa + fsa->next_free);
	fsa->next_free = ((fsa *)block_ptr)->next_free;
	
	return (block_ptr);
}

void FsaFree(fsa_t *fsa, *void mem_block) /* wrong place for star */
{
	assert(fsa);
	assert(mem_block);
	
	((fsa_header_t *)mem_block)->next_free = fsa->next_free;
	fsa->next_free = (size_t)((char *)mem_block - (char *)fsa);
}

/*section 2 */
#define BLOCK_SIZE (sizeof(vsa_chunk_t))
#define VSA_T_SIZE (sizeof(vsa_t))

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

/*section 3 */
void *FSAAllocAligned(fsa_t *fsa)
{
	fsa_header_t *ptr = NULL;
	
	assert(fsa);
	
	if (0 == fsa->next_free)
	{
		return (NULL);
	}
	
	ptr = (fsa_header_t *)(char *)fsa + fsa->next_free; /* forgot parentheses */
	
	while (0 != (size_t)(ptr) % WORD_SIZE)
	{
		ptr = (char *)ptr + 1;
	}
	
	fsa->next_free = ((fsa_t *)ptr)->next_free); /* unnecessary ending parentheses */
	
	return (ptr);
}

void FsaFree(fsa_t *fsa, *void mem_block) /* wrong place for star */
{
	assert(fsa);
	assert(mem_block);
	
	((fsa_header_t *)mem_block)->next_free = fsa->next_free;
	fsa->next_free = (size_t)((char *)mem_block - (char *)fsa);
}

/* Question 2 */


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
		
	/* may add return; */
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
	
	while (NULL != p1)
	{
		++counter1;
		p1 = p1->next;
	}
	
	while (NULL != p2)
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
	
	/* may add return; */
}

/* Question 4 */

iter_t Remove(iter_t iter)
{
	iter_t tmp = iter->next;
	
	assert(iter);
	
	iter->data = tmp->data;
	iter->next = iter->next->next;
	
	if (NULL == iter->next)
	{
		((list_t *)(iter->data)->tail = iter /* forgot semi-colon */
	}
	
	free(tmp);
	
	return (iter);
}

/* Question 5 */

dll_iter Insert(dll_iter where, void *data)
{
	dll_iter iter = NULL;
	
	assert(where);
	
	iter = (dll_iter)malloc(sizeof(node_t));
	
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

dll_iter Remove(dll_iter iter)
{
	dll_iter tmp = iter;
	
	assert(iter);
	
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
	
	free(iter);
	
	return (tmp);
}

/* Question 6 */
/* I wrote only a verbal answer in the exam. will implament in v2. */
/* 
sum all numbers in arr using loop
sum all numbers from 1 to k using formula: (k * (k + 1)) / 2
subtract first sum from second sum and get the result
*/


/* Question 7 */
/* I wrote only a verbal answer in the exam. will implament in v2. */
/*
get a coordinate.
if value in coordinate is 1 - return FALSE
loop on x axis from 0 to coor x and count 1's.
if odd number - True
else - False
*/

/* Question 8 */

int PushChar(struct Queue *q, char ch) /* should create typedef for struct Queue */
{
	size_t loc = 0;
	
	assert(q);
	
	if (QSIZE == q->m_elements_in_q)
	{
		return (1);
	}
	
	loc = q->m_first_element - q->m_elements_in_q;
	
	if (0 > loc)
	{
		loc += QSIZE;
	}
	
	q->m_queue[loc] = ch;
	++q->m_elements_in_q;
	
	return (0);
}

char PopChar(struct Queue *q)
{
	char tmp = '0';
	
	assert(q);
	
	if (0 == m_elements_in_q)
	{
		return ('\0');
	}
	
	tmp = q->m_queue[m_first_element];
	m_first_element = m_first_element - m_elements_in_q;
	
	if (m_first_element < 0) /* order of expression not as conventions */
	{
		m_first_element += QSIZE;
	}
	
	m_elements_in_q--; /* order of expression not as conventions */
	
	return (tmp);
}
