// url:https://codeforces.com/contest/158/problem/B
// time:2023-04-26 19:41:02
// name:B-Taxi

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    int cnt[5] {};
    for (int i = 0; i < n; i++) {
        int s;
        std::cin >> s;
        cnt[s]++;
    }
    
    int ans = cnt[4];
    int t = std::min(cnt[1], cnt[3]);
    cnt[1] -= t, cnt[3] -= t;
    ans += t;
    ans += cnt[3];
    ans += (cnt[2] * 2 + cnt[1] + 3) / 4;
    std::cout << ans << "\n";
    
    return 0;
}
