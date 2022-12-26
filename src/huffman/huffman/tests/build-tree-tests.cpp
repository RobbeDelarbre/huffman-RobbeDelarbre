#ifdef TEST_BUILD

#include "catch.hpp"
#include <encoding/huffman/huffman-encoding.h>
#include <util.h>

namespace
{
	TEST_CASE("tree-builder: root + 1 level different weights")
	{
		//create frequency table
		data::FrequencyTable<Datum> table = data::FrequencyTable<Datum>();
		table.increment(1);
		table.increment(1);
		table.increment(2);
		table.increment(2);
		table.increment(2);

		//create tree
		auto tree = std::move(encoding::huffman::build_tree(table));

		//extract children from tree
		auto& root_branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(*tree);

		auto& left_child = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(root_branch.get_left_child());
		auto& right_child = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(root_branch.get_right_child());


		//check if data in children is correct
		CHECK(left_child.get_value().first == 1);
		CHECK(left_child.get_value().second == 2);
		CHECK(right_child.get_value().first == 2);
		CHECK(right_child.get_value().second == 3);
	}

	TEST_CASE("tree-builder: root + 1 level same weights")
	{
		//create frequency table
		data::FrequencyTable<Datum> table = data::FrequencyTable<Datum>();
		table.increment(1);
		table.increment(1);
		table.increment(2);
		table.increment(2);

		//create tree
		auto tree = std::move(encoding::huffman::build_tree(table));

		//extract children from tree
		auto& root_branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(*tree);

		auto& left_child = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(root_branch.get_left_child());
		auto& right_child = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(root_branch.get_right_child());


		//check if data in children is correct
		CHECK(left_child.get_value().first == 2);
		CHECK(left_child.get_value().second == 2);
		CHECK(right_child.get_value().first == 1);
		CHECK(right_child.get_value().second == 2);
	}

	TEST_CASE("tree-builder: root + 2 level (3 leaves)")
	{
		//create frequency table
		data::FrequencyTable<Datum> table = data::FrequencyTable<Datum>();
		table.increment(1);
		table.increment(1);
		table.increment(2);
		table.increment(2);
		table.increment(2);
		table.increment(2);
		table.increment(3);
		table.increment(3);
		table.increment(3);

		//create tree
		auto tree = std::move(encoding::huffman::build_tree(table));

		//extract children from tree
		auto& root_branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(*tree);

		auto& left_child = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(root_branch.get_left_child());
		auto& right_branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(root_branch.get_right_child());

		auto& RBL = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(right_branch.get_left_child());
		auto& RBR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(right_branch.get_right_child());

		//check if data in children is correct
		CHECK(left_child.get_value().first == 2);
		CHECK(left_child.get_value().second == 4);
		CHECK(RBL.get_value().first == 1);
		CHECK(RBL.get_value().second == 2);
		CHECK(RBR.get_value().first == 3);
		CHECK(RBR.get_value().second == 3);
	}

	TEST_CASE("tree-builder: root + 2 level (4 leaves)")
	{
		//create frequency table
		data::FrequencyTable<Datum> table = data::FrequencyTable<Datum>();
		table.increment(1);
		table.increment(1);
		table.increment(2);
		table.increment(2);
		table.increment(2);
		table.increment(2);
		table.increment(2);
		table.increment(3);
		table.increment(3);
		table.increment(3);
		table.increment(3);
		table.increment(4);

		//create tree
		auto tree = std::move(encoding::huffman::build_tree(table));

		//extract children from tree
		auto& root_branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(*tree);

		auto& left_leaf = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(root_branch.get_left_child());
		auto& right_branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(root_branch.get_right_child());

		auto& RBL = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(right_branch.get_left_child());
		auto& RBR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(right_branch.get_right_child());

		auto& RBLL = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(RBL.get_left_child());
		auto& RBLR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(RBL.get_right_child());

		//check if data in children is correct
		CHECK(left_leaf.get_value().first == 2);
		CHECK(left_leaf.get_value().second == 5);
		CHECK(RBR.get_value().first == 3);
		CHECK(RBR.get_value().second == 4);
		CHECK(RBLL.get_value().first == 4);
		CHECK(RBLL.get_value().second == 1);
		CHECK(RBLR.get_value().first == 1);
		CHECK(RBLR.get_value().second == 2);
	}

