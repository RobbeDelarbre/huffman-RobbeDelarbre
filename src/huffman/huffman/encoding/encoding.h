#ifndef ENCODING_H
#define ENCODING_H

#include <io/streams.h>
#include <io/data-endpoints.h>

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


#endif

