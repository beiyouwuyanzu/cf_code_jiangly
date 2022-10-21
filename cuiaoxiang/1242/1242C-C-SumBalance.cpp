// url:https://codeforces.com/contest/1242/problem/C
// time:2022-04-18 15:48:32
// name:C-SumBalance

// #define LOCAL
#define _USE_MATH_DEFINES
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
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

template <typename A, typename B>
ostream& operator <<(ostream& out, const pair<A, B>& a) {
  out << "(" << a.first << "," << a.second << ")";
  return out;
}
template <typename T, size_t N>
ostream& operator <<(ostream& out, const array<T, N>& a) {
  out << "["; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const set<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const multiset<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}
#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...) 42
#endif
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

template <class T> auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D> auto vect(const T& v, int n, D... m) {
  return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

using int64 = long long;
using int128 = __int128_t;
using ii = pair<int, int>;
#define SZ(x) (int)((x).size())
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
// mt19937 mrand(random_device{}());
// int rnd(int x) { return mrand() % x; }
mt19937_64 mrand(random_device{}());
int64 rnd(int64 x) { return mrand() % x; }
int lg2(int64 x) { return sizeof(int64) * 8 - 1 - __builtin_clzll(x); }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

int main() {
  int n;
  cin >> n;
  vector<vector<int64>> a(n);
  vector<int64> balance(n);
  int64 sum = 0;
  map<int64, ii> pos;
  for (int i = 0; i < n; ++i) {
    int len;
    cin >> len;
    a[i].resize(len);
    for (int j = 0; j < len; ++j) {
      cin >> a[i][j];
      pos[a[i][j]] = {i, j};
      balance[i] += a[i][j];
    }
    sum += balance[i];
  }
  if (sum % n) {
    cout << "No" << '\n';
    return 0;
  }
  sum /= n;
  for (int i = 0; i < n; ++i) balance[i] -= sum;
  trace(balance);

  vector<int> dp(1 << n, -1);
  vector<ii> ans(n);
  function<int(int)> Solve =
    [&](int mask) {
      if (mask == 0) return 1;
      int& ret = dp[mask];
      if (ret >= 0) return ret;
      int i = __builtin_ctz(mask);
      for (int j = 0; j < SZ(a[i]); ++j) {
        bool ok = 0;
        int used = 0;
        for (int ni = i, nj = j; ; ) {
          if (!((mask >> ni) & 1)) break;
          if ((used >> ni) & 1) break;
          used |= 1 << ni;
          int64 target = a[ni][nj] - balance[ni];
          auto it = pos.find(target);
          if (it == pos.end()) break;
          trace(ni, nj, target, it->second);
          tie(ni, nj) = it->second;
          if (ni == i && nj == j) {
            ok = 1;
            break;
          }
        }
        trace(mask, i, j, used, ok);
        if (ok && Solve(mask ^ used)) {
          for (int ni = i, nj = j; ; ) {
            int64 target = a[ni][nj] - balance[ni];
            ii val = {target, ni};
            std::tie(ni, nj) = pos[target];
            ans[ni] = val;
            if (ni == i) break;
          }
          return ret = 1;
        }
      }
      return ret = 0;
    };
  if (!Solve((1 << n) - 1)) {
    cout << "No" << '\n';
  } else {
    cout << "Yes" << '\n';
    for (auto& [x, y] : ans) cout << x << " " << y + 1 << '\n';
  }
  return 0;
}

