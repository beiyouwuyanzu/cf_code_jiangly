// url:https://codeforces.com/contest/717/problem/D
// time:2023-03-15 16:23:45
// name:D-Dexterina’sLab

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, x;
    std::cin >> n >> x;
    
    int N = 1;
    while (N <= x) {
        N *= 2;
    }
    
    std::vector<double> p(N);
    for (int i = 0; i <= x; i++) {
        std::cin >> p[i];
    }
    
    for (int i = 1; i < N; i *= 2) {
        for (int j = 0; j < N; j += 2 * i) {
            for (int k = 0; k < i; k++) {
                double a = p[j + k];
                double b = p[i + j + k];
                p[j + k] = a + b;
                p[i + j + k] = a - b;
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        p[i] = std::pow(p[i], n);
    }
    
    for (int i = 1; i < N; i *= 2) {
        for (int j = 0; j < N; j += 2 * i) {
            for (int k = 0; k < i; k++) {
                double a = p[j + k] / 2;
                double b = p[i + j + k] / 2;
                p[j + k] = a + b;
                p[i + j + k] = a - b;
            }
        }
    }
    
    auto ans = 1 - p[0];
    std::cout << std::fixed << std::setprecision(10) << ans << "\n";
    
    return 0;
}

