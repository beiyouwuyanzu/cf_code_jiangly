// url:https://codeforces.com/contest/706/problem/E
// time:2023-03-15 09:03:08
// name:E-Workingroutine

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, q;
    std::cin >> n >> m >> q;
    
    int N = (n + 1) * (m + 1);
    std::vector<int> v(N);
    
    std::vector<int> l(N), r(N), u(N), d(N);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> v[i * (m + 1) + j];
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            l[i * (m + 1) + j] = i * (m + 1) + (j + m) % (m + 1);
            r[i * (m + 1) + j] = i * (m + 1) + (j + 1) % (m + 1);
            u[i * (m + 1) + j] = (i + n) % (n + 1) * (m + 1) + j;
            d[i * (m + 1) + j] = (i + 1) % (n + 1) * (m + 1) + j;
        }
    }
    
    auto get = [&](int x, int y) {
        int p = 0;
        for (int i = 0; i < x; i++) {
            p = d[p];
        }
        for (int i = 0; i < y; i++) {
            p = r[p];
        }
        return p;
    };
    
    while (q--) {
        int A, B, C, D, h, w;
        std::cin >> A >> B >> C >> D >> h >> w;
        
        int U1 = get(A - 1, B);
        int u1 = d[U1];
        int L1 = get(A, B - 1);
        int l1 = r[L1];
        int D1 = get(A + h, B);
        int d1 = u[D1];
        int R1 = get(A, B + w);
        int r1 = l[R1];
        
        int U2 = get(C - 1, D);
        int u2 = d[U2];
        int L2 = get(C, D - 1);
        int l2 = r[L2];
        int D2 = get(C + h, D);
        int d2 = u[D2];
        int R2 = get(C, D + w);
        int r2 = l[R2];
        
        for (int i = 0; i < h; i++) {
            r[L1] = l2;
            r[L2] = l1;
            l[l2] = L1;
            l[l1] = L2;
            
            l[R1] = r2;
            l[R2] = r1;
            r[r2] = R1;
            r[r1] = R2;
            
            L1 = d[L1];
            l1 = d[l1];
            R1 = d[R1];
            r1 = d[r1];
            L2 = d[L2];
            l2 = d[l2];
            R2 = d[R2];
            r2 = d[r2];
        }
        for (int i = 0; i < w; i++) {
            d[U1] = u2;
            d[U2] = u1;
            u[u2] = U1;
            u[u1] = U2;
            
            u[D1] = d2;
            u[D2] = d1;
            d[d2] = D1;
            d[d1] = D2;
            
            U1 = r[U1];
            u1 = r[u1];
            D1 = r[D1];
            d1 = r[d1];
            U2 = r[U2];
            u2 = r[u2];
            D2 = r[D2];
            d2 = r[d2];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        int p = i * (m + 1);
        for (int j = 1; j <= m; j++) {
            p = r[p];
            std::cout << v[p] << " \n"[j == m];
        }
    }
    
    return 0;
}

