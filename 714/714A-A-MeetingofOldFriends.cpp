// url:https://codeforces.com/contest/714/problem/A
// time:2021-07-07 17:11:12
// name:A-MeetingofOldFriends

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 l1, r1, l2, r2, k;
    std::cin >> l1 >> r1 >> l2 >> r2 >> k;
    
    i64 ans = 0;
    ans += std::max(0LL, std::min(r1, r2) - std::max(l1, l2) + 1);
    ans -= (l1 <= k && k <= r1 && l2 <= k && k <= r2);
    
    std::cout << ans << "\n";
    
    return 0;
}
