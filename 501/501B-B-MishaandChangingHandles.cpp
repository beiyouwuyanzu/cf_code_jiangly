// url:https://codeforces.com/contest/501/problem/B
// time:2021-06-24 16:20:22
// name:B-MishaandChangingHandles

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q;
    std::cin >> q;
    std::map<std::string, std::string> old;
    while (q--) {
        std::string a, b;
        std::cin >> a >> b;
        if (!old.count(a)) {
            old[b] = a;
        } else {
            old[b] = old[a];
            old.erase(a);
        }
    }
    std::cout << old.size() << "\n";
    for (auto [b, a] : old) {
        std::cout << a << " " << b << "\n";
    }
    return 0;
}
