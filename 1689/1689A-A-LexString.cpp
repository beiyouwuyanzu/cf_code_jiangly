//url:https://codeforces.com/contest/1689/problem/A
//time:2022-06-10 19:38:35
//name:A-LexString

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::string a, b;
    std::cin >> a >> b;
    
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    
    int cur = 0, i = 0, j = 0;
    std::string c;
    while (i < n && j < m) {
        bool oka = cur < k;
        bool okb = cur > -k;
        if (oka && (!okb || a[i] < b[j])) {
            c += a[i++];
            cur = std::max(0, cur) + 1;
        } else {
            c += b[j++];
            cur = std::min(0, cur) - 1;
        }
    }
    
    std::cout << c << "\n";
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

