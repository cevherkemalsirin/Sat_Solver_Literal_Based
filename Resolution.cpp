#include "Resolution.h"

bool Resolution::isTautology(const clause& c)
{
    for (const Literal& L : c)
    {
        if (CNF::CaluseContains(c, L.GetCompliment()))
        {
            return true;
        }
           
    }
        return false;
}

bool Resolution::SAT(clauseSet K)
{
    bool changed = true;
    while (changed) {
        changed = false;
        clauseSet newClauses;                

        for (size_t i = 0; i < K.size(); ++i) {
            for (size_t j = i + 1; j < K.size(); ++j) {
                for (const auto& L : K[i]) {
                    Literal Lc = L.GetCompliment();
                    if (!CNF::CaluseContains(K[j], Lc)) { continue; }

                    clause R;
                    for (const auto& x : K[i]) {
                        if (x != L) { R.insert(x); }
                    }
                    for (const auto& x : K[j]) {
                        if (x != Lc) { R.insert(x); }
                    }

                    if (R.empty()) { return false; }
                    if (isTautology(R)) { continue; }
                    if (!CNF::CaluseSetContains(K, R) && !CNF::CaluseSetContains(newClauses, R)) 
                    {
                        newClauses.push_back(std::move(R));
                    }
                }
            }
        }

        if (!newClauses.empty()) {
            K.insert(K.end(), newClauses.begin(), newClauses.end());
            changed = true;
        }
    }
    return true;
}
