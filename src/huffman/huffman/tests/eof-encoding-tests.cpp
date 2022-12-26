#ifdef TEST_BUILD

#include "catch.hpp"
#include <io/streams.h>
#include <io/memory-buffer.h>
#include <encoding/encoding.h>
#include <encoding/eof-encoding.h>
#include <util.h>

namespace
{
	TEST_CASE("check EOF encoding")
	{
		const std::vector<uint8_t> data{ 8 };
		io::MemoryBuffer<17> buffer1_17_encode(data);
		io::MemoryBuffer<18> buffer2_18_encode;

		const auto eofencoding = encoding::eof_encoding<17>();
		encode(buffer1_17_encode.source(), eofencoding, buffer2_18_encode.destination());

		CHECK(buffer1_17_encode.data()->size() == buffer2_18_encode.data()->size() - 1);
	}

	TEST_CASE("check EOF encoding and decoding")
	{
		const std::vector<uint8_t> data{ 8, 15, 10 };
		io::MemoryBuffer<17> buffer1_17_encode(data);
		io::MemoryBuffer<18> buffer2_18_encode;
		io::MemoryBuffer<17> buffer3_17_encode;

		const auto eofencoding = encoding::eof_encoding<17>();
		encode(buffer1_17_encode.source(), eofencoding, buffer2_18_encode.destination());

		CHECK(buffer1_17_encode.data()->size() == buffer2_18_encode.data()->size() - 1);

		decode(buffer2_18_encode.source(), eofencoding, buffer3_17_encode.destination());

		const std::vector<uint8_t> expected{ 8, 15, 10 };
		CHECK(expected == *buffer3_17_encode.data());
	}
}

#endif