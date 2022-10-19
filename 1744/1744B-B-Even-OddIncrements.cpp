// url:https://codeforces.com/contest/1744/problem/B
// time:2022-10-18 14:08:02
// name:B-Even-OddIncrements

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    
    int cnt[2] {};
    i64 sum[2] {};
    
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cnt[x % 2]++;
        sum[x % 2] += x;
    }
    
    for (int i = 0; i < q; i++) {
        int t, x;
        std::cin >> t >> x;
        
        sum[t] += 1LL * x * cnt[t];
        if (x % 2) {
            cnt[!t] += cnt[t];
            sum[!t] += sum[t];
            cnt[t] = sum[t] = 0;
        }
        
        std::cout << sum[0] + sum[1] << "\n";
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
