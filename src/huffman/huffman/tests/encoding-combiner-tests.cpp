#ifdef TEST_BUILD

#include "catch.hpp"
#include <io/memory-buffer.h>
#include <encoding/encoding.h>
#include <encoding/eof-encoding.h>
#include <encoding/bit-grouper.h>
#include <encoding/encoding-combiner.h>

namespace
{
	TEST_CASE("Combine 2 eof encodings")
	{
		const std::vector<uint8_t> data{ 8, 15, 10 };
		const std::vector<uint8_t> expected{ 8, 15, 10 };

		io::MemoryBuffer<17> buffer6_17_combined(data);
		io::MemoryBuffer<19> buffer7_19_combined;
		io::MemoryBuffer<17> buffer8_17_combined;

		encoding::Encoding<17, 18> eof1 = encoding::eof_encoding<17>();
		encoding::Encoding<18, 19> eof2 = encoding::eof_encoding<18>();
		encoding::Encoding<17, 19> combined = eof1 | eof2;

		encode(buffer6_17_combined.source(), combined, buffer7_19_combined.destination());
		decode(buffer7_19_combined.source(), combined, buffer8_17_combined.destination());

		CHECK(expected == *buffer8_17_combined.data());

		io::MemoryBuffer<17> buffer1_17_encode(data);
		io::MemoryBuffer<18> buffer2_18_encode;
		io::MemoryBuffer<19> buffer3_19_encode;
		io::MemoryBuffer<18> buffer4_18_encode;
		io::MemoryBuffer<17> buffer5_17_encode;

		const auto eofencoding1 = encoding::eof_encoding<17>();
		const auto eofencoding2 = encoding::eof_encoding<18>();

		encode(buffer1_17_encode.source(), eofencoding1, buffer2_18_encode.destination());
		encode(buffer2_18_encode.source(), eofencoding2, buffer3_19_encode.destination());

		decode(buffer3_19_encode.source(), eofencoding2, buffer4_18_encode.destination());
		decode(buffer4_18_encode.source(), eofencoding1, buffer5_17_encode.destination());

		CHECK(expected == *buffer5_17_encode.data());

		CHECK(*buffer8_17_combined.data() == *buffer5_17_encode.data());
	}

	TEST_CASE("Combine eof and bit grouper encodings")
	{
		const std::vector<uint8_t> data{ 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1 };
		const std::vector<uint8_t> expected{ 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0 };

		io::MemoryBuffer<2> buffer6_17_combined(data);
		io::MemoryBuffer<257> buffer7_19_combined;
		io::MemoryBuffer<2> buffer8_17_combined;

		encoding::Encoding<2, 256> grouper = encoding::bit_grouper<8>();
		encoding::Encoding<256, 257> eof = encoding::eof_encoding<256>();
		encoding::Encoding<2, 257> combined = grouper | eof;

		encode(buffer6_17_combined.source(), combined, buffer7_19_combined.destination());

		CHECK(3 == buffer7_19_combined.data()->size());
		CHECK(77 == buffer7_19_combined.data()->at(0));
		CHECK(96 == buffer7_19_combined.data()->at(1));

		decode(buffer7_19_combined.source(), combined, buffer8_17_combined.destination());

		CHECK(expected == *buffer8_17_combined.data());

		io::MemoryBuffer<2> buffer1_17_encode(data);
		io::MemoryBuffer<256> buffer2_18_encode;
		io::MemoryBuffer<257> buffer3_19_encode;
		io::MemoryBuffer<256> buffer4_18_encode;
		io::MemoryBuffer<2> buffer5_17_encode;

		const auto grouperencoding = encoding::bit_grouper<8>();
		const auto eofencoding1 = encoding::eof_encoding<256>();

		encode(buffer1_17_encode.source(), grouperencoding, buffer2_18_encode.destination());
		encode(buffer2_18_encode.source(), eofencoding1, buffer3_19_encode.destination());

		decode(buffer3_19_encode.source(), eofencoding1, buffer4_18_encode.destination());
		decode(buffer4_18_encode.source(), grouperencoding, buffer5_17_encode.destination());

		CHECK(expected == *buffer5_17_encode.data());

		CHECK(*buffer8_17_combined.data() == *buffer5_17_encode.data());
	}
}

#endif