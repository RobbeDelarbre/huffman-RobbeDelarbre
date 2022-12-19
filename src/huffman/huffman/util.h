#ifndef UTIL_H
#define UTIL_H
#include <cstdint>

typedef uint64_t u64;
typedef uint64_t Datum;

constexpr u64 bits_needed(u64 domain_size)
{
    u64 count = 0;
    domain_size -= 1;

    while (domain_size != 0)
    {
        domain_size >>= 1;
        count++;
    }
    return count;
}

constexpr u64 bytes_needed(u64 domain_size)
{
    u64 bits = bits_needed(domain_size);
    if (bits % 8 == 0)
    {
        return bits / 8;
    }
    return bits / 8 + 1;
}

template<u64 NBITS> struct SelectIntegerTypeByBytes;

template<> struct SelectIntegerTypeByBytes<1> { typedef uint8_t type; };
template<> struct SelectIntegerTypeByBytes<2> { typedef uint16_t type; };
template<> struct SelectIntegerTypeByBytes<3> { typedef uint32_t type; };
template<> struct SelectIntegerTypeByBytes<4> { typedef uint32_t type; };
template<> struct SelectIntegerTypeByBytes<5> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<6> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<7> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<8> { typedef uint64_t type; };

template<u64 DOMAIN_SIZE> struct SelectIntegerTypeByDomainSize
{
    typedef typename SelectIntegerTypeByBytes<bytes_needed(DOMAIN_SIZE)>::type type;
};

#endif
