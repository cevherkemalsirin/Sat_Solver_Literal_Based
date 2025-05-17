#pragma once
#include "LiteralUtils.h"

struct Resolution
{ 
public:
	static bool isTautology(const clause& c);
	static bool SAT(clauseSet K);
};

