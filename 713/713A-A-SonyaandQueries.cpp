// url:https://codeforces.com/contest/713/problem/A
// time:2021-07-07 15:46:23
// name:A-SonyaandQueries

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    int cnt[1 << 18] = {};
    
    auto get = [&](i64 x) {
        int mask = 0;
        for (int i = 0; x > 0; i++, x /= 10) {
            mask |= (x % 2) << i;
        }
        return mask;
    };
    
    while (t--) {
        std::string op;
        std::cin >> op;
        if (op == "+") {
            i64 x;
            std::cin >> x;
            cnt[get(x)]++;
        } else if (op == "-") {
            i64 x;
            std::cin >> x;
            cnt[get(x)]--;
        } else {
            std::string s;
            std::cin >> s;
            int mask = 0;
            for (auto c : s) {
                mask = 2 * mask + c - '0';
            }
            std::cout << cnt[mask] << "\n";
        }
    }
    
    return 0;
}
