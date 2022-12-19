#ifdef TEST_BUILD

#include "catch.hpp"
#include <data/frequency-table.h>
#include <vector>

namespace
{
	TEST_CASE("Empty frequency list")
	{
		std::vector<char> expected;
		data::FrequencyTable<char> freqtable;
		REQUIRE(freqtable.values() == expected);
	}

	TEST_CASE("Increment 1 value, check value")
	{
		std::vector<char> expected = { 'a' };
		data::FrequencyTable<char> freqtable;
		freqtable.increment('a');
		REQUIRE(freqtable.values() == expected);
	}

	TEST_CASE("Increment 1 value, check index")
	{
		data::FrequencyTable<char> freqtable;
		freqtable.increment('a');
		REQUIRE(freqtable['a'] == 1);
	}

	TEST_CASE("Increment 1 value mutiple times, check index")
	{
		data::FrequencyTable<char> freqtable;
		freqtable.increment('a');
		freqtable.increment('a');
		freqtable.increment('a');
		freqtable.increment('a');
		REQUIRE(freqtable['a'] == 4);
	}

	TEST_CASE("Increment multiple values")
	{
		std::vector<char> expected = { 'a', 'b', 'c', 'd' };
		data::FrequencyTable<char> freqtable;
		freqtable.increment('a');
		freqtable.increment('b');
		freqtable.increment('c');
		freqtable.increment('d');
		REQUIRE(freqtable.values() == expected);
	}

	TEST_CASE("Increment multiple values, check indexes")
	{
		data::FrequencyTable<char> freqtable;
		freqtable.increment('a');
		freqtable.increment('b');
		freqtable.increment('c');
		REQUIRE(freqtable['a'] == 1);
		REQUIRE(freqtable['b'] == 1);
		REQUIRE(freqtable['c'] == 1);
	}

	TEST_CASE("Increment multiple values multiple times, check indexes")
	{
		data::FrequencyTable<char> freqtable;
		freqtable.increment('a');
		freqtable.increment('a');
		freqtable.increment('a');
		freqtable.increment('a');
		freqtable.increment('b');
		freqtable.increment('c');
		freqtable.increment('c');
		freqtable.increment('c');
		REQUIRE(freqtable['a'] == 4);
		REQUIRE(freqtable['b'] == 1);
		REQUIRE(freqtable['c'] == 3);
	}

	TEST_CASE("Give vector with 1 value multiple times")
	{
		data::FrequencyTable<char> expected;
		expected.increment('a');
		expected.increment('a');
		expected.increment('a');
		expected.increment('a');

		const std::vector<char> values = { 'a', 'a', 'a', 'a' };
		data::FrequencyTable<char> freqtable = data::count_frequencies<data::FrequencyTable<char>>(values);
		REQUIRE(freqtable.values() == expected.values());
		REQUIRE(freqtable['a'] == expected['a']);
	}

	TEST_CASE("Give vector with multiple values multiple times")
	{
		data::FrequencyTable<char> expected;
		expected.increment('a');
		expected.increment('a');
		expected.increment('a');
		expected.increment('a');
		expected.increment('b');
		expected.increment('b');
		expected.increment('b');
		expected.increment('c');
		expected.increment('d');
		expected.increment('e');
		expected.increment('e');

		const std::vector<char> values = { 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'c', 'd', 'e', 'e' };
		data::FrequencyTable<char> freqtable = data::count_frequencies<data::FrequencyTable<char>>(values);
		REQUIRE(freqtable.values() == expected.values());
		REQUIRE(freqtable['a'] == expected['a']);
		REQUIRE(freqtable['b'] == expected['b']);
		REQUIRE(freqtable['c'] == expected['c']);
		REQUIRE(freqtable['d'] == expected['d']);
		REQUIRE(freqtable['e'] == expected['e']);
	}
}

#endif