//url:https://codeforces.com/contest/1739/problem/F
//time:2022-09-29 18:39:42
//name:F-KeyboardDesign

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

constexpr int S = 12;

constexpr int N = 5000;

int cnt = 1;
int trie[N][S], fail[N], val[N];

void add(auto a, int c) {
    int p = 1;
    for (auto x : a) {
        if (!trie[p][x]) {
            trie[p][x] = ++cnt;
        }
        p = trie[p][x];
    }
    val[p] += c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::fill(trie[0], trie[0] + S, 1);
    
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; i++) {
        int c;
        std::string s;
        std::cin >> c >> s;
        
        std::array<std::array<int, S>, S> g {};
        const int len = s.length();
        
        for (int j = 0; j < len - 1; j++) {
            g[s[j] - 'a'][s[j + 1] - 'a'] = 1;
            g[s[j + 1] - 'a'][s[j] - 'a'] = 1;
        }
        
        std::array<int, S> deg {};
        for (int i = 0; i < S; i++) {
            deg[i] = std::count(g[i].begin(), g[i].end(), 1);
        }
        bool good = true;
        int start = -1;
        for (int j = 0; j < S; j++) {
            if (deg[j] > 2) {
                good = false;
            }
            if (deg[j] == 1) {
                start = j;
            }
        }
        
        if (!good || start == -1) {
            continue;
        }
        
        std::vector<int> a;
        
        std::function<void(int, int)> dfs = [&](int x, int p) {
            a.push_back(x);
            for (int y = 0; y < 12; y++) {
                if (y != p && g[x][y]) {
                    dfs(y, x);
                }
            }
        };
        dfs(start, -1);
        
        add(a, c);
        std::reverse(a.begin(), a.end());
        add(a, c);
    }
    
    std::queue<int> q;
    q.push(1);
    
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        
        val[x] += val[fail[x]];
        
        for (int i = 0; i < S; i++) {
            if (trie[x][i]) {
                fail[trie[x][i]] = trie[fail[x]][i];
                q.push(trie[x][i]);
            } else {
                trie[x][i] = trie[fail[x]][i];
            }
        }
    }
    
    std::vector dp(1 << S, std::vector<int>(cnt + 1, -inf));
    dp[0][1] = 0;
    
    int ans = 0;
    
    for (int mask = 0; mask < (1 << S); mask++) {
        for (int i = 1; i <= cnt; i++) {
            if (dp[mask][i] < 0) {
                continue;
            }
            ans = std::max(ans, dp[mask][i]);
            for (int j = 0; j < S; j++) {
                if (mask >> j & 1) {
                    continue;
                }
                int nmask = mask | 1 << j;
                int np = trie[i][j];
                dp[nmask][np] = std::max(dp[nmask][np], dp[mask][i] + val[np]);
            }
        }
    }
    
    std::string keybord;
    auto rec = [&](auto self, int mask, int p) {
        if (mask == 0) {
            return;
        }
        for (int i = 0; i < S; i++) {
            if (~mask >> i & 1) {
                continue;
            }
            for (int j = 1; j <= cnt; j++) {
                if (trie[j][i] == p && dp[mask ^ (1 << i)][j] + val[p] == dp[mask][p]) {
                    keybord += 'a' + i;
                    return self(self, mask ^ (1 << i), j);
                }
            }
        }
    };
    
    for (int i = 1; i <= cnt; i++) {
        if (dp[(1 << S) - 1][i] == ans) {
            rec(rec, (1 << S) - 1, i);
            std::cout << keybord << "\n";
            return 0;
        }
    }
    
    return 0;
}
