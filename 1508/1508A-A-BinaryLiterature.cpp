// url:https://codeforces.com/contest/1508/problem/A
// time:2021-04-16 17:43:46
// name:A-BinaryLiterature

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::string s[3];
        std::cin >> s[0] >> s[1] >> s[2];
        std::string ans;
        for (auto c : {'0', '1'}) {
            for (int i = 0; i < 3; i++) {
                for (int j = i + 1; j < 3; j++) {
                    if (std::count(s[i].begin(), s[i].end(), c) >= n && std::count(s[j].begin(), s[j].end(), c) >= n) {
                        ans.clear();
                        std::vector<int> p{-1}, q{-1};
                        for (int k = 0; k < 2 * n; k++) {
                            if (s[i][k] == c) {
                                p.push_back(k);
                            }
                            if (s[j][k] == c) {
                                q.push_back(k);
                            }
                        }
                        p.push_back(2 * n);
                        q.push_back(2 * n);
                        for (int k = 1; k < int(std::max(p.size(), q.size())); k++) {
                            if (k > 1) {
                                ans += c;
                            }
                            int v = 0;
                            if (k < int(p.size())) {
                                v = std::max(v, p[k] - p[k - 1]);
                            }
                            if (k < int(q.size())) {
                                v = std::max(v, q[k] - q[k - 1]);
                            }
                            ans += std::string(v - 1, c ^ 1);
                        }
                    }
                }
            }
        }
        std::cout << ans << "\n";
    }
    return 0;
}
