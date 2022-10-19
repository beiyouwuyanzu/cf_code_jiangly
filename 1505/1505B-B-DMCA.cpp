// url:https://codeforces.com/contest/1505/problem/B
// time:2021-04-01 18:07:57
// name:B-DMCA

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int a;
    std::cin >> a;
    std::cout << (a - 1) % 9 + 1 << "\n";
    return 0;
}

