// url:https://codeforces.com/contest/1677/problem/B
// time:2022-05-08 17:46:21
// name:B-TokitsukazeandMeeting

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::string s;
    std::cin >> s;
    
    std::vector<bool> row(m);
    std::vector<int> ans(n * m);
    
    std::vector<int> sum(n * m + 1);
    for (int i = 0; i < n * m; i++) {
        sum[i + 1] = sum[i] + s[i] - '0';
    }
    for (int i = 0; i < n * m; i++) {
        int t = sum[i + 1] - sum[std::max(0, i + 1 - m)];
        if (i >= m) {
            ans[i] = ans[i - m];
        }
        ans[i] += (t > 0);
    }
    int cRow = 0;
    for (int i = 0; i < n * m; i++) {
        if (s[i] == '1') {
            if (!row[i % m]) {
                row[i % m] = true;
                cRow++;
            }
        }
        ans[i] += cRow;
    }
    for (int i = 0; i < n * m; i++) {
        std::cout << ans[i] << " \n"[i == n * m - 1];
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
