#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include "encoding/encoding.h"
#include <vector>
#include "data/frequency-table.h"
#include <algorithm>
#include "data/binary-tree.h"
#include <cassert>
#include "encoding/huffman/tree-encoding.h"
#include "data/frequency-table.h"

namespace encoding
{
	namespace huffman
	{
		const std::vector<Datum> copy_to_vector(io::InputStream&);
		std::unique_ptr<data::Node<std::pair<Datum, u64>>> build_tree(const data::FrequencyTable<Datum>);
		std::map<Datum, std::vector<Datum>> build_codes(const data::Node<Datum>&);
		Datum weight(std::unique_ptr<data::Node<std::pair<Datum, u64>>>);
		bool weight_comparator(std::unique_ptr<data::Node<std::pair<Datum, u64>>>&, std::unique_ptr<data::Node<std::pair<Datum, u64>>>&);
		std::map<Datum, std::vector<Datum>> build_bits(const data::Node<Datum>&, std::map<Datum, std::vector<Datum>>, std::vector<Datum>);

		std::shared_ptr<EncodingImplementation> create_huffman_implementation(u64);

		template<u64 N>
		Encoding<N, 2> huffman_encoding()
		{
			return create_huffman_implementation(N);
		}

		Datum decode_single_datum(io::InputStream&, data::Node<Datum>&);
		void decode_bits(io::InputStream&, data::Node<Datum>&, io::OutputStream&);
	}
}

#endif

