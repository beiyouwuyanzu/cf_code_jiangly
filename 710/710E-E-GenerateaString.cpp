// url:https://codeforces.com/contest/710/problem/E
// time:2021-07-07 22:28:28
// name:E-GenerateaString

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, x, y;
    std::cin >> n >> x >> y;
    
    std::vector<i64> f(2 * n, -1);
    std::queue<std::pair<i64, int>> q1, q2;
    q1.emplace(0, 0);
    
    while (!q1.empty() || !q2.empty()) {
        i64 d;
        int u;
        if (!q1.empty() && (q2.empty() || q1.front() < q2.front())) {
            std::tie(d, u) = q1.front();
            q1.pop();
        } else {
            std::tie(d, u) = q2.front();
            q2.pop();
        }
        if (f[u] >= 0) {
            continue;
        }
        f[u] = d;
        if (u > 0) {
            q1.emplace(d + x, u - 1);
        }
        if (u + 1 < 2 * n) {
            q1.emplace(d + x, u + 1);
        }
        if (u < n) {
            q2.emplace(d + y, 2 * u);
        }
    }

    std::cout << f[n] << "\n";
    
    return 0;
}
