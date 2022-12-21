#include "binary-io.h"

namespace io
{
	u64 io::read_bits(u64 nbits, io::InputStream& input)
	{
		u64 result = u64(0);
		for (int i = nbits; i > 0; i--)
		{
			if (!input.end_reached())
			{
				auto x = input.read() << i - 1;
				result = result | x;
			}
		}
		return result;
	}

	void io::write_bits(u64 value, u64 nbits, io::OutputStream& output)
	{
		assert(bits_needed(value) <= nbits);
		for (int i = nbits - 1; i >= 1; i--)
		{
			output.write((value >> i) & 1);
		}
	}

}