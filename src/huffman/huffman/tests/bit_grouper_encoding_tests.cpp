#ifdef TEST_BUILD

#include "catch.hpp"
#include <io/memory-buffer.h>
#include <encoding/encoding.h>
#include <encoding/bit-grouper.h>

namespace
{
	TEST_CASE("Group 1 byte")
	{
		const std::vector<uint8_t> data{ 0, 1, 0, 0, 1, 1, 0, 1 };
		io::MemoryBuffer<2> input(data); // uint8_t
		io::MemoryBuffer<256> output; // uint8_t
		auto encoding = encoding::bit_grouper<8>();

		encode(input.source(), encoding, output.destination());

		CHECK(1 == output.data()->size());
		CHECK(77 == output.data()->at(0));
	}

	TEST_CASE("Group 1 byte v2")
	{
		const std::vector<uint8_t> data{ 1, 1, 1, 1, 1, 1, 1, 1 };
		io::MemoryBuffer<2> input(data); // uint8_t
		io::MemoryBuffer<256> output; // uint8_t
		auto encoding = encoding::bit_grouper<8>();

		encode(input.source(), encoding, output.destination());

		CHECK(1 == output.data()->size());
		CHECK(255 == output.data()->at(0));
	}

	TEST_CASE("Group 1 byte v3")
	{
		const std::vector<uint8_t> data{ 0, 0, 0, 0, 0, 0, 0, 0 };
		io::MemoryBuffer<2> input(data); // uint8_t
		io::MemoryBuffer<256> output; // uint8_t
		auto encoding = encoding::bit_grouper<8>();

		encode(input.source(), encoding, output.destination());

		CHECK(1 == output.data()->size());
		CHECK(0 == output.data()->at(0));
	}

	TEST_CASE("Group 1 byte with trailing zeros")
	{
		const std::vector<uint8_t> data{ 0, 1, 0, 0, 1, 1 };
		io::MemoryBuffer<2> input(data); // uint8_t
		io::MemoryBuffer<256> output; // uint8_t
		auto encoding = encoding::bit_grouper<8>();

		encode(input.source(), encoding, output.destination());

		CHECK(1 == output.data()->size());
		CHECK(76 == output.data()->at(0));
	}

	TEST_CASE("Bit grouper test")
	{
		const std::vector<uint8_t> data{ 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1 }; // 0, 1, 1 is in the next byte
		io::MemoryBuffer<2> input(data); // uint8_t
		io::MemoryBuffer<256> output; // uint8_t
		auto encoding = encoding::bit_grouper<8>();

		encode(input.source(), encoding, output.destination());

		CHECK(2 == output.data()->size());
		CHECK(77 == output.data()->at(0));
		CHECK(96 == output.data()->at(1));
	}

	// 256 --> |byte splitter| --> 2
	TEST_CASE("Byte splitter test")
	{
		const std::vector<uint8_t> data{ 87, 58, 112 };
		io::MemoryBuffer<256> input(data);
		io::MemoryBuffer<2> output;
		auto encoding = encoding::bit_grouper<8>();

		decode(input.source(), encoding, output.destination());

		const std::vector<uint8_t> expected{ 0,1,0,1,0,1,1,1, 0,0,1,1,1,0,1,0, 0,1,1,1,0,0,0,0 };
		CHECK(expected == *output.data());
	}

	TEST_CASE("Byte splitter & bit grouper test")
	{
		const std::vector<uint8_t> data{ 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1 }; // 0, 1, 1 is in the next byte
		io::MemoryBuffer<2> input(data); // uint8_t
		io::MemoryBuffer<256> output; // uint8_t
		auto encoding = encoding::bit_grouper<8>();

		encode(input.source(), encoding, output.destination());

		CHECK(2 == output.data()->size());
		CHECK(77 == output.data()->at(0));
		CHECK(96 == output.data()->at(1));

		io::MemoryBuffer<256> input2(*output.data()); // uint8_t
		io::MemoryBuffer<2> output2; // uint8_t

		decode(input2.source(), encoding, output2.destination());

		const std::vector<uint8_t> expected{ 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0 };
		CHECK(expected == *output2.data());
	}
}

#endif