	TEST_CASE("tree-builder: root + 3 levels (5 leaves)")
	{
		//create frequency table
		data::FrequencyTable<Datum> table = data::FrequencyTable<Datum>();
		table.increment(1);
		table.increment(2);
		table.increment(2);
		table.increment(3);
		table.increment(3);
		table.increment(3);
		table.increment(3);
		table.increment(4);
		table.increment(4);
		table.increment(4);
		table.increment(4);
		table.increment(4);
		table.increment(5);
		table.increment(5);
		table.increment(5);
		table.increment(5);
		table.increment(5);
		table.increment(5);

		//create tree
		auto tree = std::move(encoding::huffman::build_tree(table));

		//extract children from tree
		//niveau 1
		auto& branch_root = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(*tree);

		//niveau 2
		auto& TBL = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(branch_root.get_left_child());
		auto& TBR = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(branch_root.get_right_child());

		//niveau 3
		auto& MB = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(TBL.get_left_child());
		auto& MLR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(TBL.get_right_child());
		auto& MRL = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(TBR.get_left_child());
		auto& MRR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(TBR.get_right_child());

		//niveau 4
		auto& BLL = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(MB.get_left_child());
		auto& BLR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(MB.get_right_child());

		//check if data in children is correct
		CHECK(BLL.get_value().first == 1);
		CHECK(BLL.get_value().second == 1);
		CHECK(BLR.get_value().first == 2);
		CHECK(BLR.get_value().second == 2);
		CHECK(MLR.get_value().first == 3);
		CHECK(MLR.get_value().second == 4);
		CHECK(MRL.get_value().first == 4);
		CHECK(MRL.get_value().second == 5);
		CHECK(MRR.get_value().first == 5);
		CHECK(MRR.get_value().second == 6);
	}

	TEST_CASE("tree-builder: root + 3 levels (8 leaves)")
	{
		//create frequency table
		data::FrequencyTable<Datum> table = data::FrequencyTable<Datum>();
		table.increment(1);
		table.increment(2);
		table.increment(2);
		table.increment(3);
		table.increment(3);
		table.increment(3);
		table.increment(3);
		table.increment(4);
		table.increment(4);
		table.increment(4);
		table.increment(4);
		table.increment(4);
		table.increment(5);
		table.increment(5);
		table.increment(5);
		table.increment(5);
		table.increment(5);
		table.increment(5);
		for (int i = 0; i < 9; i++)
		{
			table.increment(6);
		}
		for (int i = 0; i < 18; i++)
		{
			table.increment(7);
		}
		for (int i = 0; i < 25; i++)
		{
			table.increment(8);
		}

		//create tree
		auto tree = std::move(encoding::huffman::build_tree(table));

		//extract children from tree
		//niveau 1
		auto& branch_root = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(*tree);

		//niveau 2
		auto& TBL = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(branch_root.get_left_child()); // 26
		auto& TBR = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(branch_root.get_right_child()); // 41

		//niveau 3
		auto& MLL = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(TBL.get_left_child()); // 11
		auto& MLR = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(TBL.get_right_child()); // 15
		auto& MRL = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(TBR.get_left_child()); // 7: 18
		auto& MRR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(TBR.get_right_child()); // 8: 25

		//niveau 4
		auto& BLLL = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(MLL.get_left_child()); // 4: 5
		auto& BLLR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(MLL.get_right_child()); // 5: 6
		auto& BLRL = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(MLR.get_left_child()); // 7
		auto& BLRR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(MLR.get_right_child()); // 6: 9

		//niveau 5
		auto& BLRLL = dynamic_cast<const data::Branch<std::pair<Datum, u64>>&>(BLRL.get_left_child()); // 3
		auto& BLRLR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(BLRL.get_right_child()); // 3: 4

		//niveau 6
		auto& BLRLLL = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(BLRLL.get_left_child()); // 1: 1
		auto& BLRLLR = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>&>(BLRLL.get_right_child()); // 2: 2

		//check if data in children is correct
		//niveau 3
		CHECK(MRL.get_value().first == 7);
		CHECK(MRL.get_value().second == 18);
		CHECK(MRR.get_value().first == 8);
		CHECK(MRR.get_value().second == 25);

		//niveau 4
		CHECK(BLLL.get_value().first == 4);
		CHECK(BLLL.get_value().second == 5);
		CHECK(BLLR.get_value().first == 5);
		CHECK(BLLR.get_value().second == 6);
		CHECK(BLRR.get_value().first == 6);
		CHECK(BLRR.get_value().second == 9);

		//niveau 5
		CHECK(BLRLR.get_value().first == 3);
		CHECK(BLRLR.get_value().second == 4);

		//niveau 6
		CHECK(BLRLLL.get_value().first == 1);
		CHECK(BLRLLL.get_value().second == 1);
		CHECK(BLRLLR.get_value().first == 2);
		CHECK(BLRLLR.get_value().second == 2);
	}
}
#endif