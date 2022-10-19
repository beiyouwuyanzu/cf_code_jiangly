// url:https://codeforces.com/contest/1746/problem/E2
// time:2022-10-15 18:40:24
// name:E2-Joking(HardVersion)

#include <bits/stdc++.h>

using i64 = long long;

void dfs(int a, int b, int k) {
    if (k == 0) {
        if (a + b > 2) {
            std::cerr << a << " " << b  << "\n";
        }
        return;
    }
    if (a <= 2 * b) {
        int x = (a + 1) / 2, y = b / 2;
        dfs(x + y, a - x, k - 1);
        dfs(a - x + b - y, x, k - 1);
    } else {
        dfs(a, 0, k - 1);
        dfs(b, a, k - 1);
    }
}

int dp[121][121];
int gx[121][121], gy[121][121];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::memset(dp, 0x3f, sizeof(dp));
    
    for (int s = 0; s <= 120; s++) {
        for (int i = 0; i <= s; i++) {
            const int j = s - i;
            if (s <= 2) {
                dp[i][j] = 0;
            } else {
                for (int x = 0; x <= i; x++) {
                    for (int y = 0; y <= j; y++) {
                        int t = std::max(dp[x + y][i - x], dp[i - x + j - y][x]) + 1;
                        if (t < dp[i][j]) {
                            dp[i][j] = t;
                            gx[i][j] = x;
                            gy[i][j] = y;
                        }
                    }
                }
            }
        }
    }
    
    int n;
    std::cin >> n;
    
    std::vector<int> T, F;
    for (int i = 1; i <= n; i++) {
        T.push_back(i);
    }
    while (T.size() + F.size() > 2) {
        int x, y;
        if (T.size() + F.size() <= 120) {
            x = gx[T.size()][F.size()];
            y = gy[T.size()][F.size()];
        } else {
            x = T.size() / 2;
            y = F.size() / 2;
        }
        std::vector T1(T.begin(), T.begin() + x), T0(T.begin() + x, T.end());
        std::vector F1(F.begin(), F.begin() + y), F0(F.begin() + y, F.end());
        
        std::cout << "? " << x + y;
        for (auto x : T1) {
            std::cout << " " << x;
        }
        for (auto x : F1) {
            std::cout << " " << x;
        }
        std::cout << std::endl;
        
        std::string s;
        std::cin >> s;
        
        T = F = {};
        if (s == "YES") {
            for (auto x : T1) {
                T.push_back(x);
            }
            for (auto x : F1) {
                T.push_back(x);
            }
            for (auto x : T0) {
                F.push_back(x);
            }
        } else {
            for (auto x : T0) {
                T.push_back(x);
            }
            for (auto x : F0) {
                T.push_back(x);
            }
            for (auto x : T1) {
                F.push_back(x);
            }
        }
    }
    
    for (auto x : T) {
        std::cout << "! " << x << std::endl;
        std::string s;
        std::cin >> s;
        if (s == ":)") {
            return 0;
        }
    }
    for (auto x : F) {
        std::cout << "! " << x << std::endl;
        std::string s;
        std::cin >> s;
        if (s == ":)") {
            return 0;
        }
    }
    
    return 0;
}
