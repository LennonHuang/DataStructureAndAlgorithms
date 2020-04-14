#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::string;
using std::vector;
using std::cin;
using std::unordered_map;

struct Query
{
	string type, s;
	size_t ind;
};

class QueryProcessor
{
	int bucket_count;//m
	// store all strings in one vector
	vector<string> elems;
	unordered_map<size_t, vector<string>> elems_hval;//unordered_map to realize chaining
	//hash function takes a string and returns the hash value (0 to m-1)
	size_t hash_func(const string& s) const
	{
		static const size_t multiplier = 263;//x multiplier for hash function
		static const size_t prime = 1000000007;//p for prevent the hash result in the range of hash table
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {}//Constructor with hash size m

	Query readQuery() const
	{
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const
	{
		std::cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query)
	{
		if (query.type == "check")
		{
			std::unordered_map<size_t, vector<string>>::iterator map_it = elems_hval.find(query.ind);
			if (map_it != elems_hval.end())
			{
				for (int i = elems_hval[query.ind].size() - 1; i >= 0; i--)
				{
					std::cout << elems_hval[query.ind][i] << " ";
				}
			}
			std::cout << "\n";
		}
		else
		{
			std::vector<string>::iterator it;
			size_t index = hash_func(query.s);
			it = std::find(elems_hval[index].begin(), elems_hval[index].end(), query.s);//Only search at corresponding hash value chain
			if (query.type == "find")
			{
				if (it != elems_hval[index].end())
				{
					writeSearchResult(true);//Found in corresponding hash value chain
				}
				else
				{
					writeSearchResult(false);//Not Found in corresponding hash value chain
				}
			}
			else if (query.type == "add")
			{
				if (it == elems_hval[index].end())//Only push back if it is not a duplicate one
					elems_hval[index].push_back(query.s);
				//std::cout << "Adding: " << index << elems_hval[index].back() << "\n";
			}
			else if (query.type == "del")
			{
				if (it != elems.end())
				{
					elems_hval[index].erase(it);
				}
			}
		}
	}

	void processQueries()
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	int bucket_count;//
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	return 0;
}
