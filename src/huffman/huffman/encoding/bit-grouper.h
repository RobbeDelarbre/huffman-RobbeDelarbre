#ifndef BIT_GROUPTER_H
#define BIT_GROUPTER_H

#include "encoding.h"
#include "io/binary-io.h"

namespace encoding
{
	std::shared_ptr<EncodingImplementation> create_bit_grouper_implementation(u64);

	template<unsigned GROUP_SIZE>
	Encoding<2, 1 << GROUP_SIZE> bit_grouper()
	{
		return create_bit_grouper_implementation(GROUP_SIZE);
	}
}

#endif

