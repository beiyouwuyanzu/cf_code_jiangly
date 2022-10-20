// url:https://codeforces.com/contest/1671/problem/D
// time:2022-04-22 18:45:09
// name:D-InsertaProgression

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
  int cas;
  cin >> cas;
  while (cas--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    trace(n,m, a);

    int64 ret = 0;
    vector<ii> event;
    for (int i = 1; i < n; ++i) {
      int L = a[i - 1], R = a[i];
      if (L > R) swap(L, R);
      ret += R - L;
      event.push_back({L, -1});
      event.push_back({R, 1});
    }
    sort(event.begin(), event.end());
    trace(event, ret);
    int sum = 0;
    vector<int> x;
    for (auto& [pos, k] : event) {
      sum -= k;
      if ((sum == 1 && k < 0) || (sum == 0 && k > 0)) {
        x.push_back(pos);
      }
    }
    if (n == 1) {
      x = {a[0], a[0]};
    }
    trace(x);
    int len = SZ(x);

    auto Get =
      [&](int ll, int rr, int x) {
        int ret = (rr - ll + 1) * 2;
        if (x < ll) ret = rr - x;
        if (x > rr) ret = x - ll;
        return (rr - ll + 1) * 2 - ret;
      };
    vector<ii> bestL(2, ii{0, inf<int>});
    vector<ii> bestR(2, ii{0, inf<int>});
    auto Update =
      [&](vector<ii>& best, ii cur) {
        if (cur > best[0]) {
          best[1] = best[0];
          best[0] = cur;
        } else if (cur > best[1]) {
          best[1] = cur;
        }
      };
    if (x[0] > 1) {
      int ll = 1, rr = x[0] - 1;
      ret += (rr - ll + 1) * 2;
      int gain = Get(ll, rr, a[0]);
      Update(bestL, {gain, 0});
      gain = Get(ll, rr, a[n - 1]);
      Update(bestR, {gain, 0});
    }
    for (int i = 1; i + 1 < SZ(x); i += 2) {
      int ll = x[i] + 1, rr = x[i + 1] - 1;
      ret += (rr - ll + 1) * 2;
      int gain = Get(ll, rr, a[0]);
      Update(bestL, {gain, i});
      gain = Get(ll, rr, a[n - 1]);
      Update(bestR, {gain, i});
    }
    if (x.back() < m) {
      int ll = x.back() + 1, rr = m;
      ret += (rr - ll + 1) * 2;
      int gain = Get(ll, rr, a[0]);
      Update(bestL, {gain, len});
      gain = Get(ll, rr, a[n - 1]);
      Update(bestR, {gain, len});
    }
    trace(ret, bestL, bestR);
    if (bestL[0].second != bestR[0].second) {
      ret -= bestL[0].first + bestR[0].first;
    } else {
      ret -= max(bestL[1].first + bestR[0].first, bestL[0].first + bestR[1].first);
    }

    cout << ret << '\n';
  }

  return 0;
}

