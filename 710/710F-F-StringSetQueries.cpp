// url:https://codeforces.com/contest/710/problem/F
// time:2021-07-07 23:03:22
// name:F-StringSetQueries

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 30, A = 26;

struct Node {
    int fail;
    int sum;
    int next[A];
    Node() : fail(-1), sum(0) {
        std::memset(next, -1, sizeof(next));
    }
} node[N];

int cnt = 0;
int bin[N];
int nBin = 0;

int newNode() {
    int p = nBin > 0 ? bin[--nBin] : cnt++;
    node[p] = Node();
    return p;
}

struct AC {
    std::vector<int> x;
    AC(AC &&a) : x(std::move(a.x)) {}
    AC(std::vector<std::string> s, std::vector<int> w) {
        x = {newNode(), newNode()};
        std::fill(node[x[0]].next, node[x[0]].next + A, x[1]);
        node[x[1]].fail = x[0];
        
        for (int i = 0; i < int(s.size()); i++) {
            int p = x[1];
            for (int j = 0; j < int(s[i].length()); j++) {
                int c = s[i][j] - 'a';
                if (node[p].next[c] == -1) {
                    int u = newNode();
                    x.push_back(u);
                    node[p].next[c] = u;
                }
                p = node[p].next[c];
            }
            node[p].sum += w[i];
        }
        
        std::queue<int> que;
        que.push(x[1]);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            node[u].sum += node[node[u].fail].sum;
            for (int c = 0; c < A; c++) {
                if (node[u].next[c] == -1) {
                    node[u].next[c] = node[node[u].fail].next[c];
                } else {
                    node[node[u].next[c]].fail = node[node[u].fail].next[c];
                    que.push(node[u].next[c]);
                }
            }
        }
    }
    ~AC() {
        for (auto p : x) {
            bin[nBin++] = p;
        }
    }
    i64 query(const std::string &s) const {
        i64 ans = 0;
        int p = x[1];
        for (int i = 0; i < int(s.length()); i++)  {
            int c = s[i] - 'a';
            p = node[p].next[c];
            ans += node[p].sum;
        }
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int m;
    std::cin >> m;
    
    int n = 0;
    std::vector<std::string> s;
    std::vector<int> w;
    
    std::vector<AC> ac;
    
    for (int i = 0; i < m; i++) {
        int op;
        std::cin >> op;
        std::string t;
        std::cin >> t;
        if (op <= 2) {
            n++;
            s.push_back(t);
            w.push_back(op == 1 ? 1 : -1);
            for (int j = 0; ~n >> j & 1; j++) {
                ac.pop_back();
            }
            int u = n & (n - 1);
            ac.emplace_back(std::vector<std::string>(s.begin() + u, s.end()), std::vector<int>(w.begin() + u, w.end()));
        } else {
            i64 ans = 0;
            for (const auto &x : ac) {
                ans += x.query(t);
            }
            std::cout << ans << std::endl;
        }
    }
    
    return 0;
}
