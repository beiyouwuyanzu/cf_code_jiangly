// url:https://codeforces.com/contest/1179/problem/B
// time:2022-01-09 12:53:13
// name:B-TolikandHisUncle

#define _USE_MATH_DEFINES
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <complex>
#include <cmath>
#include <numeric>
#include <bitset>
#include <functional>
#include <random>
#include <ctime>

using namespace std;

#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << ": " << arg1 << " |";
  __f(comma + 1, args...);
}

typedef long long int64;
typedef pair<int, int> ii;
const int INF = 1 << 29;
const int MOD = 1e9 + 7;

int main() {
  int n, m;
  cin >> n >> m;
  vector<ii> ret;
  int i;
  for (i = 0; i < n / 2; ++i) {
    for (int j = 0; j < m; ++j) {
      ret.push_back({i, j});
      ret.push_back({n - 1 - i, m - 1 - j});
    }
  }
  if (n % 2) {
    int j;
    for (j = 0; j < m / 2; ++j) {
      ret.push_back({i, j});
      ret.push_back({i, m - 1 - j});
    }
    if (m % 2) ret.push_back({i, j});
  }
  for (auto& [x, y] : ret) {
    cout << x + 1 << " " << y + 1 << '\n';
  }
  return 0;
}

