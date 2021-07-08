/*
  Name : Nir
  Status: Reviewed
  Reviewer: Eden Wittenberg
  Description: FSM calculator
  Date : 19/06/2021
*/


#define  isnan(x) ((x) != (x)) /* Is not a number function for ansi standart */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen */
#include <ctype.h> /* isspace */
#include <math.h> /*pow, isnan */
#include <assert.h> 

#include "calculator.h"
#include "stack.h"


typedef enum 
{
    WAIT_FOR_DIGIT,
    WAIT_FOR_OPERATOR,
    ERROR_STATE,
    STATES_SIZE
} state_t;

typedef enum 
{
    DIGIT_EVENT,
    ADD_EVENT,
    SUBSTRACT_EVENT,
    MULTIPLICATION_EVENT,
    DIV_EVENT,
    POW_EVENT,
    OPEN_BRACKET_EVENT,
    CLOSE_BRACKET_EVENT,
    ERROR_EVENT,
    EVENTS_SIZE
} event_t;

#define UNUSED(x) ((void)(x))


typedef struct calculator
{
    stack_t *operands;
    stack_t *operators;
    const char *exp_ptr;
    event_t curr_event;
} calc_t;

typedef calc_status_t (*char_handler_t)(calc_t *calculator);
typedef calc_status_t (*arit_operation_t)(double left, double right, double *result);

typedef struct transaction
{
    char_handler_t event_handler;
    state_t next_state;
} trans_t;

/* Lut getters */
static event_t GetEvent(char input);
static trans_t GetTransition(state_t curr_state, event_t curr_event);
static int IsPreceding(event_t first_op, event_t second_op);
static arit_operation_t GetOpFunc(event_t curr_event);

/* Calculator event loop functions */ 
static calc_status_t SubCalc(calc_t *calculator);
static calc_status_t SkipSpace(calc_t *calculator);
static calc_status_t Nothing(calc_t *calculator);
static calc_status_t PushNum(calc_t *calculator);
static calc_status_t SkipChar(calc_t *calculator);
static calc_status_t HandleNegative(calc_t *calculator);
static calc_status_t HandleCloseBrackets(calc_t *calculator);
static calc_status_t HandleOpenBrackets(calc_t *calculator);
static calc_status_t HandleOpenBracketsAsOp(calc_t *calculator);

static calc_status_t PerformOperation(calc_t *calculator, arit_operation_t op_func);

/* Operation functions */
static calc_status_t NoOperation(double left, double right, double *result);
static calc_status_t Add(double left, double right, double *result);
static calc_status_t Substract(double left, double right, double *result);
static calc_status_t Pow(double left, double right, double *result);
static calc_status_t Mul(double left, double right, double *result);
static calc_status_t Div(double left, double right, double *result);



/* O(1) */
static event_t GetEvent(char input)
{
    static event_t char_to_event [256] = 
    { 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            OPEN_BRACKET_EVENT, CLOSE_BRACKET_EVENT, MULTIPLICATION_EVENT, ADD_EVENT, ERROR_EVENT,   SUBSTRACT_EVENT, ERROR_EVENT, DIV_EVENT, 
            DIGIT_EVENT, DIGIT_EVENT, DIGIT_EVENT, DIGIT_EVENT, DIGIT_EVENT, DIGIT_EVENT, DIGIT_EVENT, DIGIT_EVENT, 
            DIGIT_EVENT, DIGIT_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, POW_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
            ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, ERROR_EVENT, 
    };

    return (char_to_event[(size_t)input]);

}
/* O(1) */
static trans_t GetTransition(state_t curr_state, event_t curr_event)
{
    static trans_t trans_lut[STATES_SIZE][EVENTS_SIZE] = 
    {
        { 
            {PushNum, WAIT_FOR_OPERATOR}, {Nothing, WAIT_FOR_DIGIT}, {HandleNegative, WAIT_FOR_DIGIT}, {Nothing, ERROR_STATE}, 
            {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE}, {HandleOpenBrackets, WAIT_FOR_DIGIT}, {Nothing, ERROR_STATE},{Nothing, ERROR_STATE},
        },
        { 
            {Nothing, ERROR_STATE}, {SubCalc, WAIT_FOR_DIGIT}, {SubCalc, WAIT_FOR_DIGIT}, {SubCalc, WAIT_FOR_DIGIT}, 
            {SubCalc, WAIT_FOR_DIGIT}, {SubCalc, WAIT_FOR_DIGIT}, {HandleOpenBracketsAsOp, WAIT_FOR_DIGIT}, {HandleCloseBrackets, WAIT_FOR_OPERATOR}, {Nothing, ERROR_STATE},
        },
        { 
            {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE}, 
            {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE}, {Nothing, ERROR_STATE},
        }
    };

    return (trans_lut[curr_state] [curr_event]);
}

