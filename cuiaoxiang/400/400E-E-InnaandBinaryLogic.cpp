// url:https://codeforces.com/contest/400/problem/E
// time:2021-11-08 17:31:59
// name:E-InnaandBinaryLogic

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

int main() {
  int n, q;
  cin >> n >> q;
  const int K = 20;
  vector<bitset<K>> a(n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    a[i] = x;
  }
  vector<set<ii>> b(K);
  for (int k = 0; k < K; ++k) {
    for (int i = 0, j; i < n; i = j) {
      for (; i < n && a[i][k] == 0; ++i);
      if (i == n) break;
      for (j = i + 1; j < n && a[j][k]; ++j);
      b[k].insert({i, j});
    }
  }
  auto cost =
    [&](int len) {
      return 1LL * (len + 1) * len / 2;
    };
  int64 sum = 0;
  for (int k = 0; k < K; ++k) {
    for (auto& p : b[k]) sum += cost(p.second - p.first) * (1LL << k);
  }
  while (q--) {
    int p, x;
    cin >> p >> x;
    --p;
    for (int k = 0; k < K; ++k) {
      int xk = (x >> k) & 1;
      if (a[p][k] == xk) continue;
      if (xk == 1) {
        auto it = b[k].upper_bound(ii{p, p});
        auto R = it == b[k].end() ? ii{-1, -1} : *it;
        auto L = it == b[k].begin() ? ii{-1, -1} : *prev(it);
        if (L.second == p && R.first == p + 1) {
          sum += (cost((R.second - R.first) + (L.second - L.first) + 1) -
                  cost(R.second - R.first) -
                  cost(L.second - L.first)) * (1LL << k);
          b[k].erase(L); b[k].erase(R); b[k].insert(ii{L.first, R.second});
        } else if (L.second == p) {
          sum += (cost((L.second - L.first) + 1) - cost(L.second - L.first)) * (1LL << k);
          b[k].erase(L); b[k].insert(ii{L.first, L.second + 1});
        } else if (R.first == p + 1) {
          sum += (cost((R.second - R.first) + 1) - cost(R.second - R.first)) * (1LL << k);
          b[k].erase(R); b[k].insert(ii{R.first - 1, R.second});
        } else {
          sum += cost(1) * (1LL << k);;
          b[k].insert(ii{p, p + 1});
        }
      } else {
        auto it = b[k].upper_bound(ii{p, inf<int>});
        --it;
        auto cur = *it;
        // trace(cur, p);
        sum += (cost(p - cur.first) + cost(cur.second - (p + 1)) - cost(cur.second - cur.first)) * (1LL << k);
        b[k].erase(cur);
        if (p > cur.first) b[k].insert(ii{cur.first, p});
        if (cur.second > p + 1) b[k].insert(ii{p + 1, cur.second});
      }
    }
    a[p] = x;
    // trace(a, x);
    // for (int k = 0; k < K; ++k) trace(k, b[k]);
    cout << sum << '\n';
  }

  return 0;
}

