#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "calculator.h"
#include "stack.h"

#define STATE (3)
#define EVENTS (256)
#define RETURN_VAL (2)
#define OPERATORS (8)

#define UNUSED(X) ((void)X)

/*#define ERROR_STATE, GoNext (ERROR_STATE, GoNext)*/
/*#define WAIT_FOR_DIGIT, GoNext (WAIT_FOR_DIGIT, GoNext)*/
/*#define WAIT_FOR_OPERATOR, DigitFunc (WAIT_FOR_OPERATOR, DigitFunc)*/
/*#define WAIT_FOR_DIGIT, OperatorFunc (WAIT_FOR_DIGIT, OperatorFunc)*/
/*#define WAIT_FOR_OPERATOR, GoNext (WAIT_FOR_OPERATOR, GoNext)*/

typedef struct state state_t;
typedef struct calculator calculator_t;
typedef int (*oper_func_t)(calculator_t *, char *, char **);
typedef int (*calc_func_t)(double num1, double num2, double *res);
typedef int (*calc_type_func_t)(calculator_t *calc, calc_func_t func);

typedef enum operators
{
    NOTHING,
    PLUS,
    MINUS ,
    MULTIPLY,
    DIVISE,
    POWER,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    NUM_OF_OPERATORS
} operators_t;

typedef enum calc_state
{
    WAIT_FOR_DIGIT,
    WAIT_FOR_OPERATOR,
    ERROR_STATE
} calc_state_t;

struct state
{
    calc_state_t state;
    int (*oper_func)(calculator_t *calc, char *exp, char **ptr);
};

struct calculator
{
    stack_t *operators_stack;
    stack_t *digit_stack;
    calc_state_t active_state;
    /*
    state_t **lut_state;
    calc_func_t **operators_funcs;
    */
};

static int GoNext           (calculator_t *calc, char *exp, char **ptr);
static int DigitFunc        (calculator_t *calc, char *exp, char **ptr);
static int OperatorFunc     (calculator_t *calc, char *exp, char **ptr);

static int ClosedParsWFO (calculator_t *calc, char *exp, char **ptr);
static int OpenParWFD(calculator_t *calc, char *exp, char **ptr);
static int OpenParWFO(calculator_t *calc, char *exp, char **ptr);
static int PushMinuS(calculator_t *calc, char *exp, char **ptr);

static int EmptyStack(calculator_t *calc, operators_t index);

static operators_t ToEnum   (char *exp);

static int InitCalc         (calculator_t *calculator, size_t stack_size);
void CalcDestroy(calculator_t *calculator);

/*
static state_t **InitLutState();
static calc_func_t **InitLutOperators();
*/
int DoCalcs(calculator_t *calc, int (*calc_func)(double num1, double num2, double *res));
int DoNotCalc(calculator_t *calc, int (*calc_func_t)(double num1, double num2, double *res));

int Addition         (double num1, double num2, double *res);
int Subtraction      (double num1, double num2, double *res);
int Multiplication   (double num1, double num2, double *res);
int Division         (double num1, double num2, double *res);
int Power            (double num1, double num2, double *res);
int DoNothing        (double num1, double num2, double *res);

