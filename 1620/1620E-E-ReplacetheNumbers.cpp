// url:https://codeforces.com/contest/1620/problem/E
// time:2021-12-18 19:56:49
// name:E-ReplacetheNumbers

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5E5 + 1;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int q;
    std::cin >> q;
    
    std::vector<int> op(q), x(q), y(q);
    for (int i = 0; i < q; i++) {
        std::cin >> op[i] >> x[i];
        if (op[i] == 2) {
            std::cin >> y[i];
        }
    }
    
    std::vector<int> ans;
    std::vector<int> f(N);
    std::iota(f.begin(), f.end(), 0);
    for (int i = q - 1; i >= 0; i--) {
        if (op[i] == 1) {
            ans.push_back(f[x[i]]);
        } else {
            f[x[i]] = f[y[i]];
        }
    }
    
    std::reverse(ans.begin(), ans.end());
    for (int i = 0; i < int(ans.size()); i++) {
        std::cout << ans[i] << " \n"[i == int(ans.size()) - 1];
    }
    
    return 0;
}

