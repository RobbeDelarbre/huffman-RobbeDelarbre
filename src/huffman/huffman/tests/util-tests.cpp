#ifdef TEST_BUILD

#include "catch.hpp"
#include "util.h"


TEST_CASE("Passing test")
{
    REQUIRE(1 == 1);
}

namespace
{
    void check(u64 domain_size, int expected)
    {
        unsigned actual = bits_needed(domain_size);
        CHECK(actual == expected);
    }
    void check_bytes(u64 domain_size, int expected)
    {
        unsigned actual = bytes_needed(domain_size);
        CHECK(actual == expected);
    }
}

#define TEST_BITS(A, EXPECTED) TEST_CASE(#A " should equal " #EXPECTED " bits") { check(A, EXPECTED); }

TEST_BITS(2, 1);
TEST_BITS(3, 2);
TEST_BITS(4, 2);
TEST_BITS(5, 3);
TEST_BITS(6, 3);
TEST_BITS(7, 3);
TEST_BITS(8, 3);
TEST_BITS(9, 4);
TEST_BITS(128, 7);
TEST_BITS(129, 8);
TEST_BITS(255, 8);
TEST_BITS(256, 8);
TEST_BITS(257, 9);
TEST_BITS(1000000, 20);

#define TEST_BYTES(A, EXPECTED) TEST_CASE(#A " should equal " #EXPECTED " bytes" ) { check_bytes(A, EXPECTED); }

TEST_BYTES(2, 1);
TEST_BYTES(128, 1);
TEST_BYTES(129, 1);
TEST_BYTES(255, 1);
TEST_BYTES(256, 1);
TEST_BYTES(257, 2);
TEST_BYTES(1000000, 3);

#endif
