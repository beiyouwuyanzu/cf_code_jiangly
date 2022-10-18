//url:https://codeforces.com/contest/827/problem/A
//time:2021-03-31 15:53:16
//name:A-StringReconstruction

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
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
constexpr int N = 2e6;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::string s(N, 'a');
    DSU d(N);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        std::string t;
        std::cin >> t;
        int k;
        std::cin >> k;
        for (int j = 0; j < k; j++) {
            int x;
            std::cin >> x;
            x--;
            mx = std::max(mx, int(t.length()) + x);
            int y = d.leader(x);
            while (y < x + int(t.length())) {
                s[y] = t[y - x];
                d.merge(y + 1, y);
                y = d.leader(y);
            }
        }
    }
    s.resize(mx);
    std::cout << s << "\n";
    return 0;
}

