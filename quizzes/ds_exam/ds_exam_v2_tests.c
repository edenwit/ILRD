/*  Developer: Eden Wittenberg;									*
 *  Date Of Creation: 25.05.21;									*

 *  Description: Data Structure Exam;							*/
#include <stdio.h> /* printf */
#include <assert.h>
#include <stdlib.h>

/*#include "ds_exam_v2.c"*/
#include <time.h>
#define QSIZE 7

typedef struct Queue
{
	char m_queue[QSIZE];
	size_t m_elements_in_q;
	size_t m_first_element;
} circular_queue;

static void IsInsideShapeTest();
int IsInsideShape(int *bitmap, size_t width, size_t height, size_t point_x, size_t point_y);
unsigned int FindMissingNumber(const int arr[], const size_t arr_size);
static void FindMissingNumberTest();
static int IsPair(size_t num);
static void PrintQueueArr(circular_queue *queue);
static void CQueueTest();

int main()
{
	FindMissingNumberTest();
	IsInsideShapeTest();
	CQueueTest();
	
	return (0);
}

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

static void FindMissingNumberTest()
{
	int arr[1023] = {0};
	int result = 0;
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
    int rand_num = 0;	
	srand (time(NULL));

	rand_num = rand() % arr_size + 2;
	/*
    printf("random number is: %d\n", rand_num);
	printf("arr size: %ld\n", arr_size);
	*/
	for (i = 1; i < arr_size + 1; ++i)
	{
		if ((size_t)rand_num != i)
		{
			arr[i - 1] = i;		
		}
		else
		{
			arr[i - 1] = arr_size + 1;				
		}
	}
	/*
	for (i = 0; i < arr_size; ++i)
	{
		printf("%d ", arr[i]);	
	}	
	
	printf("\n");
	*/
	result = FindMissingNumber(arr, arr_size);
	
	if (rand_num != result)
	{
		printf("Failed FindMissingNumber test. expected: %d, actual: %d\n", rand_num, result);
	}
	
	return;	
}




/* Question 1 */

/*section 1 */

/* Question 6 */


/* Question 7 */

static void IsInsideShapeTest()
{
	int bitmap[5][7] = 
	{							  /**/
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 1, 0, 1, 1},
	{0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}
	};
	
	printf("1-IsInsideShape: %d\n", IsInsideShape(bitmap[0], 5, 7, 4, 2));
}

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

circular_queue *CQueueCreate()
{
	circular_queue *queue = (circular_queue *)malloc(sizeof(circular_queue));
	size_t i = 0;
	
	if (NULL == queue)
	{
		return (NULL);
	}
	
	queue->m_elements_in_q = 0;
	queue->m_first_element = 0;	

	return (queue);
}

void CQueueDestroy(circular_queue *queue)
{
	assert(queue);
	
	free(queue);
	
	return;
}

static void CQueueTest()
{
	int arr[] = {'e', 'd', 'e', 'n', '_', 'g', 'f'};
	circular_queue *queue = CQueueCreate();
	size_t i = 0;
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	
	assert(queue);

	PrintQueueArr(queue);
	
	for (i = 0; i < arr_size; ++i)
	{
		PushChar(queue, arr[i]);
		PrintQueueArr(queue);
	}

	for (i = 0; i < 3; ++i)
	{
		PopChar(queue);
		PrintQueueArr(queue);
	}
	
	for (i = 0; i < 3; ++i)
	{
		PushChar(queue, arr[i]);
		PrintQueueArr(queue);
	}	

	for (i = 0; i < 3; ++i)
	{
		PopChar(queue);
		PrintQueueArr(queue);
	}
	
	for (i = 0; i < 3; ++i)
	{
		PushChar(queue, arr[i]);
		PrintQueueArr(queue);
	}	
	
}

	char m_queue[QSIZE];
	size_t m_elements_in_q;
	size_t m_first_element;

static void PrintQueueArr(circular_queue *queue)
{
	size_t i = 0;
	
	assert(queue);

	if (((queue->m_first_element + queue->m_elements_in_q - 1) % QSIZE) >= queue->m_first_element)
    {
        for (i = queue->m_first_element; i <= ((queue->m_first_element + queue->m_elements_in_q - 1) % QSIZE); i++)
            printf("%c ",queue->m_queue[i]);
    }
    else
    {
        for (i = queue->m_first_element; i < QSIZE; i++)
            printf("%c ", queue->m_queue[i]);
 
        for (i = 0; i <= ((queue->m_first_element + queue->m_elements_in_q - 1) % QSIZE); i++)
            printf("%c ", queue->m_queue[i]);
    }

	printf("\n");
	
	return;
}
