#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <map>
#include <vector>

namespace data
{
	template<typename T>
	class FrequencyTable
	{
	public:
		std::map<T, unsigned> freqtable;
		typename std::map<T, unsigned>::iterator it;

		void increment(const T& x)
		{
			this->it = freqtable.find(x);
			if (this->it != freqtable.end())
			{
				this->it->second++;
			}
			else
			{
				freqtable.insert(std::make_pair(x, 1));
			}
		}

		unsigned operator [](const T& x)
		{
			return freqtable.find(x)->second;
		}

		const unsigned operator [](const T& x) const
		{
			return freqtable.find(x)->second;
		}

		const std::vector<T> values() const
		{
			std::vector<T> values;
			for(auto& e : freqtable)
			{
				values.push_back(e.first);
			}
			return values;
		}
	};

	template<typename FrequencyTable, typename T>
	const FrequencyTable count_frequencies(const std::vector<T> ns)
	{
		FrequencyTable freqtable;
		for (auto& e : ns)
		{
			freqtable.increment(e);
		}
		return freqtable;
	}
}

#endif
