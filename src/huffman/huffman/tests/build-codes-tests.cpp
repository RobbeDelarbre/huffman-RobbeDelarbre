#ifdef TEST_BUILD

#include "catch.hpp"
#include <io/streams.h>
#include <io/memory-buffer.h>
#include <encoding/encoding.h>
#include <encoding/eof-encoding.h>
#include <encoding/bit-grouper.h>
#include <encoding/encoding-combiner.h>
#include <encoding/huffman/tree-encoding.h>
#include <encoding/huffman/huffman-encoding.h>
#include <util.h>

namespace
{
	TEST_CASE("check build_codes")
	{
		auto freq_table = data::FrequencyTable<Datum>();
		freq_table.increment(1);
		freq_table.increment(1);
		freq_table.increment(2);
		freq_table.increment(3);
		freq_table.increment(3);
		freq_table.increment(3);
		freq_table.increment(3);
		freq_table.increment(4);
		freq_table.increment(4);
		freq_table.increment(4);
		freq_table.increment(4);
		freq_table.increment(4);

		const std::unique_ptr<data::Node<std::pair<Datum, u64>>>& root = encoding::huffman::build_tree(freq_table);

		auto codes = encoding::huffman::build_codes(*root);
		for (auto const& pair : codes)
		{
			std::string s = "";
			for (auto const& datum : pair.second)
			{
				s.append(std::to_string(datum));

			}
			std::cout << "{" << pair.first << ": " << s << "}\n";
		}

		REQUIRE(codes.size() == 4);
	}
}

#endif