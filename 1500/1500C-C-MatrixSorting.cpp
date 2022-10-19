// url:https://codeforces.com/contest/1500/problem/C
// time:2021-03-13 12:50:10
// name:C-MatrixSorting

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int N = 1500;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n, std::vector<int>(m)), b(a);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> b[i][j];
            b[i][j]--;
        }
    }
    std::vector<int> down(m);
    std::vector<std::vector<int>> e(n);
    std::vector<int> que;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (b[j][i] > b[j + 1][i]) {
                down[i]++;
                e[j].push_back(i);
            }
        }
        if (down[i] == 0) {
            que.push_back(i);
        }
    }
    std::vector<bool> ok(n);
    for (int i = 0; i < int(que.size()); i++) {
        int c = que[i];
        for (int j = 0; j < n - 1; j++) {
            if (!ok[j] && b[j][c] < b[j + 1][c]) {
                ok[j] = true;
                for (auto v : e[j]) {
                    down[v]--;
                    if (down[v] == 0) {
                        que.push_back(v);
                    }
                }
            }
        }
    }
    std::reverse(que.begin(), que.end());
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    for (auto c : que) {
        std::vector<int> cnt(n);
        for (int i = 0; i < n; i++) {
            cnt[a[i][c]]++;
        }
        for (int i = 1; i < n; i++) {
            cnt[i] += cnt[i - 1];
        }
        std::vector<int> q(n);
        for (int i = n - 1; i >= 0; i--) {
            q[--cnt[a[p[i]][c]]] = p[i];
        }
        p = q;
    }
    for (int i = 0; i < n; i++) {
        if (a[p[i]] != b[i]) {
            std::cout << "-1\n";
            return 0;
        }
    }
    std::cout << que.size() << "\n";
    for (auto x : que) {
        std::cout << x + 1 << " \n"[x == que.back()];
    }
    return 0;
}
