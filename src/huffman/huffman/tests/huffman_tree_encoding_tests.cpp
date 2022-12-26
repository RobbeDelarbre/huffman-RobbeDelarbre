#ifdef TEST_BUILD

#include "catch.hpp"
#include <io/memory-buffer.h>
#include <encoding/encoding.h>
#include <encoding/huffman/tree-encoding.h>

namespace
{
	TEST_CASE("encode and decode binary tree")
	{
		const std::vector<uint8_t> data{ 1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1 };

		io::MemoryBuffer<2> input(data);
		auto root = encoding::huffman::decode_tree(8, *input.source()->create_input_stream());

		io::MemoryBuffer<2> output;
		encoding::huffman::encode_tree(*root, 8, *output.destination()->create_output_stream());

		CHECK(data == *output.data());
	}

	TEST_CASE("encode and decode big number")
	{
		int nr = 4506811;

		io::MemoryBuffer<6> buffer1;
		auto input = buffer1.source()->create_input_stream();
		auto output = buffer1.destination()->create_output_stream();

		io::write_bits(nr, 23, *output);

		auto root = encoding::huffman::decode_tree(6, *input);
		encoding::huffman::encode_tree(*root, 6, *output);
		auto result = io::read_bits(23, *input);

		CHECK(result == nr);
	}
}

#endif