#include <string.h> /* strlen */
#include <math.h> /*pow */
#include <assert.h>
#include <stdlib.h>  /* strtod */

#include "calculator.h"
#include "stack.h"

#define UNUSED(x) ((void)(x))
#define CHARS (256)

typedef enum
{
    WAIT_FOR_DIGIT,
    WAIT_FOR_OPERATOR,
    ERROR_STATE,
    STATES
} state_t;

typedef enum
{
    DIGIT,
    ADDITION,
    MINUS,
    MULTIPLY,
    DIVIDE,
    POWER,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    ERROR,
    SPACE,
    EVENTS
} event_t;

typedef struct calculator
{
    event_t active_event;
    char *expression;
    stack_t *digit_stack;
    stack_t *operators_stack;
} calculator_t;

typedef calc_status_t (*action_func)(calculator_t *calculator);
typedef calc_status_t (*calc_func_t)(double num1, double num2, double *result);

typedef struct func_and_state
{
    action_func event_handler;
    state_t next_state;
} func_state_t;

static calc_status_t InitCalc(calculator_t *calculator, char *expression);
static void FinitCalc(calculator_t *calculator);

static event_t GetEvent(char input);
static func_state_t GetTransition(state_t active_state, event_t active_event);
static calc_status_t CheckForOpenPars(event_t event);
static int IsPreceding(event_t first_op, event_t second_op);
static calc_func_t GetOpFunc(event_t active_event);

static calc_status_t HandleSubCalc(calculator_t *calculator);
static calc_status_t EmptyStack(calculator_t *calculator);

static calc_status_t GetSuccess(calculator_t *calculator);
static calc_status_t HandleNumber(calculator_t *calculator);
static calc_status_t HandleNegative(calculator_t *calculator);
static calc_status_t HandleClosePars(calculator_t *calculator);
static calc_status_t HandleOpenPars(calculator_t *calculator);
static calc_status_t HandleOpenParsAsOp(calculator_t *calculator);

static calc_status_t GoNext(calculator_t *calculator);

static calc_status_t Calc(calculator_t *calculator, calc_func_t action_func);

static calc_status_t HandleInvalidEquetion(double num1, double num2, 
                                           double *calc_res);
static calc_status_t Addition(double num1, double num2, double *calc_res);
static calc_status_t Subtraction(double num1, double num2, double *calc_res);
static calc_status_t Power(double num1, double num2, double *calc_res);
static calc_status_t Multiplication(double num1, double num2, double *calc_res);
static calc_status_t Division(double num1, double num2, double *calc_res);

calc_status_t Calculate(const char *expression, double *result)
{
    calculator_t calculator = {0};
    func_state_t curr_trans = {0};
    state_t active_state = DIGIT;
    calc_status_t status = SUCCESS;

    assert(expression);
    assert(result);

    status = InitCalc(&calculator, (char *)expression);

    if(SUCCESS != status)
    {
        return (SYSTEM_FAIL);
    }

    while ((ERROR_STATE != active_state) &&
           (SUCCESS == status) && ('\0' != *(calculator.expression)))
    {
      calculator.active_event = GetEvent(*(calculator.expression));
      curr_trans = GetTransition(active_state, calculator.active_event);

      status = curr_trans.event_handler(&calculator);
      active_state = curr_trans.next_state;
      GoNext(&calculator);
    }

    if ( (WAIT_FOR_OPERATOR != active_state) && (MATH_ERROR != status))
    {
        status = INVALID_EQUATION;
    }

    else if (SUCCESS == status)
    {
        calculator.active_event = ADDITION;
        status = EmptyStack(&calculator);
        *(void **)result = StackPeek(calculator.digit_stack);
    }

    FinitCalc(&calculator);

    return (status);
}

static calc_status_t InitCalc(calculator_t *calculator, char *expression)
{
    double dummy_number = 0.0;
    size_t len_of_exp = 0;

    assert(calculator);
    assert(expression);

    len_of_exp = strlen(expression);

    calculator->digit_stack = StackCreate(len_of_exp + 1);

    if (NULL == calculator->digit_stack)
    {
        return (SYSTEM_FAIL);
    }

    calculator->operators_stack = StackCreate(len_of_exp + 2);

    if (NULL == calculator->operators_stack)
    {
       StackDestroy(calculator->digit_stack);

       return (SYSTEM_FAIL);
    }

    calculator->active_event = DIGIT;
    calculator->expression = expression;

    StackPush(calculator->operators_stack, (void *)CLOSE_PARENTHESIS);
    StackPush(calculator->operators_stack, (void *)CLOSE_PARENTHESIS);
    StackPush(calculator->digit_stack, *(void **)&dummy_number);

    return (SUCCESS);
}

