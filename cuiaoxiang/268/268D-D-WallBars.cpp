// url:https://codeforces.com/contest/268/problem/D
// time:2022-01-08 14:47:12
// name:D-WallBars

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
const int MOD = 1e9 + 9;
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

  auto dp = vect<int>(0, 2, m + 1, m + 1, m + 1);
  dp[0][1][1][1] = 4;
  for (int i = 2; i <= n; ++i) {
    auto ndp = vect<int>(0, 2, m + 1, m + 1, m + 1);
    for (int x = 0; x < 2; ++x) {
      for (int y = 0; y <= m; ++y) {
        for (int z = y; z <= m; ++z) {
          for (int u = z; u <= m; ++u) {
            int t = dp[x][y][z][u];
            if (t == 0) continue;
            int ny = min(y + 1, m), nz = min(z + 1, m), nu = min(u + 1, m);
            add_mod(ndp[x][ny][nz][nu], t);
            if (x == 1) {
              add_mod(ndp[y == m ? 1 : 0][nz][nu][m], t);
              add_mod(ndp[z == m ? 1 : 0][ny][nu][m], t);
              add_mod(ndp[u == m ? 1 : 0][ny][nz][m], t);
            } else {
              add_mod(ndp[y == m ? 1 : 0][1][nz][nu], t);
              add_mod(ndp[z == m ? 1 : 0][1][ny][nu], t);
              add_mod(ndp[u == m ? 1 : 0][1][ny][nz], t);
            }
          }
        }
      }
    }
    swap(dp, ndp);
    trace(i, dp);
  }
  dp[1][m][m][m] = 0;
  int ret = 0;
  for (int x = 0; x < 2; ++x) {
    for (int y = 0; y <= m; ++y) {
      for (int z = y; z <= m; ++z) {
        for (int u = z; u <= m; ++u) {
          add_mod(ret, dp[x][y][z][u]);
        }
      }
    }
  }
  cout << ret << '\n';
  return 0;
}

