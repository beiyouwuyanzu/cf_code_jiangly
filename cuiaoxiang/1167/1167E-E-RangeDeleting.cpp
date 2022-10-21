// url:https://codeforces.com/contest/1167/problem/E
// time:2021-11-01 12:30:34
// name:E-RangeDeleting

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

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> L(m, inf<int>), R(m, -inf<int>);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    --x;
    ckmin(L[x], i);
    ckmax(R[x], i + 1);
  }
  vector<int> L2 = L, R2 = R;
  int last = 0, ll = -1;
  for (int k = 0; k < m; ++k) {
    if (R[k] < 0) {
      L[k] = R[k] = last;
    } else {
      if (L[k] < last) {
        ll = k;
        break;
      }
      last = R[k];
    }
  }

  if (ll < 0) {
    cout << 1LL * m * (m + 1) / 2 << '\n';
    return 0;
  }

  last = n;
  int rr = -1;
  for (int k = m - 1; k >= 0; --k) {
    trace(k, R2[k], last);
    if (R2[k] < 0) {
      L2[k] = R2[k] = last;
    } else {
      if (R2[k] > last) {
        rr = k;
        break;
      }
      last = L2[k];
    }
  }
  // if (rr < ll - 1) rr = ll - 1;
  vector<ii> pos;
  for (int k = rr + 1; k < m; ++k) pos.push_back({L2[k], R2[k]});
  int64 ret = SZ(pos) + 1;
  trace(pos);

  for (int k = 0; k < ll; ++k) {
    auto it = lower_bound(pos.begin(), pos.end(), ii{R[k], 0});
    int cur = pos.end() - it + 1;
    trace(k, cur);
    ret += cur;
  }
  cout << ret << '\n';

  return 0;
}

