// url:https://codeforces.com/contest/1616/problem/E
// time:2021-12-29 19:07:01
// name:E-LexicographicallySmallEnough

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

void solve() {
    int n;
    std::cin >> n;
    
    std::string s, t;
    std::cin >> s >> t;
    
    std::vector<int> a[26], b[26];
    for (int i = 0; i < n; i++) {
        a[s[i] - 'a'].push_back(i);
        b[t[i] - 'a'].push_back(i);
    }
    
    int c[26] = {};
    std::vector<int> p(n, -1);
    for (int x = 0; x < 26; x++) {
        for (int i = 0; i < std::min(int(a[x].size()), int(b[x].size())); i++) {
            p[b[x][i]] = a[x][i];
        }
    }
    
    i64 ans = 1E18;
    
    Fenwick<int> fen(n);
    i64 cur = 0;
    
    for (int i = 0; i < n; i++) {
        for (int x = 0; x < t[i] - 'a'; x++) {
            if (c[x] < int(a[x].size())) {
                i64 res = cur;
                res += a[x][c[x]] - i;
                res += fen.rangeSum(a[x][c[x]], n);
                ans = std::min(ans, res);
            }
        }
        
        if (p[i] == -1) {
            break;
        }
        c[t[i] - 'a']++;
        cur += p[i] - i;
        cur += fen.rangeSum(p[i], n);
        fen.add(p[i], 1);
    }
    
    if (ans == 1E18) {
        ans = -1;
    }
    std::cout << ans << "\n";
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