static state_t lut_state[STATE][EVENTS] = {{{ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {WAIT_FOR_DIGIT, GoNext},
                                            {WAIT_FOR_DIGIT, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {WAIT_FOR_DIGIT, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {WAIT_FOR_DIGIT, OpenParWFD}, {ERROR_STATE, DigitFunc}, {ERROR_STATE, GoNext}, {WAIT_FOR_OPERATOR, DigitFunc}, {ERROR_STATE, GoNext}, {WAIT_FOR_DIGIT, PushMinuS}, {WAIT_FOR_OPERATOR, DigitFunc}, {ERROR_STATE, GoNext}, 
                                            {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, 
                                            {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, {WAIT_FOR_OPERATOR, DigitFunc}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}},

                                           {{ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {WAIT_FOR_OPERATOR, GoNext},
                                            {WAIT_FOR_OPERATOR, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {WAIT_FOR_OPERATOR, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {WAIT_FOR_DIGIT, OpenParWFO}, {WAIT_FOR_OPERATOR, ClosedParsWFO}, {WAIT_FOR_DIGIT, OperatorFunc}, {WAIT_FOR_DIGIT, OperatorFunc}, {ERROR_STATE, GoNext}, {WAIT_FOR_DIGIT, OperatorFunc}, {ERROR_STATE, GoNext}, {WAIT_FOR_DIGIT, OperatorFunc},  {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {WAIT_FOR_DIGIT, OperatorFunc}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext},
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, 
                                            {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}},

                                           {{ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}, {ERROR_STATE, GoNext}}
                                           };
/*
static calc_func_t lut_operators[OPERATORS][OPERATORS] =
    {   
        {DoNothing, DoNothing,      DoNothing,      DoNothing,      DoNothing,      DoNothing},
        {DoNothing, Addition ,      Addition,       DoNothing,      DoNothing,      DoNothing},
        {DoNothing, Subtraction,    Subtraction,    DoNothing,      DoNothing,      DoNothing},
        {DoNothing, Multiplication, Multiplication, Multiplication, Multiplication, DoNothing},
        {DoNothing, Division,       Division,       Division,       Division,       DoNothing},
        {DoNothing, Power,          Power,          Power,          Power,          DoNothing}
    };

static calc_type_func_t lut_do_donothing[OPERATORS][OPERATORS] =
    {   
        {DoNotCalc, DoNotCalc,  DoNotCalc,  DoNotCalc,  DoNotCalc,  DoNotCalc},
        {DoNotCalc, DoCalcs ,   DoCalcs,    DoNotCalc,  DoNotCalc,  DoNotCalc},
        {DoNotCalc, DoCalcs,    DoCalcs,    DoNotCalc,  DoNotCalc,  DoNotCalc},
        {DoNotCalc, DoCalcs,    DoCalcs,    DoCalcs,    DoCalcs,    DoNotCalc},
        {DoNotCalc, DoCalcs,    DoCalcs,    DoCalcs,    DoCalcs,    DoNotCalc},
        {DoNotCalc, DoCalcs,    DoCalcs,    DoCalcs,    DoCalcs,    DoNotCalc}
    };

*/


static calc_func_t lut_operators_flat[OPERATORS] =
    {   DoNothing, Addition,    Subtraction,    Multiplication, Division,       Power};

static calc_type_func_t lut_do_donothing_flat[OPERATORS] =
    {   DoNotCalc, DoCalcs,     DoCalcs,    DoCalcs,    DoCalcs,    DoCalcs};



static int lut_prec[OPERATORS][OPERATORS] =
{
{0, 0, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 0, 0, 0, 1},
{0, 1, 1, 1, 1, 0, 0, 1},
{0, 1, 1, 1, 1, 0, 0, 1},
{0, 1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 0}
};

calc_status_t Calculate(const char *expression, double *result)
{
    calculator_t calc = {0};
    char *ptr_start = (char *)expression;
    char *ptr_get = ptr_start;
    int action_res = 0;
   /* operators_t index = 0;*/

    assert(expression);
    assert(result);

    InitCalc(&calc, strlen(expression) + 1);
    printf("------------------------------------\n");
    printf("%s\n", ptr_start);

    while (('\0' != *ptr_start) && (ERROR_STATE != calc.active_state) && (0 == action_res))
    {  
        action_res = lut_state[calc.active_state][(int)*ptr_start].oper_func(&calc, ptr_start, &ptr_get);
        
        calc.active_state = lut_state[calc.active_state][(int)*ptr_start].state;

        ptr_start = ptr_get;

       /* printf("%s\n", ptr_start);*/

    }

    printf("\n");

    /*printf("aciton func: %d, state: %d\n", action_res, calc.active_state);*/
    if (WAIT_FOR_OPERATOR != calc.active_state)
    {
        printf("INVALID EQUATION\n");

        return (INVALID_EQUETION);
    }

    if (1 == action_res)
    {
        printf("MATH ERROR\n");

        return (MATH_ERROR);
    }

    while (0 == action_res && !StackIsEmpty(calc.operators_stack))
    {
        /*index = (operators_t)StackPeek(calc.operators_stack);*/
        action_res = lut_do_donothing_flat[(operators_t)StackPeek(calc.operators_stack)](&calc, lut_operators_flat[(operators_t)StackPeek(calc.operators_stack)]);
        /*lut_do_donothing_flat[index](&calc, lut_operators_flat[index]);*/
        /*DoCalcs(&calc, lut_operators_flat[index]);*/
       /* printf("in here\n");*/

    }

    if (1 == action_res)
    {
        printf("MATH ERROR\n");

        return (MATH_ERROR);
    }

/*
    EmptyStack(&calc);
*/
    /*printf("here\n");*/
    *(void **)result = StackPeek(calc.digit_stack);

    printf("result: %f\n\n", *result);

    CalcDestroy(&calc);

    return (SUCCESS);
}

static int GoNext(calculator_t *calc, char *exp, char **ptr)
{
    UNUSED(calc);
    UNUSED(exp);

    ++(*ptr);

    return (EXIT_SUCCESS);
}

static int DigitFunc(calculator_t *calc, char *exp, char **ptr)
{
    double strtod_res = 0.0;
    calc_status_t status = SUCCESS;

    strtod_res = strtod(exp, ptr);

    StackPush(calc->digit_stack, *(void **)&strtod_res);

    return (status);
}

static int OpenParWFD(calculator_t *calc, char *exp, char **ptr)
{
    operators_t oper = OPEN_PARENTHESIS;

    UNUSED(exp);
    /*printf("right here\n");*/
    StackPush(calc->operators_stack, *(void **)&oper);

    ++(*ptr);
    
    return (EXIT_SUCCESS);
}

static int OpenParWFO(calculator_t *calc, char *exp, char **ptr)
{
    operators_t oper = MULTIPLY;
    calc_state_t status = SUCCESS;

    UNUSED(exp);

    status = EmptyStack(calc, MULTIPLY);
    
    StackPush(calc->operators_stack, *(void **)&oper);
    
    oper = OPEN_PARENTHESIS;
    
    StackPush(calc->operators_stack, *(void **)&oper);

    ++(*ptr); 
    
    return (status);
}

static int PushMinuS(calculator_t *calc, char *exp, char **ptr)
{
    operators_t oper = MULTIPLY;
    double res = -1.0;
    
    UNUSED(exp);

    StackPush(calc->operators_stack, *(void **)&oper);
   /* printf("hi1\n");*/
    StackPush(calc->digit_stack, *(void **)&res);
  /*  printf("hi2\n");*/

    ++(*ptr);
    
    return (EXIT_SUCCESS);
}

static int OperatorFunc(calculator_t *calc, char *exp, char **ptr)
{
    operators_t index = ToEnum(exp);
    calc_state_t status = SUCCESS;

/*
    DoCalcs(calc, calc->operators_funcs[peek_res][index]);
*/
    status = EmptyStack(calc, index);

    StackPush(calc->operators_stack, *(void **)&index);
/*    printf(": = %d\n", *(void **)&index);*/

    ++(*ptr);

    return (status);
}

static int EmptyStack(calculator_t *calc, operators_t index)
{
    int status = 0;

    while (0 == status &&!StackIsEmpty(calc->operators_stack) && lut_prec[(operators_t)StackPeek(calc->operators_stack)][index])
    {
      /*  printf("inside stack: %d\n", (operators_t)StackPeek(calc->operators_stack));*/
        status = lut_do_donothing_flat[(operators_t)StackPeek(calc->operators_stack)](calc, lut_operators_flat[(operators_t)StackPeek(calc->operators_stack)]);
    }

    return (status);
}

static int ClosedParsWFO (calculator_t *calc, char *exp, char **ptr)
{
    /*operators_t close_pars = CLOSE_PARENTHESIS;*/
    calc_status_t status = 0;

    UNUSED(exp);

/*
    DoCalcs(calc, calc->operators_funcs[peek_res][index]);
*/
    printf("start this\n");

    while (0 == status && OPEN_PARENTHESIS != (operators_t)StackPeek(calc->operators_stack))
    {
       /* printf("run this\n");*/

/*      lut_do_donothing[peek_res][CLOSE_PARENTHESIS](calc, lut_operators[peek_res][CLOSE_PARENTHESIS]);*/
        status = lut_do_donothing_flat[(operators_t)StackPeek(calc->operators_stack)](calc, lut_operators_flat[(operators_t)StackPeek(calc->operators_stack)]);
    }

    StackPop(calc->operators_stack);
    /*StackPush(calc->operators_stack, *(void **)&close_pars);*/
   /* printf("2: = %d\n", *(void **)&close_pars);*/

    ++(*ptr);

    return (status);
}


/*
static int ErrorFunc(calculator_t *calc, char *exp, char **ptr)
{
    UNUSED(calc);
    UNUSED(exp);
    UNUSED(ptr);

    return (EXIT_SUCCESS);
}
*/

static int InitCalc(calculator_t *calculator, size_t stack_size)
{
    double dummy_digit = 0.0;
    operators_t dummy_operation = PLUS;
    /*void *val = NULL;*/

    assert(calculator);
    assert(0 < stack_size);

    calculator->operators_stack = StackCreate(stack_size);

    if (NULL == calculator->operators_stack)
    {
        return (EXIT_FAILURE);
    }

    calculator->digit_stack = StackCreate(stack_size);

    if (NULL == calculator->digit_stack)
    {
        StackDestroy(calculator->operators_stack);
        calculator->operators_stack = NULL;

        return (EXIT_FAILURE);
    }

    calculator->active_state = WAIT_FOR_DIGIT;

    StackPush(calculator->digit_stack, *(void **)&dummy_digit);
    StackPush(calculator->operators_stack, *(void **)&dummy_operation);

   /* printf("hi\n");*/
    /*val = StackPeek(calculator->digit_stack);*/
    /*printf("inside digit stack: %f\n", *((double *)&val));*/
    /*val = StackPeek(calculator->operators_stack);*/
    /*printf("inside operator stack: %d\n", *((int *)&val));*/

    return (EXIT_SUCCESS);
}

void CalcDestroy(calculator_t *calculator)
{
    StackDestroy(calculator->digit_stack);
    StackDestroy(calculator->operators_stack);

    return;
}

int DoCalcs(calculator_t *calc, int (*calc_func)(double num1, double num2, double *res))
{
    void *val1 = NULL;
    void *val2 = NULL;
    int status = 0;

    assert(calc);

    val2 = StackPeek(calc->digit_stack);
   /* printf("val2: %f\n", *(double *)&val2);*/

    StackPop(calc->digit_stack);
    val1 = StackPeek(calc->digit_stack);
   /* printf("val1: %f\n", *(double *)&val1);*/

    StackPop(calc->digit_stack);

    status = calc_func(*(double *)&(val1), *(double *)&(val2), (double *)&(val1));
    /* printf("val1: %f\n", *(double *)&val1);*/
    StackPush(calc->digit_stack, val1);
    StackPop(calc->operators_stack);

    return (status);
}

int DoNotCalc(calculator_t *calc, int (*calc_func_t)(double num1, double num2, double *res))
{
    UNUSED(calc);
    UNUSED(calc_func_t);

    return (0);
}

int Addition(double num1, double num2, double *calc_res)
{
/*     assert(calc_res);
 */    
    *calc_res = num1 + num2;

    return (0);
}

int Subtraction(double num1, double num2, double *calc_res)
{
/*     assert(calc_res);
 */        
    *calc_res = num1 - num2;

    return (0);
}

int Multiplication(double num1, double num2, double *calc_res)
{
/*     assert(calc_res);
 */
    *calc_res = num1 * num2;

    return (0);
}

int Division(double num1, double num2, double *calc_res)
{
/*     assert(calc_res);
 */
    if (0.0 == num2)
    {
        return (1);
    }

    *calc_res = num1 / num2;

    return (0);
}

int Power(double num1, double num2, double *calc_res)
{
/*     assert(calc_res);
 */
    if (0 == num1 && 0 >= num2)
    {
        return (1);
    }

    *calc_res = pow(num1, num2);

    return (0);
}

int DoNothing(double num1, double num2, double *calc_res)
{
    UNUSED(num1);
    UNUSED(num2);
    UNUSED(calc_res);

    return (0);
}

static operators_t ToEnum(char *exp)
{
    static operators_t to_enum_lut[] =
        {
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            OPEN_PARENTHESIS, CLOSE_PARENTHESIS, MULTIPLY,PLUS,    NOTHING, MINUS  , NOTHING, DIVISE,  NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, POWER   ,NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
            NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING};

    return (to_enum_lut[(int)*exp]);
}
