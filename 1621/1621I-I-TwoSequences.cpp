// url:https://codeforces.com/contest/1621/problem/I
// time:2022-01-04 11:20:13
// name:I-TwoSequences

#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<std::vector<int>> b{a};
    while (!std::is_sorted(b.back().begin(), b.back().end(), std::greater())) {
        auto v = b.back();
        
        std::vector<int> f(n + 1), g(n + 1);
        for (int i = 1, j = 0, k = 0; i <= n; ) {
            if ((i - j) % (i - k) == 0) {
                f[i] = k;
                g[i] = j;
            } else {
                f[i] = f[k] + i - k;
                g[i] = g[k] + i - k;
            }
            if (i == n || v[i] < v[k]) {
                while (j <= k) {
                    j += i - k;
                }
                k = j;
                i = k + 1;
            } else if (v[i] == v[k]) {
                i++;
                k++;
            } else {
                k = j;
                i++;
            }
        }
        
        for (int i = n - 1, j = -1; i >= 0; i--) {
            f[i + 1] = j == i + 1 ? f[i + 1] : g[i + 1];
            j = f[i + 1];
        }
        
        for (int i = 1, j = 0; i <= n; i++) {
            for (int k = f[i]; k < i && j < n; k++) {
                v[j++] = b.back()[k];
            }
        }
        
        b.push_back(v);
    }
    
    int q;
    std::cin >> q;
    
    while (q--) {
        int i, j;
        std::cin >> i >> j;
        j--;
        i = std::min(i, int(b.size()) - 1);
        std::cout << b[i][j] << "\n";
    }
    
    return 0;
}

