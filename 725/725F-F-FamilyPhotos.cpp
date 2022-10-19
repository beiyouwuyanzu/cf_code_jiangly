// url:https://codeforces.com/contest/725/problem/F
// time:2021-07-06 22:36:37
// name:F-FamilyPhotos

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    i64 sum = 0;
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        int a1, b1, a2, b2;
        std::cin >> a1 >> b1 >> a2 >> b2;
        if (a1 - b2 < 0 && b1 - a2 < 0) {
            continue;
        }
        int x = a1 + b1;
        int y = a2 + b2;
        sum += a1 - b1 + a2 - b2;
        if (x >= y) {
            v.push_back(x);
            v.push_back(y);
        } else if (a1 - b2 >= 0) {
            sum += x - y;
        } else {
            sum += y - x;
        }
    }
    
    std::sort(v.begin(), v.end(), std::greater<>());
    for (int i = 0; i < int(v.size()); i += 2) {
        sum += v[i];
        sum -= v[i + 1];
    }
    
    sum /= 2;
    std::cout << sum << "\n";
    
    return 0;
}
