#pragma once
#include <iostream>
#include <string>

using namespace std;

class Literal
{
	string _atom;
	bool _negated;

public:

	inline string GetVar() const { return _atom; }
	inline bool GetNegated() const { return _negated; }

	Literal(string atom, bool neg) :_atom(atom), _negated(neg) {};

	inline Literal GetCompliment() const { return { _atom, !_negated }; }
	inline string GetAtom() const
	{
		if (_negated)
		{
			return "~" + _atom;
		}
		else
		{
			return _atom;
		}
	}
	
	bool operator < (const Literal& other) const {
		return GetAtom() < other.GetAtom();
	}

	bool operator==(const Literal& other) const
	{
		return GetAtom() == other.GetAtom();
	}

	bool operator!=(const Literal& other) const
	{
		return !(GetAtom() == other.GetAtom());
	}
};



