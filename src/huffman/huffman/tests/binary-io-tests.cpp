#ifdef TEST_BUILD

#include "catch.hpp"
#include "io/binary-io.h"
#include <util.h>
#include <memory>
#include <vector>
#include <io/streams.h>
#include <io/memory-buffer.h>


namespace 
{
    void check(u64 n, unsigned nbits)
    {
        io::MemoryBuffer<2> buffer;
        auto input = buffer.source()->create_input_stream();
        auto output = buffer.destination()->create_output_stream();
        io::write_bits(n, nbits, *output);
        auto result = io::read_bits(nbits, *input);

        REQUIRE(n == result);
    }


    TEST_CASE("Test binary-io1")
    {
        check(36, 6);
    }

    TEST_CASE("Test binary-io2")
    {
        check(1, 1);
    }

    TEST_CASE("Test binary-io3")
    {
        check(10, 4);
    }

    TEST_CASE("Test binary-io4")
    {
        check(10, 10);
    }

    TEST_CASE("Test binary-io5")
    {
        check(357478, 19);
    }
}
#endif
