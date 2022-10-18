//url:https://codeforces.com/contest/1692/problem/H
//time:2022-06-14 17:54:59
//name:H-Gambling

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::map<int, std::vector<int>> p;
    
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
        p[x[i]].push_back(i);
    }
    
    int a = x[0], l = 0, r = 1, ans = 1;
    
    for (auto [b, q] : p) {
        int min = 0, k = q[0];
        for (int j = 0; j < int(q.size()); j++) {
            int i = q[j];
            int cur = j - (i - j);
            if (cur < min) {
                min = cur;
                k = i;
            }
            int res = cur + 1 - min;
            if (res > ans) {
                ans = res;
                a = b;
                l = k;
                r = i + 1;
            }
        }
    }
    
    std::cout << a << " " << l + 1 << " " << r << "\n";
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

