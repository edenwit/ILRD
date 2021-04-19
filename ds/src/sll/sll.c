#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */

#include "sll.h"

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
	dummy->data = list;
	dummy->next = NULL;	

	return list;

}

void SLLDestroy(s_list_t *list)
{
	s_list_iter_t temp;
	
	assert(list);
	
	temp = list-> head;
	
	while (NULL != temp->next)
	{
		temp->data = NULL;
		
		temp = SLLRemove(temp);
	}
	
	list->tail = NULL;
	list->head = NULL;
	free(temp);
	free(list);
	
}

int SLLIsEmpty (const s_list_t *list)
{
	return SLLIsSameIter(SLLBegin(list),SLLEnd(list));
}

/*
size_t SLLCount(const s_list_t *list)
{

}*/

s_list_iter_t SLLBegin(const s_list_t *list)
{
	return list->head;
}

s_list_iter_t SLLEnd(const s_list_t *list)
{
	return list->tail;	
}

s_list_iter_t SLLNext(const s_list_iter_t iter)
{
	assert(iter);
	
	return iter->next;
}

int SLLIsSameIter(const s_list_iter_t iter1, const s_list_iter_t iter2) /*O(1)*/

{
	assert(iter1);
	assert(iter2);
	
	return iter1->data == iter2->data;
}

/* approved by nir */
void SLLSetData(s_list_iter_t iter, void *data)
{
	assert(iter);
	assert(iter->next);	
	
	iter->data = data;
	
	return;
}


/* approved by nir */
void *SLLGetData(const s_list_iter_t iter)
{
	return iter->data;
}


s_list_iter_t SLLRemove(s_list_iter_t iter)
{
	s_list_iter_t temp = iter->next;

	assert(iter);
	
	iter->data = iter->next->data;
	iter->next = iter->next->next;

	if (NULL == iter->next)
	{
	((s_list_t *)(iter->data))->tail = iter;
	}

	temp->data = NULL;
	temp->next = NULL;	
	free(temp);

	return iter;
	
}

s_list_iter_t SLLInsert(s_list_iter_t where, void *data)    
 /* on success: O(1); on failure O(n) */
{
	s_list_iter_t node = NULL;
	s_list_t *where_data = where->data;
	assert(where);
	
	node = (s_list_iter_t)malloc(sizeof(struct s_list_node));
	
	if (NULL == node)
	{   
		while (NULL != where->next)
		{
			where = SLLNext(where);
		}
		return where;
	}	
	
	if (NULL == where->next)
	{
		where_data->tail = node;
	}
	
	node->data = where->data;
	node->next = where->next;
	
	where->next = node;
	where->data = data;
	
	return where;
}

/*
s_list_iter_t SLLFind(s_list_iter_t from, s_list_iter_t to, int (*match_func)(const void * data,void *param),void *param);

int SLLForEach(s_list_iter_t from,s_list_iter_t to, int (*action_func)(void * data,void *param),void *param)
{
	s_list_iter_t cur_iter = NULL;
	
	assert(from);
	assert(to);
	
	cur_iter->data = from->data;
	cur_iter->next = from->next;
	
	while (cur_iter ())
		
	
}*/
