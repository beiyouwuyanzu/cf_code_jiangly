//url:https://codeforces.com/contest/801/problem/B
//time:2021-01-03 17:21:41
//name:B-ValuedKeys

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string x, y;
    std::cin >> x >> y;
    int n = x.length();
    for (int i = 0; i < n; i++) {
        if (x[i] < y[i]) {
            std::cout << "-1\n";
            return 0;
        }
    }
    std::cout << y << "\n";
    return 0;
}