/* O(1) */
static arit_operation_t GetOpFunc(event_t curr_event)
{
    static arit_operation_t  op_lut[EVENTS_SIZE] = 
    {
        NoOperation, Add, Substract, Mul, Div, Pow, NoOperation, NoOperation, NoOperation
    };

    return (op_lut[curr_event]);
}

/* O(1) */
static int IsPreceding(event_t first_op, event_t second_op)
{

    static int precedence_lut[EVENTS_SIZE][EVENTS_SIZE] = 
    {
        { 
            0, 0, 0, 0, 0, 0, 0, 0,0,
        },
        { 
            1, 1, 1, 0, 0, 0, 0, 0,0,
        },
        { 
            1, 1, 1, 0, 0, 0, 0, 0,0,
        },
        { 
            1, 1, 1, 1, 1, 0, 0, 0,0,
        },
        { 
            1, 1, 1, 1, 1, 0, 0, 0,0,
        },
        { 
            1, 1, 1, 1, 1, 0, 0, 0,0,
        },
        { 
            1, 0, 0, 0, 0, 0, 0, 0,0,
        },
        { 
            0, 0, 0, 0, 0, 0, 0, 0,0,
        },
        { 
            0, 0, 0, 0, 0, 0, 0, 0,0,
        }
    };

    return (precedence_lut[first_op][second_op]);
}

/* O(1) */
static calc_t *CreateCalculator(const char *expression)
{
    const size_t exp_len = strlen(expression);
    const double dummy_operand = 0.0; 
    calc_t *calculator = malloc(sizeof(calc_t));

    assert(expression);


    if (!calculator)
    {
        return (NULL);
    }

    calculator->operands = StackCreate(exp_len + 1);
    if (!calculator->operands)
    {
        free(calculator);
    }

    calculator->operators = StackCreate(exp_len + 2);
    if (!calculator->operators)
    {
        StackDestroy(calculator->operands);
        free(calculator);
    }

    calculator->curr_event = DIGIT_EVENT;
    calculator->exp_ptr = expression;

    /* Dummy event and number */
    StackPush(calculator->operators, (void *)CLOSE_BRACKET_EVENT);
    StackPush(calculator->operators, (void *)CLOSE_BRACKET_EVENT);
    StackPush(calculator->operands, *(void **)&dummy_operand);

    return (calculator);
}

/* O(1) */
static void DestroyCalculator(calc_t *calculator)
{
    assert(calculator);

    StackDestroy(calculator->operands);
    StackDestroy(calculator->operators);
    free(calculator);

    return;
}

/* O(n) n - number of chars  */
calc_status_t Calculate(const char *expression, double *result)
{
    calc_t *calculator = NULL;
    calc_status_t status = SUCCESS;
    trans_t curr_trans = {0};
    state_t curr_state = DIGIT_EVENT;

    assert(expression);
    assert(result);

    calculator = CreateCalculator(expression);
    if(!calculator)
    {
        return (SYSTEM_FAIL);
    }

    SkipSpace(calculator);

    while (ERROR_STATE != curr_state && 0 == status 
           && '\0' != *(calculator->exp_ptr))
    {
      calculator->curr_event = GetEvent(*(calculator->exp_ptr));
      curr_trans = GetTransition(curr_state, calculator->curr_event);
    
      status = curr_trans.event_handler(calculator);
      curr_state = curr_trans.next_state;
      SkipChar(calculator);
    }

    if (ERROR_STATE == curr_state || WAIT_FOR_DIGIT == curr_state)
    {
        status = INVALID_EQUATION; 
    }
    else if (!status)
    {
        /* Push event to calculate the rest */
        calculator->curr_event = DIGIT_EVENT;
        status = SubCalc(calculator);
        *(void **)result = StackPeek(calculator->operands);
    }

    DestroyCalculator(calculator);

    return (status); 
}

