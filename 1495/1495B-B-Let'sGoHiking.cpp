// url:https://codeforces.com/contest/1495/problem/B
// time:2021-03-10 15:43:04
// name:B-Let'sGoHiking

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);;
    int n;
    std::cin >> n;
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    std::vector<int> l(n), r(n);
    for (int i = 1; i < n; i++) {
        l[i] = x[i] > x[i - 1] ? l[i - 1] + 1 : 0;
    }
    for (int i = n - 2; i >= 0; i--) {
        r[i] = x[i] > x[i + 1] ? r[i + 1] + 1 : 0;
    }
    int s = std::max_element(l.begin(), l.end()) - l.begin();
    for (int i = 0; i < n; i++) {
        if (i != s && std::max(l[i], r[i]) >= l[s]) {
            std::cout << "0\n";
            return 0;
        }
    }
    std::cout << (l[s] == r[s] && l[s] % 2 == 0) << "\n";
    return 0;
}

