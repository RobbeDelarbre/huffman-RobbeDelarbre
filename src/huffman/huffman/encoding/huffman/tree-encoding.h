#ifndef TREE_ENCODING_H
#define TREE_ENCODING_H
#include "util.h"
#include "data/binary-tree.h"
#include "io/streams.h"
#include "io/binary-io.h"

namespace encoding
{
	namespace huffman
	{
		void encode_tree(const data::Node<Datum>&, u64, io::OutputStream&);
		std::unique_ptr<data::Node<Datum>> decode_tree(u64, io::InputStream&);
	}
}

#endif

