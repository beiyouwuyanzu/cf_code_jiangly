//url:https://codeforces.com/contest/702/problem/E
//time:2021-07-12 19:22:19
//name:E-AnalysisofPathesinFunctionalGraph

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    i64 k;
    std::cin >> n >> k;
    
    std::vector<int> f(n), mn(n);
    std::vector<i64> sum(n);
    for (int i = 0; i < n; i++) {
        std::cin >> f[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> mn[i];
        sum[i] = mn[i];
    }
    
    std::vector<int> c(n), cmn(n, 1e9);
    std::iota(c.begin(), c.end(), 0);
    std::vector<i64> csum(n);
    
    for (; k > 0; k /= 2) {
        if (k & 1) {
            for (int i = 0; i < n; i++) {
                cmn[i] = std::min(cmn[i], mn[c[i]]);
                csum[i] += sum[c[i]];
                c[i] = f[c[i]];
            }
        }
        
        std::vector<int> nf(n), nmn(n);
        std::vector<i64> nsum(n);
        
        for (int i = 0; i < n; i++) {
            nmn[i] = std::min(mn[i], mn[f[i]]);
            nsum[i] = sum[i] + sum[f[i]];
            nf[i] = f[f[i]];
        }
        
        mn = std::move(nmn);
        sum = std::move(nsum);
        f = std::move(nf);
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << csum[i] << " " << cmn[i] << "\n";
    }
    
    return 0;
}
