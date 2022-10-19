// url:https://codeforces.com/contest/500/problem/B
// time:2021-06-22 11:21:29
// name:B-NewYearPermutation

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        std::vector<int> que{i};
        vis[i] = true;
        for (int t = 0; t < int(que.size()); t++) {
            int u = que[t];
            for (int v = 0; v < n; v++) {
                if (s[u][v] == '1' && !vis[v]) {
                    vis[v] = true;
                    que.push_back(v);
                }
            }
        }
        std::sort(que.begin(), que.end());
        std::vector<int> a;
        for (auto j : que) {
            a.push_back(p[j]);
        }
        std::sort(a.begin(), a.end());
        for (int j = 0; j < int(que.size()); j++) {
            p[que[j]] = a[j];
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << p[i] << " \n"[i == n - 1];
    }
    return 0;
}
