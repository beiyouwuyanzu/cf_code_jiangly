// url:https://codeforces.com/contest/497/problem/B
// time:2021-06-20 20:36:06
// name:B-TennisGame

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> sum[2];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    std::vector<int> tim[2];
    for (int x = 0; x < 2; x++) {
        sum[x].resize(n + 1);
        tim[x].resize(n + 2, n + 1);
        for (int i = 0; i < n; i++) {
            sum[x][i + 1] = sum[x][i] + (a[i] == x);
        }
        for (int i = n; i >= 0; i--) {
            tim[x][sum[x][i]] = i;
        }
    }
    std::vector<std::pair<int, int>> ans;
    for (int t = 1; t <= n; t++) {
        int win[2] = {};
        int cur = 0;
        while (true) {
            int nxt[2];
            for (int x = 0; x < 2; x++) {
                nxt[x] = tim[x][std::min(n + 1, sum[x][cur] + t)];
            }
            int mnxt = std::min(nxt[0], nxt[1]);
            cur = mnxt;
            if (cur > n) {
                break;
            }
            assert(nxt[0] != nxt[1]);
            int winner = nxt[1] < nxt[0];
            win[winner]++;
            if (cur == n) {
                if (win[winner] > win[!winner]) {
                    ans.emplace_back(win[winner], t);
                }
                break;
            }
        }
    }
    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << "\n";
    for (auto [s, t] : ans) {
        std::cout << s << " " << t << "\n";
    }
    return 0;
}
