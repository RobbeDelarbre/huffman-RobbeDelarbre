#ifndef ENCODING_H
#define ENCODING_H

#include <io/streams.h>
#include <io/data-endpoints.h>
#include <util.h>
#include <memory>

namespace encoding
{
	class EncodingImplementation
	{
	public:
		virtual ~EncodingImplementation() {};
		virtual const void encode(io::InputStream&, io::OutputStream&) const = 0;
		virtual const void decode(io::InputStream&, io::OutputStream&) const = 0;
	};

	template<u64 IN, u64 OUT>
	class Encoding
	{
		std::shared_ptr<EncodingImplementation> _encode_imp;
	public:
		Encoding(std::shared_ptr<EncodingImplementation> encode_imp) : _encode_imp(encode_imp) {}

		EncodingImplementation* operator->()
		{
			return _encode_imp.get();
		}

		const EncodingImplementation* operator->() const
		{
			return _encode_imp.get();
		}
	};
}

template<u64 IN, u64 OUT>
void encode(io::DataSource<IN> source, encoding::Encoding<IN, OUT> encoding, io::DataDestination<OUT> destination)
{
	encoding->encode(*source->create_input_stream(), *destination->create_output_stream());
}

template<u64 IN, u64 OUT>
void decode(io::DataSource<IN> source, encoding::Encoding<IN,OUT> encoding, io::DataDestination<OUT> destination)
{
	encoding->encode(*source->create_input_stream(), *destination->create_output_stream());
}


#endif

