//url:https://codeforces.com/contest/641/problem/E
//time:2021-07-09 21:50:34
//name:E-LittleArtemandTimeMachine

#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::tuple<int, int, int, int>> op;
    for (int i = 0; i < n; i++) {
        int a, t, x;
        std::cin >> a >> t >> x;
        op.emplace_back(x, t, i, a);
    }
    
    std::vector<int> ans(n, -1);
    
    Fenwick<int> fen(n);
    
    std::sort(op.begin(), op.end());
    for (int l = 0, r; l < n; l = r) {
        for (r = l; r < n && std::get<0>(op[l]) == std::get<0>(op[r]); r++)
            ;
        for (int i = l; i < r; i++) {
            auto [x, t, j, a] = op[i];
            if (a == 1) {
                fen.add(j, 1);
            } else if (a == 2) {
                fen.add(j, -1);
            } else {
                ans[j] = fen.sum(j);
            }
        }
        for (int i = l; i < r; i++) {
            auto [x, t, j, a] = op[i];
            if (a == 1) {
                fen.add(j, -1);
            } else if (a == 2) {
                fen.add(j, 1);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (ans[i] < 0) {
            continue;
        }
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
