#include "eof-encoding.h"

namespace
{
	class EofEncodingImplementation : public encoding::EncodingImplementation
	{
		const u64 _domain_size;

	public:
		EofEncodingImplementation(u64 domain_size) : _domain_size(domain_size) {}

		const void encode(io::InputStream& input, io::OutputStream& output) const override
		{
			while (!input.end_reached())
			{
				output.write(input.read());
			}
			output.write(_domain_size);
		}

		const void decode(io::InputStream& input, io::OutputStream& output) const override
		{
			while (!input.end_reached())
			{
				auto result = input.read();
				if (result != _domain_size)
				{
					output.write(result);
				}
			}
		}
	};
}

std::shared_ptr<encoding::EncodingImplementation> encoding::create_eof_implementation(u64 domain_size)
{
	return std::make_shared<EofEncodingImplementation>(domain_size);
}