/* O(m) m - number of operators with equal precdence */
static calc_status_t SubCalc(calc_t *calculator)
{
    calc_status_t status = SUCCESS;
    event_t prev_op = (event_t)StackPeek(calculator->operators);

    while ( status == 0 &&
            IsPreceding(prev_op, calculator->curr_event))
    {
        status = PerformOperation(calculator, GetOpFunc(prev_op));
        StackPop(calculator->operators);
        prev_op = (event_t)StackPeek(calculator->operators);
    }

    StackPush(calculator->operators, (void *)(size_t)(calculator->curr_event));
    
    return (status);
}

/* O(m) m - number of operators with equal precdence */
static calc_status_t HandleCloseBrackets(calc_t *calculator)
{
    calc_status_t status = SUCCESS;
    event_t prev_op = (event_t)StackPeek(calculator->operators);

    while (SUCCESS == status &&
           OPEN_BRACKET_EVENT != prev_op)
    {
        status = PerformOperation(calculator, GetOpFunc(prev_op));
        StackPop(calculator->operators);
        prev_op = (event_t)StackPeek(calculator->operators);
    }

    StackPop(calculator->operators);

    return (status);
}

/* O(1) */
static calc_status_t HandleOpenBracketsAsOp(calc_t *calculator)
{
    calc_status_t status = 0;
    assert(calculator);

    calculator->curr_event = MULTIPLICATION_EVENT;
    status = SubCalc(calculator);
    StackPush(calculator->operators, (void *) OPEN_BRACKET_EVENT);

    return (status);
}

/* O(1) */
static calc_status_t HandleOpenBrackets(calc_t *calculator)
{
    assert(calculator);

    StackPush(calculator->operators, (void *)OPEN_BRACKET_EVENT);

    return (SUCCESS);
}

/* O(1) */
static calc_status_t Nothing(calc_t *calculator)
{
    UNUSED(calculator);

    return (SUCCESS);
}

/* O(k) k- number of spaces in a equence */
static calc_status_t SkipSpace(calc_t *calculator)
{
    while (isspace(*(calculator->exp_ptr)))
    {
        ++(calculator->exp_ptr);
    }

    return (SUCCESS);
}

/* O(n + k) n - number size in digits k- number of spaces in a equence */
static calc_status_t PushNum(calc_t *calculator)
{
    double num = 0.0;

    assert(calculator);

    num = strtod(calculator->exp_ptr, (char **)&(calculator->exp_ptr));
    StackPush(calculator->operands, *(void **)&num);

    --(calculator->exp_ptr);

    return (SUCCESS);
}

static calc_status_t SkipChar(calc_t *calculator)
{
    ++(calculator->exp_ptr);
    SkipSpace(calculator);

    return (SUCCESS);
}

static calc_status_t HandleNegative(calc_t *calculator)
{
    const double negative = -1.0;
    StackPush(calculator->operands, *(void **)&negative);
    StackPush(calculator->operators, (void *)MULTIPLICATION_EVENT);

    return (SUCCESS);

}

/* O(1) */
static calc_status_t PerformOperation(calc_t *calculator, arit_operation_t op_func)
{
    void *first = NULL;
    calc_status_t status = SUCCESS;
    void *second = StackPeek(calculator->operands);

    assert(calculator);
    assert(op_func);

    StackPop(calculator->operands);
    first = StackPeek(calculator->operands);
    StackPop(calculator->operands);

    status = op_func(*(double *)&(first), *(double *)&(second), (double *)&first);

    StackPush(calculator->operands, first);

    SkipSpace(calculator);

    return (status);
}


/* O(1) */
static calc_status_t NoOperation(double left, double right, double *result)
{
    UNUSED(left);
    UNUSED(right);
    UNUSED(result);

    return (INVALID_EQUATION);
}

/* O(1) */
static calc_status_t Add(double left, double right, double *result)
{
    assert(result);

    *result = left + right;

    return (SUCCESS);
}

/* O(1) */
static calc_status_t Substract(double left, double right, double *result)
{
    assert(result);

    *result = left - right;

    return (SUCCESS);
}

/* O(1) */
static calc_status_t Pow(double left, double right, double *result)
{
    assert(result);

    *result = pow(left, right);

    if ((0 == left && 0 >= right) || isnan(*result))
    {
        return (MATH_ERROR);
    }

    return (SUCCESS);    
}

/* O(1) */
static calc_status_t Mul(double left, double right, double *result)
{
    assert(result);

    *result = left * right;

    return (SUCCESS);
}

/* O(1) */
static calc_status_t Div(double left, double right, double *result)
{
    assert(result);

    if (0 == right)
    {
        return (MATH_ERROR);
    }

    *result = left / right;

    return (SUCCESS);
}
