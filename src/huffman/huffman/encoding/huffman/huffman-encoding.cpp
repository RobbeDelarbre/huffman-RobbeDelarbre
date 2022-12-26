#include "huffman-encoding.h"



namespace 
{
	class HuffmanEncodingImplementation : public encoding::EncodingImplementation
	{
		const u64 _domain_size;

		HuffmanEncodingImplementation(u64 domain_size) : _domain_size(domain_size) {}

		const void encode(io::InputStream& input, io::OutputStream& output) const override
		{
			const std::vector<Datum> in = encoding::huffman::copy_to_vector(input);

			const data::FrequencyTable<Datum> freq_table = data::count_frequencies<data::FrequencyTable<Datum>>(in);

			const std::unique_ptr <data::Node<std::pair<Datum, u64>>> tree = std::move(encoding::huffman::build_tree(freq_table));

			std::unique_ptr<data::Node<Datum>> node = data::map<std::pair<Datum, u64>, Datum>(*tree, [](const std::pair<Datum, u64>& leaf) { return leaf.first; });

			auto codes = encoding::huffman::build_codes(*node);

			auto nbits = bits_needed(_domain_size);
			encoding::huffman::encode_tree(*node, nbits, output);

			for (Datum dat : in)
			{
				auto bits = codes[dat];
				for (auto bit :bits)
				{
					output.write(bit);
				}
			}
		}

		const void decode(io::InputStream& input, io::OutputStream& output) const override
		{
			auto nbits = bits_needed(_domain_size);
			std::unique_ptr<data::Node<Datum>> tree = encoding::huffman::decode_tree(nbits, input);
			encoding::huffman::decode_bits(input, *tree, output);
		}
	};


}

namespace encoding
{
	namespace huffman
	{
		const std::vector<Datum> copy_to_vector(io::InputStream& input)
		{
			std::vector<Datum> data;
			while (!input.end_reached())
			{
				data.push_back(input.read());
			}
			return data;
		}

		std::unique_ptr<data::Node<std::pair<Datum, u64>>> build_tree(const data::FrequencyTable<Datum> freq_table)
		{
			std::vector<std::unique_ptr<data::Node<std::pair<Datum, u64>>>> nodes;
			auto values = freq_table.values();

			for (Datum value : values)
			{
				auto freq = freq_table[value];
				std::pair<Datum, u64> pair = std::pair<Datum, u64>(value, freq);
				nodes.push_back(std::make_unique<data::Leaf<std::pair<Datum, u64>>>(pair));
			}

			while (nodes.size() > 1)
			{
				std::sort(nodes.begin(), nodes.end(), weight_comparator);
				auto left = std::move(nodes.back());
				nodes.pop_back();
				auto right = std::move(nodes.back());
				nodes.pop_back();

				auto branch = std::make_unique<data::Branch<std::pair<Datum, u64>>>(std::move(left), std::move(right));
				nodes.push_back(std::move(branch));
			}
			return std::move(nodes.front());
		}

		Datum weight(const data::Node<std::pair<Datum, u64>>& node)
		{
			if (dynamic_cast<const data::Leaf<std::pair<Datum, u64>>*>(&node) != nullptr)
			{
				return dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(node).get_value().second;
			}
			if (dynamic_cast<const data::Branch<std::pair<Datum, u64>>*>(&node) != nullptr)
			{
				auto& branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(node);
				return (weight(branch.get_left_child()) + weight(branch.get_right_child()));
			}
			return 0;
		}

		bool weight_comparator(std::unique_ptr<data::Node<std::pair<Datum, u64>>>& a, std::unique_ptr<data::Node<std::pair<Datum, u64>>>& b)
		{
			return weight(*a) > weight(*b);
		}

		std::map<Datum, std::vector<Datum>> build_codes(const data::Node<Datum>& huffman_tree)
		{
			std::map<Datum, std::vector<Datum>> codes;
			std::vector<Datum> bits;
			codes = build_bits(huffman_tree, codes, bits);
			return codes;
		}

		std::map<Datum, std::vector<Datum>> build_bits(const data::Node<Datum>& root, std::map<Datum, std::vector<Datum>> codes, std::vector<Datum> bits)
		{
			assert(&root != nullptr);
			if(dynamic_cast<const data::Leaf<Datum>*>(&root) != nullptr)
			{
				auto& leaf = dynamic_cast<const data::Leaf<Datum>&>(root);
				Datum value = leaf.get_value();
				codes.insert(std::pair<Datum, std::vector<Datum>>(value, bits));
			}
			else if(dynamic_cast<const data::Branch<Datum>*>(&root) != nullptr)
			{
				auto& branch = dynamic_cast<const data::Branch<Datum>&>(root); 
				bits.push_back(0);
				codes = build_bits(branch.get_left_child(), codes, bits);
				bits.pop_back();
				bits.push_back(1);
				codes = build_bits(branch.get_right_child(), codes, bits);
			}
			return codes;
		}

		Datum decode_single_datum(io::InputStream& input, data::Node<Datum>& tree)
		{
			if (dynamic_cast<const data::Leaf<Datum>*>(&tree) != nullptr)
			{
				auto leaf = dynamic_cast<const data::Leaf<Datum>*>(&tree);
				return leaf->get_value();
			}
			if (dynamic_cast<const data::Branch<Datum>*>(&tree) != nullptr)
			{
				auto branch = dynamic_cast<data::Branch<Datum>*>(&tree);
				while (!input.end_reached())
				{
					Datum data = input.read();
					if(data == 0)
					{
						return decode_single_datum(input, branch->get_left_child());
					}
					if (data == 1)
					{
						return decode_single_datum(input, branch->get_right_child());
					}
				}
			}
			return 0;
		}

		void decode_bits(io::InputStream& input, data::Node<Datum>& tree, io::OutputStream& output)
		{
			while(!input.end_reached())
			{
				Datum data = decode_single_datum(input, tree);
				output.write(data);
			}
		}

	}
}


