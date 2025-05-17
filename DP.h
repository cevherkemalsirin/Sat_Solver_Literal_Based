#pragma once
#include "Resolution.h"

class DP
{
private:

	bool UnitRule(clauseSet& K, Assignment& A, bool& changed);
	void PureLiterals(clauseSet& K, Assignment& A, bool& changed);
	void EliminateVar(clauseSet& K, const std::string& v);
	bool simplifyUntilFixedPoint(clauseSet& K, Assignment& A);
	bool DPLL_R(clauseSet& K, Assignment& A);

public:
	
	bool DPSAT(clauseSet K);
	bool DPLLSAT(clauseSet K);

};

