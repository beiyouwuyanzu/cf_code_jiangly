// url:https://codeforces.com/contest/715/problem/C
// time:2021-07-07 12:14:00
// name:C-DigitTree

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, M;
    std::cin >> n >> M;
    
    int invM = 0;
    while (M % 10 * invM % 10 != 1) {
        invM++;
    }
    
    int inv10 = (1 + i64(M) * (10 - invM)) / 10 % M;
    
    std::vector<int> pw(2 * n);
    pw[0] = 1 % M;
    for (int i = 1; i < 2 * n; i++) {
        pw[i] = 10ll * pw[i - 1] % M;
    }
    std::vector<int> pwInv(2 * n);
    pwInv[0] = 1 % M;
    for (int i = 1; i < 2 * n; i++) {
        pwInv[i] = i64(inv10) * pwInv[i - 1] % M;
    }
    
    std::vector<std::vector<std::pair<int, int>>> e(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    
    i64 ans = 0;
    
    std::vector<int> A(n), B(n), dep(n);
    std::vector<std::map<int, int>> sA(n), sB(n);
    std::function<void(int, int)> dfs = [&](int u, int p) {
        sA[u][A[u]]++;
        sB[u][B[u]]++;
        for (auto [v, w] : e[u]) {
            if (v == p) {
                continue;
            }
            
            dep[v] = dep[u] + 1;
            A[v] = (A[u] + i64(w) * pw[dep[u]]) % M;
            B[v] = (B[u] + i64(w) * pwInv[dep[v]]) % M;
            dfs(v, u);
            
            if (sA[v].size() + sB[v].size() > sA[u].size() + sB[u].size()) {
                std::swap(sA[u], sA[v]);
                std::swap(sB[u], sB[v]);
            }
            
            for (auto [a, c] : sA[v]) {
                int b = (B[u] + i64(A[u] - a + M) * pwInv[2 * dep[u]]) % M;
                if (sB[u].find(b) != sB[u].end()) {
                    ans += i64(sB[u][b]) * c;
                }
            }
            for (auto [b, c] : sB[v]) {
                int a = (A[u] + i64(B[u] - b + M) * pw[2 * dep[u]]) % M;
                if (sA[u].find(a) != sA[u].end()) {
                    ans += i64(sA[u][a]) * c;
                }
            }
            
            for (auto [a, c] : sA[v]) {
                sA[u][a] += c;
            }
            for (auto [b, c] : sB[v]) {
                sB[u][b] += c;
            }
            
            sA[v].clear();
            sB[v].clear();
        }
    };
    dfs(0, -1);
    
    std::cout << ans << "\n";
    
    return 0;
}
