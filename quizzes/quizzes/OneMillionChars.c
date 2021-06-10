#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */
#include <string.h>

#define CHARS (256)
#define MAX2(X, Y) ((X) > (Y) ? (X) : (Y))

void GetChar(char ch);
size_t CountBitsInLong(unsigned long num);

static void GetCharTest();
static void CountBitsInLongTest();

int main()
{
    GetCharTest();
    CountBitsInLongTest();

    return (0);
}

void GetChar(char ch)
{
    static size_t lut[CHARS] = {0};
    static int init = 0;
    size_t max = 0;
    size_t i = 0;

    if (0 == init)
    {
        for (i = 0; i < CHARS; ++i)
        {
            lut[i] = 0;
        }

        init = 1;
    }

    ++lut[(int)ch];

    if ('0' == ch)
    {
        for (i = 0; i < CHARS; ++i)
        {
            max = MAX2(max, lut[i]);
        }

        printf("Max accurances: %ld\n", max);

        init = 0;
    }

    return;
}

static void GetCharTest()
{
    char *str = "g1d564g113206t3534t333352s1g3231r56y4485464w1fd1035bv0dhw0t5636grje0f5631t2df1gc.2s135217g2t";
    size_t arr_size = strlen(str);
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        /*printf("char sent: '%c'\n", *(str + i));*/

        GetChar(str[i]);
    }

    return;
}

size_t CountBitsInLong(unsigned long num)
{
    size_t counter = 0;

    while (0 != num)
    {
        num = num & (num - 1);
        ++counter;
    }

    return (counter);
}

static void CountBitsInLongTest()
{
    unsigned long arr[] = {0x0000000000000000, 0x0000000000000001, 0x0000000000000010, 0x0000200000000000, 0xF000000000000000,
                           0x000F000000000000, 0x00000C0000000000, 0x00000000DD000000, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFF1F};
    size_t exp_arr[] = {0, 1, 1, 1, 4,
                        4, 2, 6, 64, 61};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        if (CountBitsInLong(arr[i]) != exp_arr[i])
        {
            printf("Iter #%ld: Fail. Actual: %ld, expacted: %ld\n", i + 1, CountBitsInLong(arr[i]), exp_arr[i]);
        }
    }

    return;
}