//url:https://codeforces.com/contest/1685/problem/C
//time:2022-05-25 21:08:33
//name:C-BringBalance

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> a(2 * n + 1);
    for (int i = 0; i < 2 * n; i++) {
        a[i + 1] = a[i] + (s[i] == '(' ? 1 : -1);
    }
    
    if (*std::min_element(a.begin(), a.end()) == 0) {
        std::cout << "0\n";
        return;
    }
    
    int L = 0, R = 2 * n;
    while (a[L] >= 0) {
        L++;
    }
    while (a[R] >= 0) {
        R--;
    }
    
    std::vector<int> lc(2 * n + 1, -1), rc(2 * n + 1, -1);
    std::vector<int> stk;
    
    for (int i = 0; i <= 2 * n; i++) {
        while (!stk.empty() && a[i] > a[stk.back()]) {
            int x = stk.back();
            rc[x] = lc[i];
            lc[i] = x;
            stk.pop_back();
        }
        stk.push_back(i);
    }
    while (stk.size() > 1) {
        int x = stk.back();
        stk.pop_back();
        rc[stk.back()] = x;
    }
    
    int ansL = -1, ansR = -1;
    
    std::function<std::array<int, 2>(int, int, int)> solve =
        [&](int x, int l, int r) -> std::array<int, 2> {
            if (x == -1) {
                return {-1, -1};
            }
            auto [l1, r1] = solve(lc[x], l, x - 1);
            auto [l2, r2] = solve(rc[x], x + 1, r);
            int xl = -1, xr = -1;
            for (auto l : {l1, l2, x}) {
                if (l != -1 && l < L && (xl == -1 || a[l] > a[xl])) {
                    xl = l;
                }
            }
            for (auto r : {r1, r2, x}) {
                if (r != -1 && r > R && (xr == -1 || a[r] > a[xr])) {
                    xr = r;
                }
            }
            if (xl != -1 && xr != -1 && a[xl] + a[xr] >= a[x]) {
                ansL = xl;
                ansR = xr;
            }
            return {xl, xr};
        };
    
    solve(stk[0], 0, n);
    
    if (ansL != -1) {
        std::cout << "1\n";
        std::cout << ansL + 1 << " " << ansR << "\n";
        return;
    }
    
    int j = std::max_element(a.begin(), a.end()) - a.begin();
    std::cout << "2\n";
    std::cout << "1 " << j << "\n";
    std::cout << j + 1 << " " << 2 * n << "\n";
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
