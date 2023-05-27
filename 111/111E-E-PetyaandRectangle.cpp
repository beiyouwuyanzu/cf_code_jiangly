// url:https://codeforces.com/contest/111/problem/E
// time:2023-04-28 12:46:46
// name:E-PetyaandRectangle

#include <bits/stdc++.h>

using i64 = long long;

void g(std::vector<std::pair<int, int>> &ans, int x1, int y1, int x2, int y2, int tx, int ty);

void f(std::vector<std::pair<int, int>> &ans, int x1, int y1, int x2, int y2, int tx, int ty) {
    if (x1 > x2 || y1 > y2) {
        return;
    }
    if (y1 == y2) {
        ans.emplace_back(tx ? x2 : x1, y1);
        return;
    }
    if (tx) {
        for (int i = x2; i >= x1; i--) {
            ans.emplace_back(i, ty ? y2 : y1);
        }
    } else {
        for (int i = x1; i <= x2; i++) {
            ans.emplace_back(i, ty ? y2 : y1);
        }
    }
    if (ty) {
        y2--;
    } else {
        y1++;
    }
    g(ans, x1, y1, x2, y2, !tx, ty);
}

void g(std::vector<std::pair<int, int>> &ans, int x1, int y1, int x2, int y2, int tx, int ty) {
    if (x1 > x2 || y1 > y2) {
        return;
    }
    if (x1 == x2) {
        if (ty == 0) {
            for (int i = y1; i <= y2; i++) {
                ans.emplace_back(x1, i);
            }
        } else {
            for (int i = y2; i >= y1; i--) {
                ans.emplace_back(x1, i);
            }
        }
        return;
    }
    if (y1 == y2) {
        if (tx == 0) {
            for (int i = x1; i <= x2; i++) {
                ans.emplace_back(i, y1);
            }
        } else {
            for (int i = x2; i >= x1; i--) {
                ans.emplace_back(i, y1);
            }
        }
        return;
    }
    if (x1 + 1 == x2 && y1 + 1 == y2) {
        ans.emplace_back(tx ? x2 : x1, ty ? y2 : y1);
        ans.emplace_back(tx ? x1 : x2, ty ? y2 : y1);
        ans.emplace_back(tx ? x1 : x2, ty ? y1 : y2);
        return;
    }
    if (x2 - x1 > y2 - y1) {
        for (int v = 0; v < 2; v++) {
            if (ty ^ v) {
                for (int i = y2; i >= y1; i--) {
                    ans.emplace_back(tx ? x2 : x1, i);
                }
            } else {
                for (int i = y1; i <= y2; i++) {
                    ans.emplace_back(tx ? x2 : x1, i);
                }
            }
            if (tx) {
                x2--;
            } else {
                x1++;
            }
        }
        g(ans, x1, y1, x2, y2, tx, ty);
    } else {
        for (int v = 0; v < 2; v++) {
            if (tx ^ v) {
                for (int i = x2; i >= x1; i--) {
                    ans.emplace_back(i, ty ? y2 : y1);
                }
            } else {
                for (int i = x1; i <= x2; i++) {
                    ans.emplace_back(i, ty ? y2 : y1);
                }
            }
            if (ty) {
                y2--;
            } else {
                y1++;
            }
        }
        g(ans, x1, y1, x2, y2, tx, ty);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, x1, y1, x2, y2;
    std::cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    
    std::vector<std::pair<int, int>> ans;
    
    int req;
    
    if (n * m % 2 == 0) {
        if ((x1 + y1 + x2 + y2) % 2 == 0) {
            req = n * m - 1;
        } else {
            req = n * m;
        }
    } else {
        req = n * m - ((x1 + y1) % 2) - ((x2 + y2) % 2);
    }
    
    for (int fxy = 0; fxy < 2; fxy++) {
        for (int fx = 0; fx < 2; fx++) {
            for (int fy = 0; fy < 2; fy++) {
                for (int rev = 0; rev < 2; rev++) {
                    
                    int N = n, M = m, X1 = x1, Y1 = y1, X2 = x2, Y2 = y2;
                    
                    if (fxy) {
                        std::swap(N, M);
                        std::swap(X1, Y1);
                        std::swap(X2, Y2);
                    }
                    
                    if (fy) {
                        Y1 = M + 1 - Y1;
                        Y2 = M + 1 - Y2;
                    }
                    
                    if (fx) {
                        X1 = N + 1 - X1;
                        X2 = N + 1 - X2;
                    }
                    
                    if (rev) {
                        std::swap(X1, X2);
                        std::swap(Y1, Y2);
                    }
                    
                    if (ans.size() != req) {
                        ans.clear();
                        f(ans, 1, 1, X1, Y1, 1, 1);
                        // std::cerr << ans.size() << " ";
                        g(ans, X1 + 1, 1, N, Y1, 0, 0);
                        // std::cerr << ans.size() << " ";
                        f(ans, 1, Y1 + 1, N, Y2 - 1, 1, 0);
                        // std::cerr << ans.size() << " ";
                        g(ans, X2 + 1, Y2, N, M, 1, 0);
                        // std::cerr << ans.size() << " ";
                        f(ans, 1, Y2, X2, M, 1, 1);
                        // std::cerr << ans.size() << "\n";
                    }
                    if (ans.size() != req && Y1 + 1 < Y2) {
                        ans.clear();
                        f(ans, 1, 1, X1, Y1, 1, 1);
                        // std::cerr << ans.size() << " ";
                        g(ans, X1 + 1, 1, N, Y1, 0, 0);
                        // std::cerr << ans.size() << " ";
                        g(ans, 1, Y1 + 1, N, Y2 - 1, 1, 0);
                        // std::cerr << ans.size() << " ";
                        g(ans, 1, Y2, X2 - 1, M, 0, 0);
                        // std::cerr << ans.size() << " ";
                        f(ans, X2, Y2, N, M, 0, 1);
                        // std::cerr << ans.size() << "\n";
                    }
                    
                    if (ans.size() != req) {
                        continue;
                    }
                    if (rev) {
                        std::reverse(ans.begin(), ans.end());
                    }
                    if (fx) {
                        for (auto &[x, y] : ans) {
                            x = N + 1 - x;
                        }
                    }
                    if (fy) {
                        for (auto &[x, y] : ans) {
                            y = M + 1 - y;
                        }
                    }
                    if (fxy) {
                        for (auto &[x, y] : ans) {
                            std::swap(x, y);
                        }
                    }
                    
                    std::cout << ans.size() << "\n";
                    for (auto [x, y] : ans) {
                        std::cout << x << " " << y << "\n";
                    }
                    return 0;
                }
            }
        }
    }
    
    return 0;
}
