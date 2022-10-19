// url:https://codeforces.com/contest/1491/problem/G
// time:2021-02-28 18:21:44
// name:G-SwitchandFlip

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
        c[i]--;
    }
    std::vector<int> a;
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        int j = i;
        while (!vis[j]) {
            vis[j] = true;
            j = c[j];
        }
        a.push_back(i);
    }
    std::vector<std::pair<int, int>> ans;
    auto swap = [&](int i, int j) {
        std::swap(c[i], c[j]);
        ans.emplace_back(i, j);
    };
    auto solve = [&](int u, int v) {
        swap(u, v);
        while (true) {
            if (c[u] != v) {
                swap(u, c[u]);
            } else if (c[v] != u) {
                swap(v, c[v]);
            } else {
                swap(u, v);
                break;
            }
        }
    };
    for (int i = 0; i + 1 < int(a.size()); i += 2) {
        solve(a[i], a[i + 1]);
    }
    int u = a.back();
    if (c[u] != u) {
        if (a.size() == 1) {
            int v = c[u];
            swap(u, v);
            swap(c[u], v);
            while (true) {
                if (c[u] != v) {
                    swap(u, c[u]);
                } else if (c[v] != u) {
                    swap(v, c[v]);
                } else {
                    swap(u, v);
                    break;
                }
            }
        } else {
            int i = 0;
            while (c[i] != i) {
                i++;
            }
            solve(u, i);
        }
    }
    std::cout << ans.size() << "\n";
    for (auto [i, j] : ans) {
        std::cout << i + 1 << " " << j + 1 << "\n";
    }
    return 0;
}

