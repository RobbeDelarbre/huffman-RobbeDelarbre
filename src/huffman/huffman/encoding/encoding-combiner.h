#ifndef ENCODING_COMBINER_Hj
#define ENCODING_COMBINER_H

#include "util.h"
#include "encoding.h"
#include "io/memory-buffer.h"

namespace encoding
{
	template<u64 N1, u64 N2, u64 N3>
	class EncodingCombinerImplementation : public encoding::EncodingImplementation
	{
		Encoding<N1, N2> _e1;
		Encoding<N2, N3> _e2;

	public:
		EncodingCombinerImplementation(Encoding<N1, N2> e1, Encoding<N2, N3> e2) : _e1(e1), _e2(e2) {}

		const void encode(io::InputStream& input, io::OutputStream& output) const override
		{
			io::MemoryBuffer<N2> temp;
			auto temp_input = temp.source();
			auto temp_output = temp.destination();

			_e1->encode(input, *temp_output->create_output_stream());
			_e2->encode(*temp_input->create_input_stream(), output);
		}

		const void decode(io::InputStream& input, io::OutputStream& output) const override
		{
			io::MemoryBuffer<N2> temp;
			auto temp_input = temp.source();
			auto temp_output = temp.destination();

			_e2->decode(input, *temp_output->create_output_stream());
			_e1->decode(*temp_input->create_input_stream(), output);
		}
	};

	template<u64 N1, u64 N2, u64 N3>
	Encoding<N1, N3> operator | (Encoding<N1, N2> e1, Encoding<N2, N3> e2)
	{
		auto combiner = std::make_shared<EncodingCombinerImplementation<N1, N2, N3>>(e1, e2);
		return Encoding<N1, N3>(combiner);
	}
}

#endif

