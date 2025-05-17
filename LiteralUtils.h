#pragma once
#include "Literal.h"
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>

using clause = set <Literal>;
using clauseSet = vector<clause>;
using Assignment = map<string, int>;

namespace CNF
{
	inline Literal CreateLiteralFromString(string const& str)
	{
		if (str[0] == '~')
		{
			return Literal{ str.substr(1), true };
		}
		else
		{
			return Literal{ str, false };
		}
	}



	inline bool CaluseContains(const clause& c, const Literal& l)
	{
		return c.count(l) != 0;
	}

	inline bool CaluseSetContains(const clauseSet& k, const clause& c)
	{
		return find(k.begin(), k.end(), c) != k.end();
	}

	inline void PrintClause(clause const& c)
	{
		std::cout << "{ ";
		for (auto const& L : c) cout << L.GetAtom() << " ";
		std::cout << '}';
	}

	inline void PrintClauseSet(const clauseSet& K)
	{
		for (auto const& c : K)
		{
			PrintClause(c);
			cout << '\n';
		}
	}
	// ------------ custom CNF from any istream ----
	inline clauseSet ReadCNF(std::istream& in = std::cin) {
		int n;
		if (!(in >> n)) { return {}; }
		in.ignore();
		clauseSet K;
		for (int i = 0; i < n; ++i) {
			std::string line; std::getline(in, line);
			std::istringstream iss(line);
			clause c; std::string tok;
			while (iss >> tok) { c.insert(CreateLiteralFromString(tok)); }
			K.push_back(std::move(c));
		}
		return K;
	}




}