// url:https://codeforces.com/contest/714/problem/B
// time:2021-07-07 17:14:04
// name:B-FilyaandHomework

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    std::set<int> s;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        s.insert(x);
    }
    
    if (s.size() <= 2) {
        std::cout << "YES\n";
        return 0;
    }
    
    if (s.size() >= 4) {
        std::cout << "NO\n";
        return 0;
    }
    
    if (*s.begin() + *s.rbegin() == 2 * *std::next(s.begin())) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    
    return 0;
}
