// url:https://codeforces.com/contest/612/problem/C
// time:2023-04-24 10:31:22
// name:C-ReplaceToMakeRegularBracketSequence

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::map<char, int> id;
    id['('] = 1;
    id[')'] = -1;
    id['['] = 2;
    id[']'] = -2;
    id['{'] = 3;
    id['}'] = -3;
    id['<'] = 4;
    id['>'] = -4;
    
    std::string s;
    std::cin >> s;
    
    int n = s.size();
    
    int ans = 0;
    std::vector<int> stk;
    for (auto c : s) {
        if (id[c] > 0) {
            stk.push_back(id[c]);
        } else if (stk.empty()) {
            std::cout << "Impossible" << "\n";
            return 0;
        } else {
            if (stk.back() != -id[c]) {
                ans += 1;
            }
            stk.pop_back();
        }
    }
    if (!stk.empty()) {
        std::cout << "Impossible" << "\n";
        return 0;
    }
    std::cout << ans << "\n";
    
    return 0;
}
