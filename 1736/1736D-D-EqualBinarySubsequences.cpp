// url:https://codeforces.com/contest/1736/problem/D
// time:2022-10-10 19:07:09
// name:D-EqualBinarySubsequences

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    if (std::count(s.begin(), s.end(), '1') % 2) {
        std::cout << -1 << "\n";
        return;
    }
    
    std::vector<int> a;
    for (int i = 0; i < 2 * n; i += 2) {
        if (s[i] != s[i + 1]) {
            if (s[i] == '0' + int(a.size()) % 2) {
                a.push_back(i);
            } else {
                a.push_back(i + 1);
            }
        }
    }
    
    std::cout << a.size();
    for (auto x : a) {
        std::cout << " " << x + 1;
    }
    std::cout << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << 2 * i + 1 << " \n"[i == n - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

