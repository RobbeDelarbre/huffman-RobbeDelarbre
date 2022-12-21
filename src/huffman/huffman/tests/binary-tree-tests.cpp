#ifdef TEST_BUILD

#include "catch.hpp"
#include <data/binary-tree.h>
#include <memory>

namespace
{
	TEST_CASE("Test binary tree constructor")
	{
		std::unique_ptr<data::Leaf<char>> la = std::make_unique<data::Leaf<char>>('a');
		std::unique_ptr<data::Leaf<char>> lb = std::make_unique<data::Leaf<char>>('b');
		std::unique_ptr<data::Leaf<char>> lc = std::make_unique<data::Leaf<char>>('c');
		std::unique_ptr<data::Leaf<char>> ld = std::make_unique<data::Leaf<char>>('d');
		std::unique_ptr<data::Leaf<char>> le = std::make_unique<data::Leaf<char>>('e');

		std::unique_ptr<data::Branch<char>> ba = std::make_unique<data::Branch<char>>(std::move(la), std::move(ld));
		std::unique_ptr<data::Branch<char>> bb = std::make_unique<data::Branch<char>>(std::move(lb), std::move(lc));
		std::unique_ptr<data::Branch<char>> bc = std::make_unique<data::Branch<char>>(std::move(bb), std::move(ba));

		std::unique_ptr<data::Branch<char>> bd = std::make_unique<data::Branch<char>>(std::move(le), std::move(bc));

		CHECK(dynamic_cast<const data::Leaf<char>&>(bd->get_left_child()).get_value() == 'e');

	}
}



#endif