static void FinitCalc(calculator_t *calculator)
{
    assert(calculator);

    StackDestroy(calculator->digit_stack);
    StackDestroy(calculator->operators_stack);

    return;
}

static calc_status_t HandleSubCalc(calculator_t *calculator)
{
    calc_status_t status = SUCCESS;
    event_t operation_in_stack = SPACE;

    assert(calculator);

    operation_in_stack = (event_t)StackPeek(calculator->operators_stack);

    while ((SUCCESS == status) && 
           (IsPreceding(operation_in_stack, calculator->active_event)))
    {
        status = Calc(calculator, GetOpFunc(operation_in_stack));
        StackPop(calculator->operators_stack);
        operation_in_stack = (event_t)StackPeek(calculator->operators_stack);
    }

    StackPush(calculator->operators_stack, 
             (void *)(size_t)(calculator->active_event));

    return (status);
}

static calc_status_t EmptyStack(calculator_t *calculator)
{
    calc_status_t status = SUCCESS;
    event_t operation_in_stack = SPACE;

    assert(calculator);

    operation_in_stack = (event_t)StackPeek(calculator->operators_stack);

    status = CheckForOpenPars(operation_in_stack);

    while ((SUCCESS == status) && 
           (IsPreceding(operation_in_stack, calculator->active_event)))
    {
        status = Calc(calculator, GetOpFunc(operation_in_stack));
        StackPop(calculator->operators_stack);
        operation_in_stack = (event_t)StackPeek(calculator->operators_stack);
    }

    StackPush(calculator->operators_stack, 
             (void *)(size_t)(calculator->active_event));

    return (status);
}


static calc_status_t HandleOpenParsAsOp(calculator_t *calculator)
{
    calc_status_t status = SUCCESS;

    assert(calculator);

    calculator->active_event = MULTIPLY;
    status = HandleSubCalc(calculator);
    StackPush(calculator->operators_stack, (void *) OPEN_PARENTHESIS);

    return (status);
}

static calc_status_t HandleOpenPars(calculator_t *calculator)
{
    assert(calculator);

    StackPush(calculator->operators_stack, (void *)OPEN_PARENTHESIS);

    return (SUCCESS);
}

static calc_status_t HandleClosePars(calculator_t *calculator)
{
    calc_status_t status = SUCCESS;
    event_t operation_in_stack = SPACE;

    assert(calculator);

    operation_in_stack = (event_t)StackPeek(calculator->operators_stack);

    while ((SUCCESS == status) && (OPEN_PARENTHESIS != operation_in_stack))
    {
        status = Calc(calculator, GetOpFunc(operation_in_stack));
        StackPop(calculator->operators_stack);
        operation_in_stack = (event_t)StackPeek(calculator->operators_stack);
    }

    StackPop(calculator->operators_stack);

    return (status);
}

static calc_status_t GetSuccess(calculator_t *calculator)
{
    UNUSED(calculator);

    return (SUCCESS);
}

static calc_status_t GoNext(calculator_t *calculator)
{
    assert(calculator);

    ++(calculator->expression);

    return (SUCCESS);
}

static calc_status_t HandleNumber(calculator_t *calculator)
{
    double num = 0.0;

    assert(calculator);

    num = strtod(calculator->expression, (char **)&(calculator->expression));

    StackPush(calculator->digit_stack, *(void **)&num);

    --(calculator->expression);

    return (SUCCESS);
}

static calc_status_t HandleNegative(calculator_t *calculator)
{
    double negative = -1.0;

    StackPush(calculator->digit_stack, *(void **)&negative);
    StackPush(calculator->operators_stack, (void *)MULTIPLY);

    return (SUCCESS);
}

static calc_status_t Calc(calculator_t *calculator, calc_func_t action_func)
{
    void *second_to_pop = NULL;
    calc_status_t status = SUCCESS;
    void *first_to_pop = NULL;

    assert(calculator);
    assert(action_func);

    first_to_pop = StackPeek(calculator->digit_stack);
    StackPop(calculator->digit_stack);

    second_to_pop = StackPeek(calculator->digit_stack);
    StackPop(calculator->digit_stack);

    status = action_func(*(double *)&(second_to_pop),
            *(double *)&(first_to_pop), (double *)&second_to_pop);

    StackPush(calculator->digit_stack, second_to_pop);

    return (status);
}

static calc_status_t HandleInvalidEquetion
                     (double num1, double num2, double *calc_res)
{
    UNUSED(num1);
    UNUSED(num2);
    UNUSED(calc_res);

    return (INVALID_EQUATION);
}

