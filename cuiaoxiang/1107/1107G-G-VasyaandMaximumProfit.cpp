// url:https://codeforces.com/contest/1107/problem/G
// time:2022-03-15 09:16:20
// name:G-VasyaandMaximumProfit

#define LOCAL
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
#include <ctime>using namespace std;template <typename A, typename B>
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
}template <class T> auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D> auto vect(const T& v, int n, D... m) {
  return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}using int64 = long long;
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
void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;template<typename T, size_t N, size_t K>
struct rmq {
  T mx[N][K], mn[N][K];
  int lg2[N];
  rmq(const vector<T>& a) {
    int n = SZ(a);
    for (int i = 2; i <= n; ++i) lg2[i] = lg2[i / 2] + 1;
    for (int i = 0; i < n; ++i) {
      mx[i][0] = mn[i][0] = a[i];
    }
    for (int k = 1; k < K; ++k) {
      for (int i = 0; i + (1 << k) <= n; ++i) {
        int j = i + (1 << (k - 1));
        mx[i][k] = max(mx[i][k - 1], mx[j][k - 1]);
        mn[i][k] = min(mn[i][k - 1], mn[j][k - 1]);
      }
    }
  }
  T get_min(int x, int y) {
    int k = lg2[y - x + 1];
    return min(mn[x][k], mn[y - (1 << k) + 1][k]);
  }
  T get_max(int x, int y) {
    int k = lg2[y - x + 1];
    return max(mx[x][k], mx[y - (1 << k) + 1][k]);
  }
};int main() {
  int n, gain;
  cin >> n >> gain;  vector<int> d(n), c(n);
  for (int i = 0; i < n; ++i) cin >> d[i] >> c[i];  vector<int> p(n - 1);
  iota(p.begin(), p.end(), 0);
  sort(p.begin(), p.end(),
       [&](int L, int R) {
         return d[L + 1] - d[L] < d[R + 1] - d[R];
       });
  vector<int> pre(n - 1), nxt(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    nxt[i] = i + 1;
    pre[i] = i - 1;
  }
  vector<int> L(n), R(n);
  for (int i = 0; i < n - 1; ++i) {
    int x = p[i];
    int ll = pre[x], rr = nxt[x];
    L[x] = ll + 1;
    R[x] = rr;
    if (pre[x] >= 0) nxt[pre[x]] = nxt[x];
    if (nxt[x] != n - 1) pre[nxt[x]] = pre[x];
  }  vector<int64> sum(n + 1);
  for (int i = 0; i < n; ++i) sum[i + 1] = sum[i] + (gain - c[i]);
  const int N = 3e5 + 10;
  const int K = 20;
  rmq<int64, N, K> D(sum);  int64 ret = 0;
  for (int i = 0; i < n; ++i) ckmax(ret, 1LL* gain - c[i]);
  for (int i = 0; i < n - 1; ++i) {
    int64 cur = (d[i + 1] - d[i]);
    cur = -cur * cur;
    cur += D.get_max(i + 2, R[i] + 1) - D.get_min(L[i], i);
    // trace(i, d[i], d[i + 1], cur);
    ckmax(ret, cur);
  }
  cout << ret << '\n';  return 0;
}

