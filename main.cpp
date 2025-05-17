#include "LiteralUtils.h"
#include "DP.h"

int main1()
{
    return 0;
    DP dpsat;
	cout << "Enter CNF:" << endl;
	clauseSet K = CNF::ReadCNF();

    clauseSet R = K;
    clauseSet P = K;
    clauseSet D = K;
    std::cout << "\nResolution  : " << (Resolution::SAT(R) ? "Satisfiable" : "Unsatisfiable") << '\n';
    std::cout << "Davis–Putnam: " << (dpsat.DPSAT(P) ? "Satisfiable" : "Unsatisfiable") << '\n';
    std::cout << "DPLL        : " << (dpsat.DPLLSAT(D) ? "Satisfiable" : "Unsatisfiable") << '\n';
}