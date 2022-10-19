// url:https://codeforces.com/contest/1684/problem/H
// time:2022-05-19 21:01:01
// name:H-HardCut

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    
    if (s == std::string(n, '0')) {
        std::cout << "-1\n";
        return;
    }
    
    int L = 0, R = n - 1;
    while (s[L] == '0') {
        L++;
    }
    while (s[R] == '0') {
        R--;
    }
    if (s.substr(L, R - L + 1) == std::string(R - L + 1, '1')) {
        std::vector<std::array<int, 2>> ans;
        if (L > 0) {
            ans.push_back({0, L - 1});
        }
        if (L == R) {
            ans.push_back({L, R});
        } else {
            ans.push_back({L, R - 1});
            ans.push_back({R, R});
        }
        if (R < n - 1) {
            ans.push_back({R + 1, n - 1});
        }
        std::cout << ans.size() << "\n";
        for (auto [l, r] : ans) {
            std::cout << l + 1 << " " << r + 1 << "\n";
        }
        return;
    }
    
    std::vector<std::array<int, 2>> ranges;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            int j = i;
            while (j < n && s[j] == '1') {
                j++;
            }
            ranges.push_back({i, std::min(j + 1, n - 1)});
            i = j;
        }
    }
    
    auto tmp = ranges;
    ranges.clear();
    for (auto [l, r] : tmp) {
        if (ranges.empty() || l > ranges.back()[1] + 1) {
            ranges.push_back({l, r});
        } else {
            ranges.back()[1] = r;
        }
    }
    
    std::vector<std::array<int, 2>> ans;
    
    for (int i = 0; i < ranges[0][0]; i++) {
        ans.push_back({i, i});
    }
    for (int i = 0; i + 1 < int(ranges.size()); i++) {
        for (int j = ranges[i][1] + 1; j < ranges[i + 1][0]; j++) {
            ans.push_back({j, j});
        }
    }
    for (int i = ranges.back()[1] + 1; i < n; i++) {
        ans.push_back({i, i});
    }
    
    int sum = std::count(s.begin(), s.end(), '1');
    
    int N = ranges.size();
    
    std::vector<int> len(N);
    for (int i = 0; i < N; i++) {
        len[i] = ranges[i][1] - ranges[i][0] + 1;
    }
    
    int k = 0;
    while ((1 << k) < sum) {
        k++;
    }
    
    int res = (1 << k) - sum;
    
    int totlen = 0;
    int m = ranges.size();
    while (m > 0 && totlen < 50) {
        m--;
        totlen += len[m];
    }
    if (len[m] > 50) {
        totlen -= len[m] - 50;
        auto [l, r] = ranges[m];
        ranges[m][0] = r - 50 + 1;
        ranges.insert(ranges.begin() + m, {l, r - 50});
        m++;
    }
    
    auto more = [&](int l, int r) {
        int v = 0, u = 0;
        for (int i = l; i <= r; i++) {
            v = 2 * v + s[i] - '0';
            u += s[i] - '0';
        }
        return v - u;
    };
    
    for (int i = 0; i < m; i++) {
        auto [l, r] = ranges[i];
        for (int j = l; j <= r; j++) {
            int k = j;
            while (k + 1 <= r && more(j, k + 1) <= res) {
                k++;
            }
            res -= more(j, k);
            ans.push_back({j, k});
            j = k;
        }
    }
    
    ranges.erase(ranges.begin(), ranges.begin() + m);
    
    N = ranges.size();
    std::vector<int> st(N + 1);
    for (int i = 0; i < N; i++) {
        st[i + 1] = st[i] + ranges[i][1] - ranges[i][0] + 1;
    }
    
    std::vector<std::vector<int>> dp(st[N] + 1, std::vector<int>(res + 1, -1));
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        auto [l, r] = ranges[i];
        int len = r - l + 1;
        for (int x = 0; x <= len; x++) {
            for (int v = 0; v <= res; v++) {
                if (dp[st[i] + x][v] == -1) {
                    continue;
                }
                for (int y = x + 1; y <= len && y - x <= 5; y++) {
                    int t = more(l + x, l + y - 1);
                    if (v + t <= res) {
                        dp[st[i] + y][v + t] = st[i] + x;
                    }
                }
            }
        }
    }
    
    assert(dp[st[N]][res] != -1);
    
    int pos = st[N], val = res;
    while (pos > 0) {
        int npos = dp[pos][val];
        for (int i = 0; i < N; i++) {
            auto [l, r] = ranges[i];
            int len = r - l + 1;
            if (st[i] <= npos && pos <= st[i] + len) {
                ans.push_back({l + npos - st[i], l + pos - st[i] - 1});
                val -= more(l + npos - st[i], l + pos - st[i] - 1);
                pos = npos;
                break;
            }
        }
    }
    
    std::sort(ans.begin(), ans.end());
    
    std::cout << ans.size() << "\n";
    for (auto [l, r] : ans) {
        std::cout << l + 1 << " " << r + 1 << "\n";
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
