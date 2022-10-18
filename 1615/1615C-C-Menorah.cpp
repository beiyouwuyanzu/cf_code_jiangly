//url:https://codeforces.com/contest/1615/problem/C
//time:2021-12-24 17:48:53
//name:C-Menorah

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string a, b;
    std::cin >> a >> b;
    
    int ans = n + 1;
    for (auto c : {0, 1}) {
        std::vector<int> goal(n);
        for (int i = 0; i < n; i++) {
            goal[i] = b[i] - '0';
            goal[i] ^= c;
        }
        
        int cnt[2] = {};
        for (int i = 0; i < n; i++) {
            int x = a[i] - '0';
            if (x != goal[i]) {
                cnt[x]++;
            }
        }
        
        if ((cnt[0] == cnt[1] || cnt[0] == cnt[1] - 1) && (cnt[0] + cnt[1]) % 2 == c) {
            ans = std::min(ans, cnt[0] + cnt[1]);
        }
    }
    if (ans > n) {
        ans = -1;
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

