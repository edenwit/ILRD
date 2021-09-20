#ifndef ILRD_RD102_BITARRAY_HPP
#define ILRD_RD102_BITARRAY_HPP

#include <cstddef>    //size_t
#include <string>     //string
#include <stdexcept>  //std::out_of_range
#include <cstring>    //memcpy
#include <iostream>   // cout
#include <algorithm>  // transform
#include <numeric>    // accumilate
#include <functional> // bit_and

#if __cplusplus <= 199711L
#define noexcept throw()
#else
#define throw(...)
#endif

namespace ilrd
{
static const size_t CHAR_BIT = 8;
static const unsigned char MAX_CHAR_VAL = 255;

template <size_t SIZE = CHAR_BIT>
class BitArray
{
    class BitProxy;

public:
    explicit BitArray();
    ~BitArray();
    BitArray(const BitArray &other);
    inline BitArray &operator=(const BitArray &other);
    inline bool operator[](size_t index) const noexcept;
    inline BitProxy operator[](size_t index) noexcept;
    inline BitArray &operator|=(const BitArray &rhs_) noexcept;
    inline BitArray &operator&=(const BitArray &rhs_) noexcept;
    inline BitArray &operator^=(const BitArray &rhs_) noexcept;
    inline BitArray &operator<<=(size_t shifts) noexcept;
    inline BitArray &operator>>=(size_t shifts) noexcept;
    inline bool operator==(const BitArray &rhs_) const noexcept;
    inline bool operator!=(const BitArray &rhs_) const noexcept;

    inline void SetAll(bool val = true) noexcept;
    inline void SetBit(size_t index, bool val = true) throw(std::out_of_range);
    inline bool GetBit(size_t index) const throw(std::out_of_range);
    inline void FlipAll() noexcept;
    inline void FlipBit(size_t index) throw(std::out_of_range);
    inline size_t Count() const noexcept;
    inline std::string ToString() const; //Strong guarantee:
                                            //if an exception is thrown,
                                            //there are no changes in the bitset.

private:
    static const size_t NUMOFBYTES = (SIZE / CHAR_BIT) + !!(SIZE % CHAR_BIT);
    unsigned char m_bitarray[NUMOFBYTES]; //size_t
    class BitProxy
    {
    public:
        BitProxy(BitArray *bitarray, size_t index);
        inline operator bool() const;
        BitProxy &operator=(bool bit);
        BitProxy &operator=(const BitProxy &other);

    private:
        unsigned char *m_proxy_bitarr;
        size_t m_index;
    };
};

namespace detail
{
    const size_t BYTE_MAX = 0xFF;

    static unsigned char FlipByte(unsigned char byte_to_flip);

    static unsigned char CountBitsOn(size_t sum, unsigned char num);

