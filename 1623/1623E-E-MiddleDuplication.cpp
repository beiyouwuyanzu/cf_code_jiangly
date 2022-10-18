//url:https://codeforces.com/contest/1623/problem/E
//time:2021-12-28 17:03:08
//name:E-MiddleDuplication

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }
    
    std::vector<int> in(n), out(n), p(n), dep(n), pos(n);
    p[0] = -1;
    
    std::vector<int> m;
    
    int clk = 0;
    std::function<void(int)> dfs = [&](int u) {
        in[u] = clk;
        if (l[u] != -1) {
            p[l[u]] = u;
            dep[l[u]] = dep[u] + 1;
            dfs(l[u]);
        }
        pos[u] = clk++;
        m.push_back(u);
        if (r[u] != -1) {
            p[r[u]] = u;
            dep[r[u]] = dep[u] + 1;
            dfs(r[u]);
        }
        out[u] = clk;
    };
    dfs(0);
    
    std::vector<int> dup(n, -1);
    
    std::vector<int> stk;
    
    for (int i = 0, j = 0, r = 0; i < n; i++) {
        int u = m[i];
        while (j < n && s[u] == s[m[j]]) {
            j++;
        }
        if (i < r) {
            dup[u] = 0;
        }
        while (!stk.empty() && pos[u] >= out[stk.back()]) {
            stk.pop_back();
        }
        if (dup[u] != -1) {
            continue;
        }
        int step = dep[u] - (stk.empty() ? -1 : dep[stk.back()]);
        if (j == n || s[m[j]] < s[u] || step > k) {
            dup[u] = 0;
            r = out[u];
        } else {
            k -= step;
            for (int x = u; x != -1 && dup[x] == -1; x = p[x]) {
                dup[x] = 1;
                stk.push_back(x);
            }
            std::reverse(stk.end() - step, stk.end());
        }
    }
    
    std::string ans;
    for (auto u : m) {
        ans += s[u];
        if (dup[u]) {
            ans += s[u];
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

