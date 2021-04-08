#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "bit_array.h"

#define CHAR_BIT 8
#define BITS_IN_ARR (sizeof(bit_arr_t) * CHAR_BIT)

static void TestSetOn();
static void TestSetOff();
static void TestSetAll();
static void TestResetAll();
static void TestSetBit();
static void TestGetVal();
static void TestFlipBit();
static void TestRotR();
static void TestRotL();
static void TestMirror();
static void TestCountOn();
static void TestCountOff();
static void TestToString();
static void TestCountBitsLut();
static void TestMirrorLut();


int main()
{
	TestSetOn();
	TestSetOff();
	TestSetAll();
	TestResetAll();
	TestSetBit();
	TestGetVal();
	TestToString();
	TestFlipBit();
	TestRotR();
	TestRotL();
	TestMirror();
	TestCountOn();
	TestCountOff();
	TestCountBitsLut();
	TestMirrorLut();
	
	return 0;
}

static void TestSetOn()
{
    bit_arr_t nums_test = 0x0F0F0F0F0F0F0F0F;
    size_t indexes[] = {0, 63, 6, 1};
    bit_arr_t nums_exp[] = {0x0F0F0F0F0F0F0F0F, 0x8F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F4F, 0x0F0F0F0F0F0F0F0F};
    size_t arr_size = sizeof(indexes) / sizeof(indexes[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrSetOn(nums_test, indexes[i]) != nums_exp[i])
    	{
     		printf("SetOn Failed: with attempt %ld: %ld - %ld - %lx.\n", i, nums_test, nums_exp[i], BitArrSetOn(nums_test, indexes[i]));
	    }
	}

    return;
}

static void TestSetOff()
{
    bit_arr_t nums_test = 0x0F0F0F0F0F0F0F0F;
    size_t indexes[] = {0, 63, 6, 1};
    bit_arr_t nums_exp[] = {0x0F0F0F0F0F0F0F0E, 0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0D};
    size_t arr_size = sizeof(indexes) / sizeof(indexes[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrSetOff(nums_test, indexes[i]) != nums_exp[i])
    	{
     		printf("SetOff Failed: with attempt %ld: %ld - %ld - %lx.\n", i, nums_test, nums_exp[i], BitArrSetOff(nums_test, indexes[i]));
	    }
	}

    return;
}

static void TestSetAll()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000};
    bit_arr_t nums_exp = 0xFFFFFFFFFFFFFFFF;
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrSetAll(nums_test[i]) != nums_exp)
    	{
     		printf("SetAll Failed: with attempt %ld: %ld - %ld - %lx.\n", i, nums_test[i], nums_exp, BitArrSetAll(nums_test[i]));
	    }
	}

    return;
}


static void TestResetAll()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000};
    bit_arr_t nums_exp = 0x0000000000000000;
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrResetAll(nums_test[i]) != nums_exp)
    	{
     		printf("ResetAll Failed: with attempt %ld: %ld - %ld - %lx.\n", i, nums_test[i], nums_exp, BitArrResetAll(nums_test[i]));
	    }
	}

    return;
}


static void TestSetBit()
{
    bit_arr_t nums_test = 0x0F0F0F0F0F0F0F0F;
    size_t indexes[] = {0, 0, 63, 63, 6, 6, 1, 1};
    size_t values[] = {0, 1, 0, 1, 0, 1, 0, 1};
    bit_arr_t nums_exp[] = {0x0F0F0F0F0F0F0F0E, 0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F, 0x8F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F4F, 0x0F0F0F0F0F0F0F0D, 0x0F0F0F0F0F0F0F0F};
    size_t arr_size = sizeof(indexes) / sizeof(indexes[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrSetBit(nums_test, indexes[i], values[i]) != nums_exp[i])
    	{
     		printf("SetBit Failed: with attempt %ld: send: %lx - exp: %lx - actual: %lx.\n", i, nums_test, nums_exp[i], BitArrSetBit(nums_test, indexes[i], values[i]));
	    }
	}

    return;
}

static void TestGetVal()
{
    bit_arr_t nums_test = 0x0F0F0F0F0F0F0F0F;
    size_t indexes[] = {0, 63, 6, 1};
    int nums_exp[] = {1, 0, 0, 1};
    size_t arr_size = sizeof(indexes) / sizeof(indexes[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrGetVal(nums_test, indexes[i]) != nums_exp[i])
    	{
     		printf("GetVal Failed: with attempt %ld: send: %lx - exp: %d - actual: %d.\n", i, nums_test, nums_exp[i], BitArrGetVal(nums_test, indexes[i]));
	    }
	}

    return;
}

static void TestToString()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000};
    char *strings_exp[] = {
    "0000111100001111000011110000111100001111000011110000111100001111",
    "1111000011110000111100001111000011110000111100001111000011110000",
    "1111111111111111111111111111111111111111111111111111111111111111",
    "0000000000000000000000000000000000000000000000000000000000000000"};
    char string_test[BITS_IN_ARR + 1] = {0};
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (0 != strcmp(BitArrToString(nums_test[i], string_test), strings_exp[i]))
    	{
     		printf("\nToString Failed: with attempt %ld: \nsend: %lx - \nexp:    %s - \nactual: %s.\n", i, nums_test[i], strings_exp[i], BitArrToString(nums_test[i], string_test));
	    }
	}

    return;
}

