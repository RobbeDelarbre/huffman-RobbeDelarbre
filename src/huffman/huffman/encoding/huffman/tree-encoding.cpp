#include "tree-encoding.h"


namespace encoding
{
	namespace huffman
	{
		void encode_tree(const data::Node<Datum>& root, u64 nbits, io::OutputStream& output)
		{
			if (dynamic_cast<const data::Leaf<Datum>*>(&root) != nullptr)
			{
				output.write(0);
				const auto& leaf = dynamic_cast<const data::Leaf<Datum>*>(&root);
				io::write_bits(leaf->get_value(), nbits, output);
			}
			else if(dynamic_cast<const data::Branch<Datum>*>(&root) != nullptr)
			{
				output.write(1);
				const auto& branch = dynamic_cast<const data::Branch<Datum>*>(&root);
				encode_tree(branch->get_left_child(), nbits, output);
				encode_tree(branch->get_right_child(), nbits, output);
			}
		}

		std::unique_ptr<data::Node<Datum>> decode_tree(u64 nbits, io::InputStream& input)
		{
			if (!input.end_reached())
			{
				auto bit = input.read();
				if (bit == 0)
				{
					Datum data = io::read_bits(nbits, input);
					return std::make_unique<data::Leaf<Datum>>(data);
				}
				else if (bit == 1)
				{
					auto left_child = decode_tree(nbits, input);
					auto right_child = decode_tree(nbits, input);
					return std::make_unique<data::Branch<Datum>>(std::move(left_child), std::move(right_child));
				}
			}
			return nullptr;
		}
	}
}
