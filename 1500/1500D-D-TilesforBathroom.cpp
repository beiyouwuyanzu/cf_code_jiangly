//url:https://codeforces.com/contest/1500/problem/D
//time:2021-03-13 13:18:43
//name:D-TilesforBathroom

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> A(n * n);
    std::vector<std::vector<int>> R(n + 1), D[2], RD[2];
    std::vector<bool> vis(n * n);
    for (int i = 0; i < 2; i++) {
        D[i].resize(n + 1);
        RD[i].resize(n + 1);
    }
    for (int i = 0; i < n * n; i++) {
        std::cin >> A[i];
        A[i]--;
    }
    auto f = [&](int x, int y, int v) {
        return std::max(v / n - x, v % n - y);
    };
    auto merge = [&](int x, int y, const std::vector<int> &a, const std::vector<int> &b, std::vector<int> &c) {
        int i = 0, j = 0;
        while ((i < int(a.size()) || j < int(b.size())) && int(c.size()) <= q) {
            if (i < int(a.size()) && (j == int(b.size()) || f(x, y, a[i]) < f(x, y, b[j]))) {
                if (!vis[A[a[i]]]) {
                    c.push_back(a[i]);
                    vis[A[a[i]]] = true;
                }
                i++;
            } else {
                if (!vis[A[b[j]]]) {
                    c.push_back(b[j]);
                    vis[A[b[j]]] = true;
                }
                j++;
            }
        }
        for (auto x : c) {
            vis[A[x]] = false;
        }
    };
    std::vector<int> ans(n + 1);
    int cur = 0;
    for (int i = n - 1; i >= 0; i--) {
        cur ^= 1;
        for (int j = 0; j <= n; j++) {
            R[j].clear();
            D[cur][j].clear();
            RD[cur][j].clear();
        }
        for (int j = n - 1; j >= 0; j--) {
            merge(i, j, RD[!cur][j + 1], {i * n + j}, RD[cur][j]);
            merge(i, j, D[!cur][j], RD[cur][j], D[cur][j]);
            merge(i, j, R[j + 1], RD[cur][j], R[j]);
            std::vector<int> v;
            merge(i, j, R[j], D[cur][j], v);
            int x;
            if (int(v.size()) > q) {
                x = std::min({n - i, n - j, f(i, j, v.back())});
            } else {
                x = std::min(n - i, n - j);
            }
            ans[x]++;
        }
    }
    for (int i = n; i >= 1; i--) {
        ans[i - 1] += ans[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << "\n";
    }
    return 0;
}
