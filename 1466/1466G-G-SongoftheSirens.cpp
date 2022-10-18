//url:https://codeforces.com/contest/1466/problem/G
//time:2020-12-30 19:29:56
//name:G-SongoftheSirens

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 1000000007;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::string s0, t;
    std::cin >> s0 >> t;
    int l = s0.length();
    std::vector<int> pw(n + 1), len(n), invpw(n + 1);
    pw[0] = 1;
    invpw[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pw[i] = 2 * pw[i - 1] % P;
        invpw[i] = i64(invpw[i - 1]) * (P + 1) / 2 % P;
    }
    for (int i = n - 1; i >= 0; i--) {
        len[i] = (i < n - 1 && t[i] == t[i + 1]) ? len[i + 1] + 1 : 1;
    }
    std::vector<std::vector<int>> next(n + 1, std::vector<int>(26, n)), cnt(n + 1, std::vector<int>(26));
    for (int i = n - 1; i >= 0; --i) {
        next[i] = next[i + 1];
        cnt[i] = cnt[i + 1];
        next[i][t[i] - 'a'] = i;
        cnt[i][t[i] - 'a'] = (cnt[i][t[i] - 'a'] + invpw[i]) % P;
    }
    while (q--) {
        int k;
        std::string w;
        std::cin >> k >> w;
        int m = w.length();
        int ans = 0;
        for (int u = 0; u <= l; u++) {
            bool good = true;
            std::string w0;
            for (int i = 0; i < m; i++) {
                int v = (u + i) % (l + 1);
                if (v != l) {
                    if (w[i] != s0[v]) {
                        good = false;
                    }
                } else {
                    w0 += w[i];
                }
            }
            if (!good) {
                continue;
            }
            int j = 0;
            while (true) {
                if (w0.empty()) {
                    ans = (ans + pw[k - j]) % P;
                    break;
                }
                if (j == k) {
                    break;
                }
                bool odd = true, even = true;
                for (int i = 0; i < int(w0.length()); i++) {
                    if (w0[i] != t[j]) {
                        if (i % 2 == 0) {
                            even = false;
                        } else {
                            odd = false;
                        }
                    }
                }
                if (!odd && !even) {
                    break;
                }
                if (odd && even) {
                    int pos = std::min(k, j + len[j]);
                    int v = pw[k - pos];
                    int c = i64(pw[k - 1]) * (cnt[pos][w0[0] - 'a'] - cnt[k][w0[0] - 'a'] + P) % P;
                    int l1 = std::min(k - j, len[j]);
                    int l2 = l1 + 1;
                    int p = pw[l1];
                    if (l1 >= 30 || (1 << l1) >= int(w0.length())) {
                        ans = (ans + (i64(v) - c - c + P + P) * (p - int(w0.length()) + P)) % P;
                    }
                    if (l2 >= 30 || (1 << l2) >= int(w0.length())) {
                        ans = (ans + i64(c) * (pw[l2] - int(w0.length()) + P)) % P;
                    }
                    break;
                }
                std::string w1;
                for (int i = 0; i < int(w0.length()); i++) {
                    if (even ^ (i % 2 == 0)) {
                        w1 += w0[i];
                    }
                }
                if (w0 == w1) {
                    j = std::min(k, next[j][w0[0] - 'a']);
                } else {
                    j++;
                }
                w0 = w1;
            }
        }
        std::cout << ans << "\n";
    }
    return 0;
}
