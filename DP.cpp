#include "DP.h"

bool DP::UnitRule(clauseSet& K, Assignment& A, bool& changed)
{
    for (auto it = K.begin(); it != K.end(); ) {
        if (it->empty()) return false;                      

        if (it->size() == 1) {                                 
            changed = true;
            Literal L = *it->begin();
            A[L.GetVar()] = L.GetNegated() ? 0 : 1;                         

            for (auto it2 = K.begin(); it2 != K.end(); ) {
                if (CNF::CaluseContains(*it2, L))
                { 
                    it2 = K.erase(it2); 
                    continue; 
                }
                clause tmp;
                for (auto const& x : *it2)
                {
                    if (x != L.GetCompliment())
                    {
                        tmp.insert(x);
                    }
                }
                   
                *it2 = tmp;
                ++it2;
            }
            it = K.begin();                                    
        }
        else ++it;
    }
    return true;

}

void DP::PureLiterals(clauseSet& K, Assignment& A, bool& changed)
{
    changed = false;

    std::map<std::string, int> pol;

    for (const auto& c : K) 
    {
        for (const auto& L : c) 
        {
            int sign = L.GetNegated() ? -1 : 1;

            auto& slot = pol[L.GetVar()];
            if (slot == 0) 
            { 
                slot = sign;
            }
            else if (slot != sign)
            { 
                slot = 2; 
            }
        }
    }
    for (const auto& pr : pol) {
        int p = pr.second;

        if (p == 1 || p == -1) {
            changed = true;

            Literal L{ pr.first, p == -1 };

            A[L.GetVar()] = p == -1 ? 0 : 1;
            for (auto it = K.begin(); it != K.end();) 
            {
                if (CNF::CaluseContains(*it, L)) 
                {
                    it = K.erase(it);
                }
                else {
                    ++it;
                }
            }
            return;
        }
    }
}

void DP::EliminateVar(clauseSet& K, const std::string& v)
{
    clauseSet pos;
    clauseSet neg;
    clauseSet other;
    for (const auto& c : K) {
        if (CNF::CaluseContains(c, { v, false })) 
        { 
            pos.push_back(c);
        }
        else if (CNF::CaluseContains(c, { v, true })) 
        { 
            neg.push_back(c); 
        }
        else 
        { 
            other.push_back(c);
        }
    }
    for (const auto& p : pos) 
    {
        for (const auto& n : neg) 
        {
            clause R;
            for (const auto& x : p) {
                if (x.GetVar() != v) 
                { 
                    R.insert(x);
                }
            }
            for (const auto& x : n) {
                if (x.GetVar() != v) 
                { 
                    R.insert(x);
                }
            }
            if (!Resolution::isTautology(R) && std::find(other.begin(), other.end(), R) == other.end())
            {
                other.push_back(R);
            }
        }
    }
    K.swap(other);
}

bool DP::simplifyUntilFixedPoint(clauseSet& K, Assignment& A)
{
    bool changed;
    do {

        changed = false;
        if (!UnitRule(K, A, changed))
        { 
            return false; 
        }
        bool changedPure;
        PureLiterals(K, A, changedPure);
        changed = changed || changedPure;

    } while (changed);
    return true;
}


bool DP::DPLL_R(clauseSet& K, Assignment& A)
{
    if (!simplifyUntilFixedPoint(K, A)) { return false; }
    if (K.empty()) { return true; }
    Literal L = *K.front().begin();
    {
        clauseSet K1 = K;
        Assignment A1 = A;
        K1.push_back({ L });
        if (DPLL_R(K1, A1))
        {
            return true;
        }
    }
    {
        clauseSet K2 = K;
        Assignment A2 = A;
        K2.push_back({ L.GetCompliment() });

        if (DPLL_R(K2, A2))
        {
            return true;
        }
    }
    return false;
}


bool DP::DPSAT(clauseSet K)
{
    Assignment A;
    if (!simplifyUntilFixedPoint(K, A)) { return false; }
    while (!K.empty()) {
        std::string v;
        for (const auto& c : K) {
            if (!c.empty()) {
                v = c.begin()->GetVar();
                break;
            }
        }
        EliminateVar(K, v);
        if (!simplifyUntilFixedPoint(K, A)) { return false; }
    }
    return true;
}

bool DP::DPLLSAT(clauseSet K)
{
    Assignment A;
    return DPLL_R(K, A);
}

