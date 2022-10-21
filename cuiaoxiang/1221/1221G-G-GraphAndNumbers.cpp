// url:https://codeforces.com/contest/1221/problem/G
// time:2022-04-04 15:35:57
// name:G-GraphAndNumbers

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
  int n, m;
  cin >> n >> m;

  vector<int64> g(n);
  vector<vector<int>> a(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    a[x].push_back(y);
    a[y].push_back(x);
    g[x] |= 1LL << y;
    g[y] |= 1LL << x;
  }
  for (int i = 0; i < n; ++i) g[i] |= 1LL << i;

  trace(a);
  int I = 0, C = 0;
  for (int i = 0; i < n; ++i) I += SZ(a[i]) == 0;
  vector<int> color(n);
  bool bipartite = 1;
  function<void(int)> dfs =
    [&](int u) {
      for (auto& v : a[u]) {
        if (!color[v]) {
          color[v] = 3 - color[u];
          dfs(v);
        } else {
          if (color[u] == color[v]) bipartite = false;
        }
      }
    };
  for (int i = 0; i < n; ++i) {
    if (!color[i]) {
      color[i] = 1;
      dfs(i);
      ++C;
    }
  }
  trace(I, C, bipartite);

  auto count_independent_set =
    [&]() {
      int m1 = n / 2, m2 = n - m1;
      vector<int> dp(1 << m2);
      for (int i = 0; i < (1 << m1); ++i) {
        int64 cur = 0;
        bool ok = 1;
        for (int j = 0; j < m1; ++j) {
          if ((i >> j) & 1) {
            if (cur & (1LL << j)) {
              ok = 0;
              break;
            }
            cur |= g[j];
          }
        }
        if (ok) dp[cur >> m1]++;
      }
      for (int k = 0; k < m2; ++k) {
        for (int i = 0; i < (1 << m2); ++i) {
          if ((i >> k) & 1) dp[i] += dp[i ^ (1 << k)];
        }
      }
      int64 ret = 0;
      for (int i = 0; i < (1 << m2); ++i) {
        int64 cur = 0;
        bool ok = 1;
        for (int j = 0; j < m2; ++j) {
          if ((i >> j) & 1) {
            if (cur & (1LL << (m1 + j))) {
              ok = 0;
              break;
            }
            cur |= g[m1 + j];
          }
        }
        cur >>= m1;
        if (ok) ret += dp[(1 << m2) - 1 - i];
      }
      return ret;
    };

  int64 IS = count_independent_set();

  auto solve =
    [&](int mask) -> int64{
      if (mask == 0) {
        return m == 0 ? 1LL << n : 0;
      } else if (mask == 1 || mask == 4) {
        return 1LL << I;
      } else if (mask == 2) {
        return bipartite ? 1LL << C : 0;
      } else if (mask == 3 || mask == 6) {
        return IS;
      } else if (mask == 5) {
        return 1LL << C;
      } else {
        return 1LL << n;
      }
    };

  int64 ret = 0;
  for (int mask = 0; mask < 8; ++mask) {
    int64 cur = solve(mask);
    trace(mask, cur);
    if (__builtin_parity(mask)) {
      ret += cur;
    } else {
      ret -= cur;
    }
  }
  cout << ret << '\n';

  return 0;
}

