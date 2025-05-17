#include "LiteralUtils.h"
#include "Resolution.h"
#include "DP.h"
#include <filesystem>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;

struct Stat { bool sat; double ms; };
template <class F> Stat timeIt(F fn) {
    auto t0 = std::chrono::steady_clock::now();
    bool sat = fn();
    auto t1 = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return { sat, ms };
}


int main(int argc, char* argv[]) {

        std::cout << "Enter CNF:\n";
        clauseSet K = CNF::ReadCNF();
        clauseSet R = K, P = K, D = K;
        DP dp;
        auto s1 = timeIt([&] { return Resolution::SAT(R); });
        auto s2 = timeIt([&] { return dp.DPSAT(P);        });
        auto s3 = timeIt([&] { return dp.DPLLSAT(D);      });
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "Resolution  : " << (s1.sat ? "SAT" : "UNSAT") << " in " << s1.ms << " ms\n";
        std::cout << "Davis-Putnam: " << (s2.sat ? "SAT" : "UNSAT") << " in " << s2.ms << " ms\n";
        std::cout << "DPLL        : " << (s3.sat ? "SAT" : "UNSAT") << " in " << s3.ms << " ms\n";
   
}
