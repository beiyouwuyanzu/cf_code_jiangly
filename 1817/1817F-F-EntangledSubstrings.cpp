// url:https://codeforces.com/contest/1817/problem/F
// time:2023-04-29 21:11:31
// name:F-EntangledSubstrings

#include <bits/stdc++.h>

using i64 = long long;
struct SAM {
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, next{} {}
    };
    std::vector<Node> t;
    SAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    int n = s.size();
    std::vector<int> pos(n + 1);
    pos[0] = 1;
    SAM sam;
    for (int i = 0; i < n; i++) {
        pos[i + 1] = sam.extend(pos[i], s[i] - 'a');
    }
    
    int cnt = sam.t.size();
    std::vector<int> freq(cnt);
    for (int i = 1; i <= n; i++) {
        freq[pos[i]]++;
    }
    
    std::vector<int> o(cnt - 1);
    std::iota(o.begin(), o.end(), 1);
    std::sort(o.begin(), o.end(), [&](int i, int j) {
        return sam.t[i].len < sam.t[j].len;
    });
    
    for (int i = cnt - 2; i; i--) {
        freq[sam.t[o[i]].link] += freq[o[i]];
    }
    
    i64 ans = 0;
    std::vector<int> f(cnt);
    std::vector<std::vector<int>> g(cnt);
    for (int i = cnt - 2; i; i--) {
        int x = o[i];
        f[x] = x;
        for (int j = 0; j < 26; j++) {
            int y = sam.t[x].next[j];
            if (y && freq[x] == freq[y]) {
                f[x] = f[y];
            }
        }
        g[f[x]].push_back(x);
    }
    for (int i = 2; i < cnt; i++) {
        if (!g[i].empty()) {
            std::vector<int> L;
            std::vector<std::pair<int, int>> R;
            for (auto x : g[i]) {
                int l = sam.t[x].len - sam.t[sam.t[x].link].len, r = sam.t[x].len;
                L.push_back(l);
                R.emplace_back(r, l);
            }
            std::sort(L.begin(), L.end());
            std::sort(R.begin(), R.end());
            i64 cnt = 0, sum = 0;
            for (int i = 0; auto l : L) {
                while (i < R.size() && R[i].first < l) {
                    sum += 1LL * R[i].first * R[i].second;
                    cnt += R[i].second;
                    i++;
                }
                ans += l * cnt - sum;
            }
            // std::cerr << ans << "\n";
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}
