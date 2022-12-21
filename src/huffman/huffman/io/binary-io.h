#ifndef BINARY_IO_H
#define BINARY_IO_H

#include <io/memory-buffer.h>
#include <io/streams.h>
#include <iostream>

namespace io
{
	u64 read_bits(u64, InputStream&);
	void write_bits(u64, u64, OutputStream&);

}

#endif

