// url:https://codeforces.com/contest/1500/problem/A
// time:2021-03-13 12:15:22
// name:A-GoingHome

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int N = 5e6 + 1;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int p[N][2] {};
    std::memset(p, -1, sizeof(p));
    int x = -1;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (p[a[i]][0] == -1) {
            p[a[i]][0] = i;
        } else if (p[a[i]][1] == -1) {
            p[a[i]][1] = i;
            if (x == -1) {
                x = a[i];
            } else {
                std::cout << "YES\n";
                std::cout << p[a[i]][0] + 1 << " " << p[x][0] + 1 << " " << p[a[i]][1] + 1 << " " << p[x][1] + 1 << "\n";
                return 0;
            }
        }
    }
    
    std::pair<int, int> b[N];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int x = a[i] + a[j];
            if (b[x].first == b[x].second) {
                b[x] = {i, j};
            } else if (std::set{b[x].first, b[x].second, i, j}.size() == 4) {
                std::cout << "YES\n";
                std::cout << b[x].first + 1 << " " << b[x].second + 1<< " " << i + 1 << " " << j + 1 << "\n";
                return 0;
            }
        }
    }
    std::cout << "NO\n";
    
    return 0;
}
