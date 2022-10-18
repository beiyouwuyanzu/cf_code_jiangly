//url:https://codeforces.com/contest/1697/problem/C
//time:2022-06-12 17:53:28
//name:C-awoo'sFavoriteProblem

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s, t;
    std::cin >> s >> t;
    
    for (auto c : { 'a', 'b', 'c' }) {
        if (std::count(s.begin(), s.end(), c) != std::count(t.begin(), t.end(), c)) {
            std::cout << "NO\n";
            return;
        }
    }
    
    std::string s1, t1;
    std::vector<int> a, b;
    for (int i = 0; i < n; i++) {
        if (s[i] != 'b') {
            s1 += s[i];
            a.push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (t[i] != 'b') {
            t1 += t[i];
            b.push_back(i);
        }
    }
    
    if (s1 != t1) {
        std::cout << "NO\n";
        return;
    }
    
    for (int i = 0; i < int(a.size()); i++) {
        if (s1[i] == 'a' ? (a[i] > b[i]) : (a[i] < b[i])) {
            std::cout << "NO\n";
            return;
        }
    }
    
    std::cout << "YES\n";
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

