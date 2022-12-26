#include "bit-grouper.h"



namespace 
{
	class BitGrouperImplementation : public encoding::EncodingImplementation
	{
		const u64 _group_size;

	public:
		BitGrouperImplementation(u64 group_size) : _group_size(group_size){}

		const void encode(io::InputStream& input, io::OutputStream& output) const override
		{
			while (!input.end_reached())
			{
				u64 result = io::read_bits(_group_size, input);
				output.write(result);
			}
		}

		const void decode(io::InputStream& input, io::OutputStream& output) const override
		{
			while(!input.end_reached())
			{
				io::write_bits(input.read(), _group_size, output);
			}
		}
	};
}

std::shared_ptr<encoding::EncodingImplementation> encoding::create_bit_grouper_implementation(u64 group_size)
{
	return std::make_shared<BitGrouperImplementation>(group_size);
}

