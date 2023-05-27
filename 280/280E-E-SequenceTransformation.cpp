// url:https://codeforces.com/contest/280/problem/E
// time:2023-04-30 11:22:08
// name:E-SequenceTransformation

#include <bits/stdc++.h>

using i64 = long long;

constexpr double eps = 1E-8;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q, a, b;
    std::cin >> n >> q >> a >> b;
    
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
        x[i] -= a * i + 1;
    }
    
    q -= a * (n - 1) + 1;
    b -= a;
    
    std::vector<std::array<double, 2>> f;
    f.push_back({0, 0});
    if (q) {
        f.push_back({q, 0});
    }
    
    std::cout << std::fixed << std::setprecision(10);
    double f0 = 0;
    std::vector<double> g(n);
    for (int i = 0; i < n; i++) {
        f0 += 1. * x[i] * x[i];
        for (auto &[X, y] : f) {
            y += 2 * (X - x[i]);
        }
        int pos = f.size();
        for (int j = 0; j < f.size(); j++) {
            if (f[j][1] > 0) {
                if (j == 0 || f[j][0] - f[j - 1][0] < eps) {
                    g[i] = f[j][0];
                } else {
                    double x = (f[j][0] - f[j - 1][0]) / (f[j][1] - f[j - 1][1]) * -f[j - 1][1] + f[j - 1][0];
                    g[i] = x;
                }
                pos = j;
                break;
            } else {
                g[i] = f[j][0];
            }
        }
        // std::cerr << "g : " << g[i] << "\n";
        if (b && i < n - 1) {
            bool ok = false;
            f.insert(f.begin() + pos, std::array{g[i], 0.});
            f.insert(f.begin() + pos, std::array{g[i], 0.});
            for (int j = pos + 1; j < f.size(); j++) {
                f[j][0] += b;
            }
            while (f.size() > 1 && f.back()[0] > q) {
                if (f[f.size() - 2][0] > q) {
                    f.pop_back();
                } else {
                    auto a = f[f.size() - 2];
                    auto b = f.back();
                    auto k = (b[1] - a[1]) / (b[0] - a[0]);
                    f.back() = {q, a[1] + (q - a[0]) * k};
                    break;
                }
            }
        }
        // for (auto [x, y] : f) {
        //     std::cerr << "(" << x << ", " << y << ") ";
        // }
        // std::cerr << "\n";
    }
    
    for (int i = n - 2; i >= 0; i--) {
        if (g[i] > g[i + 1]) {
            g[i] = g[i + 1];
        } else if (g[i] < g[i + 1] - b) {
            g[i] = g[i + 1] - b;
        }
    }
    
    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (g[i] - x[i]) * (g[i] - x[i]);
        g[i] += 1 + a * i;
        std::cout << g[i] << " \n"[i == n - 1];
    }
    std::cout << ans << "\n";
    
    return 0;
}
