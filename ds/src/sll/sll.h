18.4.20 14:26 version_2

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct s_list s_list_t;
typedef struct s_list_node *s_list_iter_t;

/*
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
*/


s_list_t *SLLCreate(void);
void SLLDestroy(s_list_t *list);

int SLLIsEmpty (const s_list_t *list);
size_t SLLCount(const s_list_t *list);

s_list_iter_t SLLBegin(const s_list_t *list);
s_list_iter_t SLLEnd(const s_list_t *list);
s_list_iter_t SLLNext(const s_list_iter_t iter);

void SLLSetData(s_list_iter_t iter, void *data);
void *SLLGetData(const s_list_iter_t iter);

s_list_iter_t SLLRemove(s_list_iter_t iter);
int SLLInsert(s_list_iter_t where, void *data);
int SLLIsSame(s_list_iter_t iter1, s_list_iter_t iter2);
-
s_list_iter_t SLLFind(s_list_iter_t from, s_list_iter_t to, int (*match_func)(const void * data,void *param),void *param);
int SLLForEach(s_list_iter_t from,s_list_iter_t to, int (*action_func)(void * data,void *param),void *param);


#endif /* __LINKED_LIST_H__ */
