//url:https://codeforces.com/contest/1622/problem/B
//time:2022-06-09 15:47:19
//name:B-BerlandMusic

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n), a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        a[p[i]] = i;
    }
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> q(n);
    int cnt = 0;
    for (auto c : { '0', '1' }) {
        for (int i = 0; i < n; i++) {
            if (s[a[i]] == c) {
                q[a[i]] = cnt++;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << q[i] + 1 << " \n"[i == n - 1];
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
