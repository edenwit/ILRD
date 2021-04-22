#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */

#include "sll.h"

#define UNUSED(X) ((void) X)

static int Add1(void * data, void *param);


struct s_list_node
{
        void *data;
        struct s_list_node *next;
};

struct s_list
{
        struct s_list_node *head;
        struct s_list_node *tail;
};

enum status
{
	SUCCESS,
	FAIL
};

/* approved by Shelly */
s_list_t *SLLCreate(void)
{
	/* create the list manager */
	s_list_t *list = (s_list_t *)malloc(sizeof(s_list_t));
	s_list_iter_t dummy = NULL;
	
	if (NULL == list)
	{    
		return NULL;
	}
	/* create the dummy node */
	dummy = (s_list_iter_t)malloc(sizeof(struct s_list_node));
	
	if (NULL == dummy)
	{   
		free(list);
		return NULL;
	}
	
	list->head = dummy;
	list->tail = dummy;
	SLLSetData(dummy, list);
	dummy->next = NULL;	

	return list;

}

/* approved by Shelly */
void SLLDestroy(s_list_t *list)
{

	assert(list);
	
	while (!SLLIsEmpty(list))
	{
		SLLRemove(SLLBegin(list));
	}
	free(SLLBegin(list));
	
	list->tail = NULL;
	list->head = NULL;

	free(list);
	
}

/* approved by Shelly */
int SLLIsEmpty (const s_list_t *list)
{
	assert(list);	
	
	return SLLIsSameIter(SLLBegin(list),SLLEnd(list));
}

/* approved by Shelly */
size_t SLLCount(const s_list_t *list)
{
	size_t counter = 0;

	assert(list);	
		
	SLLForEach(SLLBegin(list), SLLEnd(list), Add1, (void *)&counter);
	
	return counter;
}

/* approved by Shelly */
s_list_iter_t SLLBegin(const s_list_t *list)
{
	assert(list);	
	
	return list->head;
}

/* approved by Shelly */
s_list_iter_t SLLEnd(const s_list_t *list)
{
	assert(list);	
	
	return list->tail;	
}

s_list_iter_t SLLNext(const s_list_iter_t iter)
{
	assert(iter);
	
	return iter->next;
}

/* approved by Ohad */
int SLLIsSameIter(const s_list_iter_t iter1, const s_list_iter_t iter2) /*O(1)*/
{
	assert(iter1);
	assert(iter2);
	
	return iter1 == iter2;
}

/* approved by nir */
void SLLSetData(s_list_iter_t iter, void *data)
{
	assert(iter);
	
	iter->data = data;
	
	return;
}


/* approved by nir */
void *SLLGetData(const s_list_iter_t iter)
{
	return iter->data;
}


/* approved by Shelly */
s_list_iter_t SLLRemove(s_list_iter_t iter)
{
	s_list_iter_t temp = iter->next;

	assert(iter);
	
	SLLSetData(iter,SLLGetData(iter->next));
	iter->next = iter->next->next;

	if (NULL == iter->next)
	{
		((s_list_t *)(iter->data))->tail = iter;
	}

	SLLSetData(temp,NULL);
	temp->next = NULL;	
	free(temp);

	return iter;
	
}

/* approved by Shelly */
s_list_iter_t SLLInsert(s_list_iter_t where, void *data)    
 /* on success: O(1); on failure O(n) */
{
	s_list_iter_t node = NULL;
	s_list_t *where_data = SLLGetData(where);
	assert(where);
	
	node = (s_list_iter_t)malloc(sizeof(struct s_list_node));
	
	if (NULL == node)
	{   
		while (NULL != SLLNext(where))
		{
			where = SLLNext(where);
		}
		
		return where;
	}
	if (NULL == SLLNext(where))

	{
		where_data->tail = node;
	}

	SLLSetData(node, SLLGetData(where));
	node->next = SLLNext(where);
	where->next = node;
	SLLSetData(where,data);
	
	return where;
}


/* approved by Ohad */
s_list_iter_t SLLFind(s_list_iter_t from, 
					  s_list_iter_t to,
					  int (*match_func)(const void * data,void *param),
					  void *param)
{
	assert(from);

	while (!SLLIsSameIter(from,to))
	{
		if (match_func(SLLGetData(from), param))
		{
			return from;
		}
		from = SLLNext(from);
	}
	
		return to;
}


/* approved by Ohad */
int SLLForEach(s_list_iter_t from,s_list_iter_t to, int (*action_func)(void * data,void *param),void *param)
{
	int status = 0;

	assert(from);
	
	while (!SLLIsSameIter(from,to) && (0 == status))
	{
		status = action_func(SLLGetData(from), param);
		from = SLLNext(from);
	}
	
	return status;
}

static int Add1(void * data, void *param)
{
	UNUSED(data);
	
	++*(size_t *)param;
		
	return 0;
}
/* approved by Shelly */
void SLLAppend(s_list_t  *dest, s_list_t  *src)  /* O(1)*/
{
	assert(src);	
	assert(dest);	
	
	if (SLLIsEmpty(src))
	{
		return;
	}
	
	*(dest->tail) = *(src->head);
	dest->tail = src->tail;
	
	SLLBegin(src)->next = NULL;
	SLLSetData(SLLBegin(src),src);	
	src->tail = src->head;
	
	SLLSetData(SLLEnd(dest),dest);	
	
	return;
}