    static size_t Modulo8(size_t num);
}

// --------------------------------- BitArray --------------------------------

template <size_t SIZE>
BitArray<SIZE>::BitArray()
{
    std::fill(m_bitarray, m_bitarray + NUMOFBYTES, 0);
}

template <size_t SIZE>
BitArray<SIZE>::~BitArray()
{
    //empty
}

template <size_t SIZE>
BitArray<SIZE>::BitArray(const ilrd::BitArray<SIZE> &other)
{
    memcpy(m_bitarray, other.m_bitarray, NUMOFBYTES);
}

template <size_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::operator=(const BitArray<SIZE> &other)
{
    memcpy(m_bitarray, other.m_bitarray, NUMOFBYTES);

    return (*this);
}

template <size_t SIZE>
bool BitArray<SIZE>::operator[](size_t index) const noexcept
{
    return (BitProxy(const_cast<BitArray *>(this), index));
}

template <size_t SIZE>
typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator[](size_t index) noexcept
{
    return (BitProxy(this, index));
}

template <size_t SIZE>
bool BitArray<SIZE>::GetBit(size_t index) const throw(std::out_of_range)
{
    if (index > (SIZE - 1))
    {
        throw(std::out_of_range("index out of range"));
    }
    return ((*this)[index]);
}

template <size_t SIZE>
void BitArray<SIZE>::SetBit(size_t index, bool val) throw(std::out_of_range)
{
    if (index > (SIZE - 1))
    {
        throw(std::out_of_range("index out of range"));
    }

    (*this)[index] = val;

    return;
}

template <size_t SIZE>
void BitArray<SIZE>::SetAll(bool val) noexcept
{
    std::fill(m_bitarray, m_bitarray + NUMOFBYTES, MAX_CHAR_VAL * val);

    return;
}

template <size_t SIZE>
void BitArray<SIZE>::FlipAll() noexcept
{
    std::transform(m_bitarray, m_bitarray + NUMOFBYTES, m_bitarray, detail::FlipByte);

    return;
}

template <size_t SIZE>
void BitArray<SIZE>::FlipBit(size_t index) throw(std::out_of_range)
{
    if (index > (SIZE - 1))
    {
        throw(std::out_of_range("index out of range"));
    }

    bool temp = !((*this)[index]);
    (*this)[index] = temp;

    return;
}

template <size_t SIZE>
bool BitArray<SIZE>::operator==(const BitArray<SIZE> &rhs_) const noexcept
{
    size_t NON_RELEV_BITS = detail::Modulo8(CHAR_BIT - detail::Modulo8(SIZE));
    unsigned char last_byte_mask = 0xFF >> NON_RELEV_BITS;
    
    bool res = std::equal(m_bitarray, m_bitarray + NUMOFBYTES - 1, rhs_.m_bitarray);

    return ((std::equal(m_bitarray, m_bitarray + NUMOFBYTES - 1, rhs_.m_bitarray))
            && ((last_byte_mask & m_bitarray[NUMOFBYTES - 1]) 
            == (last_byte_mask & rhs_.m_bitarray[NUMOFBYTES - 1])));
}

template <size_t SIZE>
bool BitArray<SIZE>::operator!=(const BitArray<SIZE> &rhs_) const noexcept
{
    return (!(*this == rhs_));
}

template <size_t SIZE>
size_t BitArray<SIZE>::Count() const noexcept
{
    unsigned char mask(0xFF);
    mask = ~(mask << (SIZE - (CHAR_BIT * (NUMOFBYTES - 1))));

    size_t counter = std::accumulate(m_bitarray, m_bitarray + NUMOFBYTES - 1,
                                        0, detail::CountBitsOn);

    return (detail::CountBitsOn(counter, (*(m_bitarray + NUMOFBYTES - 1) & mask)));
}

template <size_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::operator|=(const BitArray<SIZE> &rhs_) noexcept
{
    std::transform(m_bitarray, m_bitarray + NUMOFBYTES, rhs_.m_bitarray,
                    m_bitarray, std::bit_or<unsigned char>());

    return (*this);
}
 
template <size_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::operator&=(const BitArray<SIZE> &rhs_) noexcept
{
    std::transform(m_bitarray, m_bitarray + NUMOFBYTES, rhs_.m_bitarray,
                    m_bitarray, std::bit_and<unsigned char>());

    return (*this);
}

template <size_t SIZE>
ilrd::BitArray<SIZE> &BitArray<SIZE>::operator^=(const BitArray<SIZE> &rhs_) noexcept
{
    std::transform(m_bitarray, m_bitarray + NUMOFBYTES, rhs_.m_bitarray,
                    m_bitarray, std::bit_xor<unsigned char>());

    return (*this);
}

template <size_t SIZE>
std::string BitArray<SIZE>::ToString() const
{
    char string[SIZE + 1] = {'\0'};

    for (size_t i = SIZE; 0 < i; --i)
    {
        string[i - 1] = ((*this)[SIZE - i] + '0');
    }

    //std::cout << string << std::endl;

    return (string);
}

namespace detail
{
    static unsigned char FlipByte(unsigned char byte_to_flip)
    {
        return (~byte_to_flip);
    }

    static size_t Modulo8(size_t num)
    {
        return (num & (CHAR_BIT - 1));
    }

    static unsigned char CountBitsOn(size_t sum, unsigned char num)
    {
        const static unsigned char lut_arr_byte_on[] =
            {
                0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2,
                3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
                3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
                6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
                3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3,
                4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
                6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3,
                4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5,
                3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
                6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4,
                4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5,
                6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7,
                6, 7, 7, 8};

        return (sum + lut_arr_byte_on[static_cast<int>(num)]);
    }

} //detail

// -------------------------------- BitProxy -------------------------------

template <size_t SIZE>
BitArray<SIZE>::BitProxy::BitProxy(BitArray *bitarray, size_t index)
    : m_proxy_bitarr(bitarray->m_bitarray + (index / CHAR_BIT)), m_index(detail::Modulo8(index))
{
    //empty
}

template <size_t SIZE>
ilrd::BitArray<SIZE>::BitProxy::operator bool() const
{
    return (*m_proxy_bitarr & (1 << m_index));
}

template <size_t SIZE>
typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(bool bit)
{
    *m_proxy_bitarr = (*m_proxy_bitarr & (~(1 << m_index))) | (bit << m_index);

    return (*this);
}

template <size_t SIZE>
typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(const BitProxy &other) 
{
    bool bit = (*(other.m_proxy_bitarr)) & (1 << other.m_index);
    return (*this = bit);
}

} //ilrd

#ifdef noexcept
#undef noexcept
#else
#undef throw
#endif

#endif /* ILRD_RD102_BITARRAY_HPP */