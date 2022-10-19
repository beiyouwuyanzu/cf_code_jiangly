// url:https://codeforces.com/contest/495/problem/A
// time:2021-06-21 19:14:20
// name:A-DigitalCounter

#include <bits/stdc++.h>
constexpr int A[] = {2, 7, 2, 3, 3, 4, 2, 5, 1, 2};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::cout << A[n / 10] * A[n % 10] << "\n";
    return 0;
}
