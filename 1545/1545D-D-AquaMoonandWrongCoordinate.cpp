//url:https://codeforces.com/contest/1545/problem/D
//time:2021-07-11 18:14:39
//name:D-AquaMoonandWrongCoordinate

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int m, k;
    std::cin >> m >> k;
    
    std::vector a(k, std::vector<int>(m));
    std::vector<int> sum(k);
    std::vector<i64> s2(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
            sum[i] += a[i][j];
            s2[i] += i64(a[i][j]) * a[i][j];
        }
    }
    
    int delta = (sum[k - 1] - sum[0]) / (k - 1);
    
    int y = 1;
    while (sum[y] - sum[y - 1] == delta) {
        y++;
    }
    
    int change = sum[y] - (sum[0] + y * delta);
    
    std::vector<int> x;
    for (int i = 0, j = 0; i < 3; i++) {
        if (j == y) {
            j++;
        }
        x.push_back(j++);
    }
    
    i64 A = 0, B = 0, C = s2[0];
    
    A = ((s2[x[1]] - C) * x[2] - (s2[x[2]] - C) * x[1]) / (x[1] * x[1] * x[2] - x[2] * x[2] * x[1]);
    B = (s2[x[1]] - C - A * x[1] * x[1]) / x[1];
    
    i64 expect = A * y * y + B * y + C;
    
    for (int i = 0; i < m; i++) {
        if (s2[y] - i64(a[y][i]) * a[y][i] + i64(a[y][i] - change) * (a[y][i] - change) == expect) {
            std::cout << y << " " << a[y][i] - change << std::endl;
            return 0;
        }
    }
    
    assert(false);
}
