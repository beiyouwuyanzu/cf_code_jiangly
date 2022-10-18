//url:https://codeforces.com/contest/1693/problem/F
//time:2022-06-16 19:11:01
//name:F-IMightBeWrong

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    int cnt = std::count(s.begin(), s.end(), '1');
    if (cnt > n - cnt) {
        std::reverse(s.begin(), s.end());
        for (auto &c : s) {
            c ^= 1;
        }
        cnt = n - cnt;
    }
    
    int ans = 0;
    int len = 0;
    while (len < n && s[len] == '0') {
        len++;
    }
    
    std::vector<int> a(n + 1);
    for (int i = 0; i < n; i++) {
        a[i + 1] = a[i] + (s[i] == '0' ? 1 : -1);
    }
    
    std::vector<int> last(2 * n + 1, -1);
    for (int i = 0; i <= n; i++) {
        last[a[i] + n] = i;
    }
    
    while (len != n - cnt) {
        ans++;
        if (len >= n - 2 * cnt) {
            len = n - cnt;
        } else {
            len += (last[len + n] - len) / 2;
        }
    }
    
    std::cout << ans << "\n";
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

