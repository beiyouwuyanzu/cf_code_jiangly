//url:https://codeforces.com/contest/1735/problem/C
//time:2022-10-04 13:44:41
//name:C-PhaseShift

#include <bits/stdc++.h>

using i64 = long long;
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    std::vector to(26, -1), from(26, -1);
    
    std::string t;
    
    DSU dsu(26);
    
    for (auto ch : s) {
        int x = ch - 'a';
        
        if (to[x] != -1) {
            t += 'a' + to[x];
            continue;
        }
        
        for (int y = 0; y < 26; y++) {
            if (from[y] != -1) {
                continue;
            }
            if (dsu.same(x, y) && dsu.size(x) < 26) {
                continue;
            }
            to[x] = y;
            from[y] = x;
            dsu.merge(x, y);
            t += 'a' + to[x];
            break;
        }
    }
    
    std::cout << t << "\n";
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
