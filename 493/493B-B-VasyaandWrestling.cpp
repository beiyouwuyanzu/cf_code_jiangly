// url:https://codeforces.com/contest/493/problem/B
// time:2021-06-21 19:29:51
// name:B-VasyaandWrestling

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a, b;
    int last = 0;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (x > 0) {
            a.push_back(x);
            last = 0;
        } else {
            b.push_back(-x);
            last = 1;
        }
    }
    auto suma = std::accumulate(a.begin(), a.end(), 0ll);
    auto sumb = std::accumulate(b.begin(), b.end(), 0ll);
    if (suma > sumb || (suma == sumb && (a > b || (a == b && last == 0)))) {
        std::cout << "first\n";
    } else {
        std::cout << "second\n";
    }
    return 0;
}
