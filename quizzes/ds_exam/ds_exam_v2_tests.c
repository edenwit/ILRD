/*  Developer: Eden Wittenberg;									*
 *  Date Of Creation: 25.05.21;									*

 *  Description: Data Structure Exam;							*/


/* Question 1 */

/*section 1 */

/* Question 7 */

static void IsInsideShapeTest()
{
	int bitmap[20][20] = 
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}					
	};
}

int IsInsideShape(int **bitmap, int width, int height, int point_x, int point_y)
{
	size_t i = 0;
	size_t cross_count = 0;
	
	assert(bitmap);
	
	if (1 == bitmap[point_x][point_y])
	{
		return (0);
	}
	
	for (i = 0; i < (point_x - 1); ++i)
	{
		if (1 == bitmap[i][point_y] && 1 != bitmap[i + 1][point_y])
		{
			++cross_count;
		}
	}
	
	if (IsPair(cross_count))
	{
		return (0);
	}
	
	cross_count = 0;
	
	for (i = point_x; i < (width - 1); ++i)
	{
		if (1 == bitmap[i][point_y] && 1 != bitmap[i + 1][point_y])
		{
			++cross_count;
		}
	}	

	if (IsPair(cross_count))
	{
		return (0);
	}
	
	cross_count = 0;
	
	for (i = 0; i < (point_y - 1); ++i)
	{
		if (1 == bitmap[point_x][i] && 1 != bitmap[point_x][i + 1])
		{
			++cross_count;
		}
	}	

	if (IsPair(cross_count))
	{
		return (0);
	}	
	
	cross_count = 0;
	
	for (i = point_y; i < (height - 1); ++i)
	{
		if (1 == bitmap[point_x][i] && 1 != bitmap[point_x][i + 1])
		{
			++cross_count;
		}
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
	
	loc = q->m_first_element - q->m_elements_in_q;
	
	if (0 > QSIZE)
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
