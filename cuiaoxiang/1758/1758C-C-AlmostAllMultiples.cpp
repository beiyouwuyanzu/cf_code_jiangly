// url:https://codeforces.com/contest/1758/problem/C
// time:2022-11-25 18:55:59
// name:C-AlmostAllMultiples

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
mt19937_64 mrand(random_device{}());
int64 rnd(int64 x) { return mrand() % x; }
constexpr inline int lg2(int64 x) { return x == 0 ? -1 : sizeof(int64) * 8 - 1 - __builtin_clzll(x); }
constexpr inline int p2ceil(int64 x) { return 1 << (lg2(x - 1) + 1); }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }
inline int mod(int x) { return x >= MOD ? x - MOD : x; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

const int N = 2e5 + 10;
bool flag[N];
vector<int> prime;
int minp[N];

void prime_gen(int n) {
  fill(flag, flag + n, false);
  for (int i = 2; i < n; ++i) {
    if (!flag[i]) {
      prime.push_back(i);
      minp[i] = i;
    }
    for (int j = 0, k; j < SZ(prime) && (k = prime[j] * i) < n; ++j) {
      flag[k] = true;
      if (i % prime[j]) {
        minp[k] = prime[j];
      } else {
        minp[k] = minp[i];
        break;
      }
    }
  }
  trace(SZ(prime));
}

int main() {
  prime_gen(N);
  int cas;
  cin >> cas;
  while (cas--) {
    int n, k;
    cin >> n >> k;
    if (k == n) {
      vector<int> ret(n);
      iota(ret.begin(), ret.end(), 1);
      swap(ret[0], ret[n - 1]);
      out(ret);
    } else {
      int m = n / 2;
      if (k >= 2 && k <= m) {
        bool ok = 1;
        vector<int> ret(n);
        iota(ret.begin(), ret.end(), 1);
        ret[n - 1] = 1;
        vector<bool> vis(n + 1);
        ret[0] = k;
        vis[k] = 1;
        for (int i = 1; i < m; ++i) {
          if (!vis[ret[i]]) {
            vis[ret[i]] = 1;
            continue;
          }
          int p = minp[n / ret[i]];
          if (ret[i] * p > m && ret[i] * p != n) {
            ok = 0;
            break;
          }
          ret[i] *= p;
          vis[ret[i]] = 1;
        }
        if (!ok) {
          cout << -1 << '\n';
        } else {
          out(ret);
        }
      } else {
        cout << -1 << '\n';
      }
    }
  }

  return 0;
}

