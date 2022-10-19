// url:https://codeforces.com/contest/499/problem/B
// time:2021-06-21 22:18:04
// name:B-Lecture

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::map<std::string, std::string> dic;
    for (int i = 0; i < m; i++) {
        std::string a, b;
        std::cin >> a >> b;
        if (a.size() <= b.size()) {
            dic[a] = a;
        } else {
            dic[a] = b;
        }
    }
    for (int i = 1; i <= n; i++) {
        std::string a;
        std::cin >> a;
        std::cout << dic[a] << " \n"[i == n];
    }
    return 0;
}
