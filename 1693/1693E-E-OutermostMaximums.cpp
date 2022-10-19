// url:https://codeforces.com/contest/1693/problem/E
// time:2022-06-16 20:42:01
// name:E-OutermostMaximums

#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
struct Fenwick {
    int n;
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
    
    std::vector<int> a(n), l(n + 1, n), r(n + 1, -1);
    std::vector<std::vector<int>> p(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] > 0) {
            l[a[i]] = std::min(l[a[i]], i);
            r[a[i]] = std::max(r[a[i]], i);
            p[a[i]].push_back(i);
        }
    }
    
    Fenwick<int> fen(n);
    
    int L = 0, R = n - 1;
    
    i64 ans = 0;
    
    for (int x = n; x > 0; x--) {
        if (l[x] > r[x]) {
            continue;
        }
        
        for (auto i : p[x]) {
            fen.add(i, 1);
        }
        
        int nL = std::min(l[x], R + 1);
        int nR = std::max(r[x], L - 1);
        L = nL;
        R = nR;
        
        ans += fen.rangeSum(L, R + 1);
    }
    
    std::cout << ans << "\n";
    
    
    return 0;
}

