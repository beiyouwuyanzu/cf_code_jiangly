//url:https://codeforces.com/contest/1689/problem/B
//time:2022-06-10 19:43:59
//name:B-MysticPermutation

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    
    if (n == 1) {
        std::cout << "-1\n";
        return;
    }
    
    std::set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(i);
    }
    for (int i = 0; i < n - 2; i++) {
        int x = *s.begin();
        if (x == p[i]) {
            x = *std::next(s.begin());
        }
        std::cout << x + 1 << " ";
        s.erase(x);
    }
    
    int a = *s.begin();
    int b = *s.rbegin();
    
    if (a == p[n - 2] || b == p[n - 1]) {
        std::swap(a, b);
    }
    std::cout << a + 1 << " " << b + 1 << "\n";
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

