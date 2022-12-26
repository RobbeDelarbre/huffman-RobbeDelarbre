#ifndef EOF_ENCODING_H
#define EOF_ENCODING_H

#include <util.h>
#include <memory>
#include <io/memory-buffer.h>
#include <io/streams.h>
#include "encoding.h"
#include <io/binary-io.h>

namespace encoding
{
	std::shared_ptr<EncodingImplementation> create_eof_implementation(u64);

	template<u64 N>
	Encoding<N, N+1> eof_encoding()
	{
		return create_eof_implementation(N);
	}
}

#endif