static void TestFlipBit()
{
    bit_arr_t nums_test = 0x0F0F0F0F0F0F0F0F;
    size_t indexes[] = {0, 63, 6, 1};
    bit_arr_t nums_exp[] = {0x0F0F0F0F0F0F0F0E, 0x8F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F4F, 0x0F0F0F0F0F0F0F0D};
    size_t arr_size = sizeof(indexes) / sizeof(indexes[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrFlipBit(nums_test, indexes[i]) != nums_exp[i])
    	{
     		printf("FlipBit Failed: with attempt %ld: %ld - %ld - %lx.\n", i, nums_test, nums_exp[i], BitArrFlipBit(nums_test, indexes[i]));
	    }
	}

    return;
}

static void TestRotR()
{
    bit_arr_t nums_test = 0x0F0F0F0F0F0F0F0F;
    size_t steps[] = {0, 63, 6, 1};
    bit_arr_t nums_exp[] = {0x0F0F0F0F0F0F0F0F, 0x1E1E1E1E1E1E1E1E, 0x3C3C3C3C3C3C3C3C, 0x8787878787878787};
    size_t arr_size = sizeof(steps) / sizeof(steps[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrRotR(nums_test, steps[i]) != nums_exp[i])
    	{
     		printf("RotR Failed: with attempt %ld: %ld - %ld - %lx.\n", i, nums_test, nums_exp[i], BitArrRotR(nums_test, steps[i]));
	    }
	}

    return;
}

static void TestRotL()
{
    bit_arr_t nums_test = 0x0F0F0F0F0F0F0F0F;
    size_t steps[] = {0, 63, 6, 1};
    bit_arr_t nums_exp[] = {0x0F0F0F0F0F0F0F0F, 0x8787878787878787, 0xC3C3C3C3C3C3C3C3, 0x1E1E1E1E1E1E1E1E};
    size_t arr_size = sizeof(steps) / sizeof(steps[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrRotL(nums_test, steps[i]) != nums_exp[i])
    	{
     		printf("RotL Failed: with attempt %ld: %ld - %ld - %lx.\n", i, nums_test, nums_exp[i], BitArrRotL(nums_test, steps[i]));
	    }
	}

    return;
}

static void TestMirror()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFF1F, 0x0100000000000000};
    bit_arr_t  nums_exp[] = {0xF0F0F0F0F0F0F0F0, 0x0F0F0F0F0F0F0F0F, 0xF8FFFFFFFFFFFFFF, 0x0000000000000080};
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrMirror(nums_test[i]) != nums_exp[i])
    	{
     		printf("Mirror Failed: with attempt %ld: \nsend:   %lx - \nexp:    %lx - \nactual: %lx.\n", i, nums_test[i], nums_exp[i], BitArrMirror(nums_test[i]));
	    }
	}

    return;
}


static void TestCountOn()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFF1F, 0x0100000000000000, 0x0000000000000000};
    size_t  nums_exp[] = {32, 32, 61, 1, 0};
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrCountOn(nums_test[i]) != nums_exp[i])
    	{
     		printf("CountOn Failed: with attempt %ld: \nsend:   %lx - \nexp:    %ld - \nactual: %ld.\n", i, nums_test[i], nums_exp[i], BitArrCountOn(nums_test[i]));
	    }
	}

    return;
}

static void TestCountOff()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFF1F, 0x0100000000000000, 0x0000000000000000};
    size_t  nums_exp[] = {32, 32, 3, 63, 64};
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrCountOff(nums_test[i]) != nums_exp[i])
    	{
     		printf("CountOff Failed: with attempt %ld: \nsend:   %lx - \nexp:    %ld - \nactual: %ld.\n", i, nums_test[i], nums_exp[i], BitArrCountOff(nums_test[i]));
	    }
	}

    return;
}

static void TestCountBitsLut()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFF1F, 0x0100000000000000, 0x0000000000000000};
    size_t  nums_exp[] = {32, 32, 61, 1, 0};
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (CountBitsNoLoop(nums_test[i]) != nums_exp[i])
    	{
     		printf("CountBitsNoLoop Failed: with attempt %ld: \nsend:   %lx - \nexp:    %ld - \nactual: %ld.\n", i, nums_test[i], nums_exp[i], CountBitsNoLoop(nums_test[i]));
	    }
	}

    return;
}

static void TestMirrorLut()
{
    bit_arr_t nums_test[] = {0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0, 0xFFFFFFFFFFFFFF1F, 0x0100000000000000};
    bit_arr_t  nums_exp[] = {0xF0F0F0F0F0F0F0F0, 0x0F0F0F0F0F0F0F0F, 0xF8FFFFFFFFFFFFFF, 0x0000000000000080};
    size_t arr_size = sizeof(nums_test) / sizeof(nums_test[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
	    if (BitArrMirrorLut(nums_test[i]) != nums_exp[i])
    	{
     		printf("BitArrMirrorLut Failed: with attempt %ld: \nsend:   %lx - \nexp:    %lx - \nactual: %lx.\n", i, nums_test[i], nums_exp[i], BitArrMirrorLut(nums_test[i]));
	    }
	}

    return;
}

