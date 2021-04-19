
struct s_list_node
{
	void *data;
	s_list_iter_t next;
};

struct s_list
{
	s_list_iter_t head;
	s_list_iter_t tail;
};

enum status
{
	SUCCESS,
	FAIL
};

s_list_t *SLLCreate(void)
{
	
}

{
	/* create the list manager */
	s_list_t *list = (s_list_t *)malloc(sizeof(s_list));

	if (NULL == list)
	{    
		return FAIL;
	}

	s_list_iter_t dummy = (s_list_iter_t)malloc(sizeof(s_list_node));
	
	vector->arr = (void **)malloc(capacity*sizeof(void*));	
	
	if (NULL == vector->arr)
	{   
		free(vector);
		return NULL;
	}

	vector->size = 0; 

	return vector;

}

void SLLDestroy(s_list_t *list);

int SLLIsEmpty (const s_list_t *list);
{
	return list->head.next == NULL);
}

size_t SLLCount(const s_list_t *list)
{

}

s_list_iter_t SLLBegin(const s_list_t *list)
{
	return list->head->next;
}

s_list_iter_t SLLEnd(const s_list_t *list)
{
	s_list_iter_t temp = NULL;
	
	
	
}
s_list_iter_t SLLNext(const s_list_iter_t iter)
{
	assert(iter);
	
	if (SLLIsEmpty())
	
	return iter.next;
}

int SLLIsSameIter(const s_list_iter_t iter1, const s_list_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return iter1->data == iter2->data;
}

void SLLSetData(s_list_iter_t iter, void *data)
{
	assert(iter);
	
	iter->data = data;
	
	return;
}

void *SLLGetData(const s_list_iter_t iter)
{
	return iter->data;
}

s_list_iter_t SLLRemove(s_list_iter_t iter)
{
	
}
int SLLInsert(s_list_iter_t where, void *data)
{
	
}

s_list_iter_t SLLFind(s_list_iter_t from, s_list_iter_t to, int (*match_func)(const void * data,void *param),void *param);
int SLLForEach(s_list_iter_t from,s_list_iter_t to, int (*action_func)(void * data,void *param),void *param);
