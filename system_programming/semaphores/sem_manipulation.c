#include <sys/types.h> /* sem_t */
#include <semaphore.h> /* sem_open, sem_close */
#include <fcntl.h> /* O_CREAT */
#include <stdio.h> /* printf */
#include <assert.h>/* assert */
#include <string.h> /* strlen */
#include <stdlib.h> /* atoi */
#include <ctype.h> /* isspace */

#define UNUSED(X) ((void)X)
#define STRUCT_SIZE (5)
#define STR_SIZE (21)
#define UNDO ("undo")

typedef enum
{
    FAIL = -1,
    SUCCESS,
    EXIT
} status_type;

struct str_ops
{
    char *str_trigger;
    status_type (*cmp_func)(const char *input, const char *trigger);
    status_type (*action_func)(const char *input, sem_t *sem);
};

void SemManipulate(sem_t *sem);

static status_type ChainOfResponsibility(const char *str, sem_t *sem, const struct str_ops *struct_arr);
/* cmp funcs */
static status_type CompareWholeStr(const char *str, const char *trigger);
static status_type CompareParcedStr(const char *str, const char *trigger);
static status_type GetSuccess(const char *str, const char *semophore_name);
/* action funcs */
static status_type DecreaseSemVal(const char *str, sem_t *sem);
static status_type IncreaseSemVal(const char *str, sem_t *sem);
static status_type GetSemVal(const char *str, sem_t *sem);
static status_type ExitProg(const char *str, sem_t *sem);
static status_type DoNothing(const char *str, sem_t *sem);
/* inner funcs */
static int IncreaseByNum(sem_t *sem, size_t num_of_loops);
static int DecreaseByNum(sem_t *sem, size_t num_of_loops);

static char *SkipSpace(char *str);

/* global undo operations var */
int undo_sum = 0;

int main(int argc, char **argv)
{
    sem_t *sem = NULL;

    assert(1 < argc);

    sem = sem_open(argv[1], O_CREAT, 0660, 0);

    if (SEM_FAILED == sem)
    {
        return (FAIL);
    }
    
    printf("semophore '%s' created. \n", argv[1]);

    SemManipulate(sem);
    
    sem_unlink(argv[1]);
    
    return (SUCCESS);
}

void SemManipulate(sem_t *sem)
{
    char str[STR_SIZE] = {'\0'};
    status_type finished = SUCCESS;
    static const struct str_ops struct_arr[] =
        {
            {"D", CompareParcedStr, DecreaseSemVal},
            {"I", CompareParcedStr, IncreaseSemVal},
            {"V", CompareWholeStr, GetSemVal},
            {"X", CompareWholeStr, ExitProg},
            {"", GetSuccess, DoNothing}};

    assert(sem);

    printf("Enter operation (up to %d characters):\n", STR_SIZE - 1);

    while (EXIT != finished)
    {
        fgets(str, STR_SIZE - 1, stdin);
        finished = ChainOfResponsibility(str, sem, struct_arr);
    }

    return;
}

static status_type ChainOfResponsibility(const char *str, sem_t *sem, const struct str_ops *struct_arr)
{
    size_t i = 0;
    status_type operate = SUCCESS;
    
    assert(sem);
    assert(str);
    assert(struct_arr);

    str = SkipSpace((char *)str);

    for (i = 0; i < STRUCT_SIZE; ++i)
    {
        operate = struct_arr[i].cmp_func(str, struct_arr[i].str_trigger);

        if (SUCCESS == operate)
        {
            return (struct_arr[i].action_func(str, sem));
        }
    }

    return (FAIL);
}

static status_type CompareWholeStr(const char *str, const char *trigger)
{
    assert(str);
    assert(trigger);

    return ((0 == strncmp(trigger, str, strlen(str) - 1)) ? SUCCESS : FAIL);
}

static status_type CompareParcedStr(const char *str, const char *trigger)
{
    assert(str);
    assert(trigger);

    if (*trigger == *str)
    {
        ++str;
        str = SkipSpace((char *)str);
        
        if (atoi(str))
        {
            return (SUCCESS);
        }
    }

    return (FAIL);
}

static status_type GetSuccess(const char *str, const char *semophore_name)
{
    UNUSED(str);
    UNUSED(semophore_name);

    return (SUCCESS);
}

static status_type GetSemVal(const char *str, sem_t *sem)
{
    int val = 0;
 
    UNUSED(str);

    assert(sem);

    if (-1 == sem_getvalue(sem, &val))
    {
        return (FAIL);
    }

    printf("Semophore value: %d\n", val);

    return (SUCCESS);
}

static status_type ExitProg(const char *str, sem_t *sem)
{
    UNUSED(str);
    UNUSED(sem);

    printf("Undoing %d operations.\n", undo_sum);

    if (0 < undo_sum)
    {
        IncreaseByNum(sem, undo_sum);
    }
    else
    {
        DecreaseByNum(sem, (-1) * undo_sum);
    }

    GetSemVal(NULL, sem);
    puts("Exiting Program.\n");

    return (EXIT);
}

static status_type DoNothing(const char *str, sem_t *sem)
{
    UNUSED(str);
    UNUSED(sem);

    return (SUCCESS);
}

static status_type IncreaseSemVal(const char *str, sem_t *sem)
{
    size_t loops = 0;
    int status = 0;

    assert(sem);
    assert(str);

    ++str;

    str = SkipSpace((char *)str);

    loops = strtod((char *)str, (char **)&str);

    IncreaseByNum(sem, loops);

    str = SkipSpace((char *)str);

    if (!CompareWholeStr(str, UNDO))
    {
        undo_sum -= loops;
    }

    return (status);
}

static status_type DecreaseSemVal(const char *str, sem_t *sem)
{
    size_t loops = 0;
    int status = 0;

    assert(sem);
    assert(str);

    ++str;
    str = SkipSpace((char *)str);

    loops = strtod((char *)str, (char **)&str);

    DecreaseByNum(sem, loops);

    str = SkipSpace((char *)str);

    if (!CompareWholeStr(str, UNDO))
    {
        undo_sum += loops;
    }

    return (status);
}

static int DecreaseByNum(sem_t *sem, size_t num_of_loops)
{
    size_t i = 0;
    int status = 0;

    assert(sem);

    for (i = 0; i < num_of_loops && (-1 != status); ++i)
    {
        status = sem_wait(sem);
    }

    return (SUCCESS);
}

static int IncreaseByNum(sem_t *sem, size_t num_of_loops)
{
    size_t i = 0;
    int status = 0;

    assert(sem);

    for (i = 0; i < num_of_loops && (-1 != status); ++i)
    {
        status = sem_post(sem);
    }

    return (SUCCESS);
}


static char *SkipSpace(char *str)
{
    assert(str);

    while (isspace(*str))
    {
        ++str;
    }

    return (str);
}