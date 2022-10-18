//url:https://codeforces.com/contest/1692/problem/F
//time:2022-06-14 17:47:19
//name:F-3SUM

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    int cnt[10] = {};
    std::vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        x %= 10;
        if (cnt[x] < 3) {
            cnt[x]++;
            a.push_back(x);
        }
    }
    
    n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if ((a[i] + a[j] + a[k]) % 10 == 3) {
                    std::cout << "YES\n";
                    return;
                }
            }
        }
    }
    
    std::cout << "NO\n";
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

