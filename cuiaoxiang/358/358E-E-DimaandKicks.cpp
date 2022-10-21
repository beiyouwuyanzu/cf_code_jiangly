// url:https://codeforces.com/contest/358/problem/E
// time:2021-11-09 18:27:10
// name:E-DimaandKicks

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

typedef long long int64;
typedef pair<int, int> ii;
#define SZ(x) (int)((x).size())
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
mt19937 mrand(random_device{}());
int rnd(int x) { return mrand() % x; }
// mt19937_64 mrand(random_device{}());
// int64 rnd(int64 x) { return mrand() % x; }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
void add(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

const int d4[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
const int N = 1e6 + 0;
int f[N], c[N];
int find(int x) {
  if (f[x] != f[f[x]]) f[x] = find(f[x]);
  return f[x];
}
void join(int x, int y) {
  int rx = find(x), ry = find(y);
  if (rx != ry) {
    f[ry] = rx;
    c[rx] += c[ry];
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  auto a = vect<int>(0, n, m);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
      sum += a[i][j];
    }
  }
  for (int i = 0; i < n * m; ++i) f[i] = i, c[i] = 1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] && i - 1 >= 0 && a[i - 1][j]) join(i * m + j, (i - 1) * m + j);
      if (a[i][j] && j - 1 >= 0 && a[i][j - 1]) join(i * m + j, i * m + (j - 1));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j]) {
        int r = find(i * m + j);
        if (c[r] != sum) {
          cout << -1 << '\n';
          return 0;
        }
      }
    }
  }

  int odd = 0;
  vector<array<int, 2>> p;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == 0) continue;
      int mask = 0;
      for (int k = 0; k < 4; ++k) {
        int ni = i + d4[k][0];
        int nj = j + d4[k][1];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && a[ni][nj]) mask |= 1 << k;
      }
      if (__builtin_popcount(mask) % 2) ++odd;
      if (mask != 5 && mask != 10) {
        p.push_back({i, j});
      }
    }
  }

  trace(odd, p);
  if (odd > 2) {
    cout << -1 << '\n';
    return 0;
  }

  int g = 0;
  for (int i = 1; i < SZ(p); ++i) {
    int x = abs(p[i][0] - p[0][0]);
    int y = abs(p[i][1] - p[0][1]);
    g = gcd(g, gcd(x, y));
  }
  vector<int> ret;
  for (int k = 1; k * k <= g; ++k) {
    if (g % k == 0) {
      if (k > 1) ret.push_back(k);
      if (k * k != g && g / k > 1) ret.push_back(g / k);
    }
  }
  if (SZ(ret) == 0) {
    cout << -1 << '\n';
  } else {
    sort(ret.begin(), ret.end());
    out(ret);
  }

  return 0;
}

