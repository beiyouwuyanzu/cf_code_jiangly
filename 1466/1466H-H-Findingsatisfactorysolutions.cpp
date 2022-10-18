//url:https://codeforces.com/contest/1466/problem/H
//time:2020-12-30 22:36:13
//name:H-Findingsatisfactorysolutions

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 1000000007;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    std::vector<int> a;
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        int j = i;
        int len = 0;
        while (!vis[j]) {
            vis[j] = true;
            j = p[j];
            len++;
        }
        a.push_back(len);
    }
    std::sort(a.begin(), a.end());
    std::vector<int> len, cnt;
    for (int i = 0; i < int(a.size()); ) {
        int j = i;
        while (j < int(a.size()) && a[i] == a[j]) {
            j++;
        }
        len.push_back(a[i]);
        cnt.push_back(j - i);
        i = j;
    }
    int k = len.size();
    std::vector<int> pre(k + 1);
    pre[0] = 1;
    for (int i = 0; i < k; ++i) {
        pre[i + 1] = pre[i] * (cnt[i] + 1);
    }
    std::vector<int> fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = i64(fac[i - 1]) * i % P;
    }
    std::vector<int> dp(pre[k]);
    std::vector<std::vector<int>> C(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        }
    }
    std::vector<std::vector<int>> sub(pre[k]);
    for (int mask = 0; mask < pre[k]; mask++) {
        std::function<void(int, int)> dfs = [&](int x, int r) {
            if (x == k) {
                sub[mask].push_back(r);
                return;
            }
            for (int i = 0; i <= mask / pre[x] % (cnt[x] + 1); i++) {
                dfs(x + 1, r + pre[x] * i);
            }
        };
        dfs(0, 0);
    }
    dp[0] = 1;
    std::vector<int> val(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            val[i] = (val[i] + i64(C[i][j]) * fac[j] % P * fac[n - j - 1]) % P;
        }
    }
    std::vector<std::vector<int>> pval(n, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        pval[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            pval[i][j] = i64(pval[i][j - 1]) * val[i] % P;
        }
    }
    for (int mask = 1; mask < pre[k]; mask++) {
        std::vector<int> c(k);
        for (int i = 0; i < k; i++) {
            c[i] = mask / pre[i] % (cnt[i] + 1);
        }
        for (auto t : sub[mask]) {
            if (t == 0) {
                continue;
            }
            int s1 = 0, s2 = 0;
            std::vector<int> b(k);
            int res = P - 1;
            for (int i = 0; i < k; i++) {
                b[i] = t / pre[i] % (cnt[i] + 1);
                s1 += len[i] * b[i];
                s2 += len[i] * (c[i] - b[i]);
                res = i64(res) * C[c[i]][b[i]] % P;
                if (b[i] % 2 == 1) {
                    res = P - res;
                }
            }
            res = i64(res) * pval[s2][s1] % P;
            dp[mask] = (dp[mask] + i64(res) * dp[mask - t]) % P;
        }
    }
    std::cout << dp[pre[k] - 1] << "\n";
    return 0;
}
