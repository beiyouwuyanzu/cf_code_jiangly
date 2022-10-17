//url:https://codeforces.com/contest/1730/problem/D
//time:2022-09-25 18:24:52
//name:D-PrefixesandSuffixes

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s1, s2;
    std::cin >> s1 >> s2;
    
    std::map<std::pair<char, char>, int> cnt;
    for (int i = 0; i < n; i++) {
        cnt[std::minmax(s1[i], s2[n - 1 - i])]++;
    }
    
    int odd = 0;
    for (auto [v, x] : cnt) {
        if (x % 2 == 1 && v.first != v.second) {
            std::cout << "NO\n";
            return;
        }
        odd += x % 2;
    }
    if (odd <= 1) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << std::fixed;
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
