//url:https://codeforces.com/contest/1503/problem/F
//time:2021-04-03 21:28:43
//name:F-BalancetheCards

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
void gg() {
    std::cout << "NO\n";
    std::exit(0);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(2 * n), b(2 * n);
    std::vector<int> xa(n), ya(n), xb(n), yb(n);
    for (int i = 0; i < 2 * n; i++) {
        std::cin >> a[i] >> b[i];
        if (a[i] > 0) {
            xa[a[i] - 1] = i;
        } else {
            ya[-1 - a[i]] = i;
        }
        if (b[i] > 0) {
            xb[b[i] - 1] = i;
        } else {
            yb[-1 - b[i]] = i;
        }
    }
    std::vector<bool> vis(2 * n);
    std::vector<int> ans;
    std::vector<int> next(2 * n, -1);
    for (int i = 0; i < 2 * n; i++) {
        if (vis[i] || a[i] < 0 || b[i] < 0) {
            continue;
        }
        std::vector<int> u, d;
        int j = i;
        while (!vis[j]) {
            vis[j] = true;
            u.push_back(j);
            if (u.size() % 2 == 1) {
                d.push_back(a[j] > 0);
                j = a[j] > 0 ? ya[a[j] - 1] : xa[-1 - a[j]];
            } else {
                d.push_back(b[j] > 0);
                j = b[j] > 0 ? yb[b[j] - 1] : xb[-1 - b[j]];
            }
        }
        int c[2][2] {};
        for (int j = 0; j < int(d.size()); j++) {
            c[d[j]][j % 2]++;
        }
        if (std::abs(c[0][0] - c[0][1]) != 1 || std::abs(c[1][0] - c[1][1]) != 1) {
            gg();
        }
        std::vector<int> s, t, q;
        for (auto x : d) {
            std::cerr << x << " ";
        }
        std::cerr << "\n";
        for (int j = 0; j < int(u.size()); j++) {
            if (s.size() >= 2 && q.back() == q[q.size() - 2]) {
                int x = s.back();
                int y = t.back();
                s.pop_back();
                t.pop_back();
                q.pop_back();
                if (q.back() == 1) {
                    next[t.back()] = x;
                    next[y] = u[j];
                    t.back() = u[j];
                } else {
                    next[u[j]] = x;
                    next[y] = s.back();
                    s.back() = u[j];
                }
                q.back() = d[j];
            } else {
                s.push_back(u[j]);
                t.push_back(u[j]);
                q.push_back(d[j]);
            }
        }
        if (s.size() == 4) {
            next[t[0]] = s[3];
            next[t[3]] = s[2];
        }
        for (int j = s[q[1]]; j != -1; j = next[j]) {
            ans.push_back(j);
        }
        for (int j = s[q[0]]; j != -1; j = next[j]) {
            ans.push_back(j);
        }
    }
    if (int(ans.size()) < 2 * n) {
        gg();
    }
    std::cout << "YES\n";
    for (int i = 0; i < 2 * n; i++) {
        std::cout << a[ans[i]] << " " << b[ans[i]] << "\n";
    }
    return 0;
}

