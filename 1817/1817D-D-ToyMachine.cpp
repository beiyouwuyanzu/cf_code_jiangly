// url:https://codeforces.com/contest/1817/problem/D
// time:2023-04-29 20:38:21
// name:D-ToyMachine

#include <bits/stdc++.h>

using i64 = long long;

using namespace std::literals::string_literals;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    n -= 2;
    
    std::string s;
    if (k == (n + 1) / 2) {
        s = "DL"s;
    } else if (k < (n + 1) / 2) {
        for (int i = 0; i < k - 1; i++) {
            s += "LDRU";
        }
        s += "L";
    } else {
        for (int i = 0; i < n - k; i++) {
            s += "RDLU";
        }
        for (int i = 0; i < n; i++) {
            s += "LDLU";
        }
        s += "RDL";
    }
    std::cout << s << "\n";
    
    return 0;
}
