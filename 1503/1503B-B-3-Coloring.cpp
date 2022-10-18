//url:https://codeforces.com/contest/1503/problem/B
//time:2021-04-03 17:47:01
//name:B-3-Coloring

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a, b;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) % 2 == 0) {
                a.emplace_back(i, j);
            } else {
                b.emplace_back(i, j);
            }
        }
    }
    int i = 0, j = 0;
    while (i < int(a.size()) && j < int(b.size())) {
        int x;
        std::cin >> x;
        if (x != 1) {
            std::cout << "1 " << a[i].first + 1 << " " << a[i].second + 1 << std::endl;
            i++;
        } else {
            std::cout << "2 " << b[j].first + 1 << " " << b[j].second + 1 << std::endl;
            j++;
        }
    }
    while (i < int(a.size())) {
        int x;
        std::cin >> x;
        std::cout << (x != 1 ? 1 : 3) << " " << a[i].first + 1 << " " << a[i].second + 1 << std::endl;
        i++;
    }
    while (j < int(b.size())) {
        int x;
        std::cin >> x;
        std::cout << (x != 2 ? 2 : 3) << " " << b[j].first + 1 << " " << b[j].second + 1 << std::endl;
        j++;
    }
    return 0;
}