static calc_status_t Addition(double num1, double num2, double *calc_res)
{
    *calc_res = num1 + num2;

    return (SUCCESS);
}

static calc_status_t Subtraction(double num1, double num2, double *calc_res)
{
    *calc_res = (num1 - num2);

    return (SUCCESS);
}

static calc_status_t Multiplication(double num1, double num2, double *calc_res)
{
    *calc_res = (num1 * num2);

    return (SUCCESS);
}

static calc_status_t Division(double num1, double num2, double *calc_res)
{
    if (0.0 == num2)
    {
        return (MATH_ERROR);
    }

    *calc_res = (num1 / num2);

    return (SUCCESS);
}

static calc_status_t Power(double num1, double num2, double *calc_res)
{
    if ((0.0 == num1 && 0.0 >= num2) || (0.0 > num1 && 1 > num2))
    {
        return (MATH_ERROR);
    }

    *calc_res = pow(num1, num2);

    return (SUCCESS);
}

static event_t GetEvent(char input)
{
    static event_t char_to_event [CHARS] =
    {
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, SPACE,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             SPACE,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            OPEN_PARENTHESIS,CLOSE_PARENTHESIS, MULTIPLY, ADDITION, ERROR, 
              MINUS, ERROR, DIVIDE,DIGIT, DIGIT,
            DIGIT,           DIGIT,             DIGIT,    DIGIT,    DIGIT,
               DIGIT, DIGIT, DIGIT, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    POWER,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR, 
              ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR, 
              ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR, 
              ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR, 
              ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR, ERROR, ERROR, ERROR, ERROR,
            ERROR,           ERROR,             ERROR,    ERROR,    ERROR,
               ERROR,
    };

    return (char_to_event[(size_t)input]);
}

static func_state_t GetTransition(const state_t active_state,
                                  const event_t active_event)
{
    static func_state_t func_state_lut[STATES][EVENTS] =
    {
        {{HandleNumber, WAIT_FOR_OPERATOR}, {GetSuccess, WAIT_FOR_DIGIT},
         {HandleNegative, WAIT_FOR_DIGIT}, {GetSuccess, ERROR_STATE},
         {GetSuccess, ERROR_STATE}, {GetSuccess, ERROR_STATE},
          {HandleOpenPars, WAIT_FOR_DIGIT}, {GetSuccess, ERROR_STATE},
         {GetSuccess, ERROR_STATE}, {GetSuccess, WAIT_FOR_DIGIT}
        },
        {{GetSuccess, ERROR_STATE}, {HandleSubCalc, WAIT_FOR_DIGIT},
         {HandleSubCalc, WAIT_FOR_DIGIT}, {HandleSubCalc, WAIT_FOR_DIGIT},
         {HandleSubCalc, WAIT_FOR_DIGIT}, {HandleSubCalc, WAIT_FOR_DIGIT},
         {HandleOpenParsAsOp, WAIT_FOR_DIGIT}, {HandleClosePars, WAIT_FOR_OPERATOR},
         {GetSuccess, ERROR_STATE}, {GetSuccess, WAIT_FOR_OPERATOR}
        },
        {{GetSuccess, ERROR_STATE}, {GetSuccess, ERROR_STATE},
        {GetSuccess, ERROR_STATE}, {GetSuccess, ERROR_STATE},
         {GetSuccess, ERROR_STATE}, {GetSuccess, ERROR_STATE},
         {GetSuccess, ERROR_STATE}, {GetSuccess, ERROR_STATE},
         {GetSuccess, ERROR_STATE}, {GetSuccess, ERROR_STATE}
        }
    };

    return (func_state_lut[active_state][active_event]);
}

static calc_func_t GetOpFunc(const event_t active_event)
{
    static calc_func_t  lut_operators[EVENTS] =
    {HandleInvalidEquetion, Addition, Subtraction, Multiplication,
    Division, Power, HandleInvalidEquetion, HandleInvalidEquetion,
    HandleInvalidEquetion, HandleInvalidEquetion};

    return (lut_operators[active_event]);
}

static int IsPreceding(const event_t op_in_stack, const event_t op_in_exp)
{
    static int precedence_lut[EVENTS][EVENTS] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    return (precedence_lut[op_in_stack][op_in_exp]);
}


static calc_status_t CheckForOpenPars(event_t event)
{
    static calc_status_t open_without_close[] = 
    {SUCCESS, SUCCESS, SUCCESS, SUCCESS, SUCCESS, 
    SUCCESS, INVALID_EQUATION, SUCCESS, SUCCESS, SUCCESS};

    return (open_without_close[event]);
}