// url:https://codeforces.com/contest/1103/problem/E
// time:2022-04-06 18:06:28
// name:E-Radixsum

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

using uint64 = unsigned long long;
const int M = 4;
using poly = array<uint64, M>;

poly operator +(const poly& a, const poly& b) {
  poly ret;
  for (int i = 0; i < M; ++i) ret[i] = a[i] + b[i];
  return ret;
}
poly operator -(const poly& a, const poly& b) {
  poly ret;
  for (int i = 0; i < M; ++i) ret[i] = a[i] - b[i];
  return ret;
}
poly operator *(const poly& a, const poly& b) {
  poly ret;
  vector<uint64> t(2 * (M - 1) + 1);
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < M; ++j) {
      t[i + j] += a[i] * b[j];
    }
  }
  for (int i = 0; i < M; ++i) ret[i] = t[i] - t[M];
  for (int i = M + 1; i < SZ(t); ++i) ret[i - M - 1] += t[i];
  return ret;
}
poly operator *(const poly& a, const uint64 b) {
  poly ret;
  for (int i = 0; i < M; ++i) ret[i] = a[i] * b;
  return ret;
}
poly power(poly a, int n) {
  poly ret {};
  ret[0] = 1;
  for (; n; n >>= 1) {
    if (n & 1) ret = ret * a;
    a = a * a;
  }
  return ret;
}

int main() {
  int n;
  cin >> n;

  vector<int> ten(6);
  for (int i = 0; i <= 5; ++i) ten[i] = i == 0 ? 1 : ten[i - 1] * 10;

  vector<poly> a(ten[5]);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    a[x][0]++;
  }
  trace("init");

  auto hd_dft =
    [&](int flag) {
      vector<poly> w(10);
      w[0][0] = 1;
      if (flag) {
        w[1][2] = -1;
      } else {
        w[1][3] = -1;
      }
      for (int i = 2; i < 10; ++i) w[i] = w[i - 1] * w[1];

      vector<poly> b(10);
      for (int d = 0; d < 5; ++d) {
        for (int i = 0; i < ten[5]; ++i) {
          if ((i / ten[d]) % 10 == 0) {
            fill(b.begin(), b.end(), poly {});
            for (int j = 0; j < 10; ++j) {
              for (int k = 0; k < 10; ++k) {
                b[j] = b[j] + a[i + k * ten[d]] * w[j * k % 10];
              }
            }
            for (int j = 0; j < 10; ++j) {
              a[i + j * ten[d]] = b[j];
            }
          }
        }
      }
      const uint64 inv5 = 14757395258967641293ULL;
      if (flag) {
        uint64 inv = inv5 * inv5 * inv5 * inv5 * inv5;
        for (int i = 0; i < ten[5]; ++i) {
          a[i] = a[i] * inv;
        }
      }
    };

  hd_dft(0);
  for (int i = 0; i < ten[5]; ++i) a[i] = power(a[i], n);
  hd_dft(1);

  const uint64 mod = 1ULL << 58;
  for (int i = 0; i < n; ++i) cout << a[i][0] / 32 % mod << '\n';

  return 0;
}

