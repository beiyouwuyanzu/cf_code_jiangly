//url:https://codeforces.com/contest/1738/problem/C
//time:2022-09-30 17:52:21
//name:C-EvenNumberAddicts

#include <bits/stdc++.h>

using i64 = long long;

int f[101][101][2][2];

int rec(int c0, int c1, int x, int p) {
    if (f[c0][c1][x][p] != -1) {
        return f[c0][c1][x][p];
    }
    int &res = f[c0][c1][x][p];
    res = 0;
    if (!c0 && !c1) {
        res = !x ^ p;
    } else {
        if (c0) {
            res |= !rec(c0 - 1, c1, x, !p);
        }
        if (c1) {
            res |= !rec(c0, c1 - 1, x ^ !p, !p);
        }
    }
    return res;
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    int cnt[2] = {};
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i] &= 1;
        cnt[a[i]]++;
    }
    
    std::cout << (rec(cnt[0], cnt[1], 0, 0) ? "Alice" : "Bob") << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::memset(f, -1, sizeof(f));
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
