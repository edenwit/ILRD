#include <iostream>

#include "bitarray.hpp"
#include "tools.h"

using namespace ilrd;
using namespace std;

static void TestBitArray();
static void TestCompoundOperators();
static void SetTest();
static void TestGetAndFlipBit();
static void TestCountSetBit();
static void TestToString();
static void TestEqualOperator();

int main()
{
    TestBitArray();
    TestCompoundOperators();
    SetTest();
    TestGetAndFlipBit();
    TestCountSetBit();
    TestEqualOperator();
    TestToString();
    TotalErrors();

    return 0;
}

static void TestBitArray()
{
    BitArray<> b1;
    BitArray<> b2;

    b2 = b1;

    for (int i = 0; i < 8; ++i)
    {
        Valid(!b1[i], "BitArray", __LINE__);
    }

    b1.SetAll();
    
    for (int i = 0; i < 8; ++i)
    {
        Valid(b1[i], "BitArray", __LINE__);
    }

    //BitArray<2> b3(b1); compile error

    BitArray<> b3(b1);

    Valid(b3 == b1, "BitArray", __LINE__);
  
    b2[2] = b3[7];

    Valid(true == b2[2], "BitArray", __LINE__);
    
    b2[2] = b3[7] = b2[6];

    Valid(false == (b2[2] || b3[7]), "BitArray", __LINE__);
    
    return;
}

static void TestCompoundOperators()
{
    const size_t SIZE = 230;

    BitArray<SIZE> b1;
    BitArray<SIZE> b2;
    BitArray<SIZE> b_zero;
    BitArray<SIZE> b_allset;
    b_allset.SetAll();

    for (size_t i = 0; i < SIZE; ++i)
    {
        b1[i] = true;
    }

    b2 |= b1;

    Valid(b_allset == b2, "|=", __LINE__);
    Valid(b_zero != b2, "|=", __LINE__);

    b1.SetAll(false);

    b2 &= b1;

    Valid(b_zero == b2, "&=", __LINE__);

    const size_t idx_arr[] = {5, 8, 12, 31, 87};
    const size_t SIZE_IDXARR = (sizeof(idx_arr) / sizeof(idx_arr[0]));

    for (size_t i = 0; i < SIZE_IDXARR; i++)
    {
        b1.SetBit(idx_arr[i]);
    }

    b2 ^= b1;

    for (size_t i = 0; i < SIZE_IDXARR; i++)
    {
        Valid(true == b2[idx_arr[i]], "^=", __LINE__);
    }

    b2 &= b1;

    for (size_t i = 0; i < SIZE_IDXARR; i++)
    {
        Valid(true == b2[idx_arr[i]], "&=", __LINE__);
    }

    b2 &= b_zero;

    Valid(b_zero == b2, "&=", __LINE__);

    b2 |= b1;

    for (size_t i = 0; i < SIZE_IDXARR; i++)
    {
        Valid(true == b2[idx_arr[i]], "|=", __LINE__);
    }

    return;
}

static void SetTest()
{
    const size_t SIZE = 24;
    BitArray<24> b1;

    b1.SetAll();

    for (size_t i = 0; i < SIZE; ++i)
    {
        Valid(true == b1[i], "SetAll", __LINE__);
    }

    b1.SetAll(false);

    for (size_t i = 0; i < SIZE; ++i)
    {
        Valid(false == b1[i], "SetAll", __LINE__);
    }

    try
    {
        b1.SetBit(SIZE - 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    for (size_t i = 0; i < SIZE - 1; ++i)
    {
        Valid(false == b1[i], "SetBit", __LINE__);
    }

    Valid(true == b1[SIZE - 1], "SetBit", __LINE__);

    try
    {
        b1.SetBit(SIZE - 1, false);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    for (size_t i = 0; i < SIZE; ++i)
    {
        Valid(false == b1[i], "SetBit", __LINE__);
    }

    b1.SetBit(9);
    Valid(true == b1[9], "SetBit", __LINE__);

    b1.SetBit(5);
    Valid(true == b1[5], "SetBit", __LINE__);

    b1.SetBit(2);
    Valid(true == b1[2], "SetBit", __LINE__);

    return;
}

static void TestGetAndFlipBit()
{
    const size_t SIZE = 8;
    BitArray<8> b1;

    bool arr_test[SIZE] = {true, false, true, true, false, false, false, false};

    for (size_t i = 0; i < SIZE; ++i)
    {
        b1[i] = arr_test[i];
    }

    for (size_t i = 0; i < SIZE; ++i)
    {
        try
        {
            Valid(b1.GetBit(i) == arr_test[i], "GetAndFlipBit", __LINE__);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    b1.FlipAll();

    for (size_t i = 0; i < SIZE; ++i)
    {
        Valid(b1.GetBit(i) != arr_test[i], "GetAndFlipBit", __LINE__);
    }

    for (size_t i = 0; i < SIZE; ++i)
    {
        try
        {
            b1.FlipBit(i);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    for (size_t i = 0; i < SIZE; ++i)
    {
        Valid(b1.GetBit(i) == arr_test[i], "GetAndFlipBit", __LINE__);
    }

    return;
}

static void TestCountSetBit()
{
    const size_t SIZE = 16;
    BitArray<16> b1;

    Valid(0 == b1.Count(), "CountSetBit", __LINE__);

    b1.SetAll();

    Valid(SIZE == b1.Count(), "CountSetBit", __LINE__);

    b1.FlipBit(0);

    Valid(SIZE - 1 == b1.Count(), "CountSetBit", __LINE__);

    b1.SetAll(false);

    Valid(0 == b1.Count(), "CountSetBit", __LINE__);

    return;
}

static void TestEqualOperator()
{
    const size_t SIZE = 12;
    BitArray<12> b1;
    BitArray<12> b2;

    Valid(b1 == b2, "operator==", __LINE__);

    b1.SetAll();

    for (size_t i = 0; i < SIZE; ++i)
    {
        b2[i] = true;
    }

    Valid(b1 == b2, "operator==", __LINE__);

    b1.SetBit(SIZE - 1, false);

    Valid(b1 != b2, "operator==", __LINE__);

    return;
}

static void TestToString()
{
    BitArray<16> b1;
    BitArray<5> b2;

    b1.SetAll();
    b1.SetBit(5, false);
    b1.SetBit(13, false);

    std::string res_b1 = "1101111111011111";

    Valid(res_b1 == b1.ToString(), "ToString", __LINE__);

    std::string res_b2 = "00000";

    Valid(res_b2 == b2.ToString(), "ToString", __LINE__);

    b2.SetBit(4);
    b2.FlipBit(0);

    res_b2 = "10001";

    Valid(res_b2 == b2.ToString(), "ToString", __LINE__);

    return;
}