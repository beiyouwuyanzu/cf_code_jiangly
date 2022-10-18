//url:https://codeforces.com/contest/827/problem/C
//time:2021-03-31 15:38:29
//name:C-DNAEvolution

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n = 0) : n(n), a(n) {}
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
Fenwick<int> t[4][11][10];
int id(char ch) {
    if (ch == 'A') {
        return 0;
    } else if (ch == 'T') {
        return 1;
    } else if (ch == 'C') {
        return 2;
    } else {
        return 3;
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    int n = s.length();
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 10; j++) {
            for (int k = 0; k < j; k++) {
                t[i][j][k] = Fenwick<int>(n);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int x = id(s[i]);
        for (int j = 1; j <= 10; j++) {
            t[x][j][i % j].add(i, 1);
        }
    }
    int q;
    std::cin >> q;
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int i;
            char c;
            std::cin >> i >> c;
            i--;
            int x = id(s[i]);
            int y = id(c);
            for (int j = 1; j <= 10; j++) {
                t[x][j][i % j].add(i, -1);
                t[y][j][i % j].add(i, 1);
            }
            s[i] = c;
        } else {
            int l, r;
            std::string e;
            std::cin >> l >> r >> e;
            l--;
            int ans = 0;
            int j = e.length();
            for (int k = 0; k < j; k++) {
                ans += t[id(e[k])][j][(l + k) % j].rangeSum(l, r);
            }
            std::cout << ans << "\n";
        }
    }
    return 0;
}

