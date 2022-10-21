// url:https://codeforces.com/contest/1394/problem/C
// time:2022-03-21 14:29:43
// name:C-BoboniuandString

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
// using int128 = __int128_t;
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
  vector<array<int, 2>> a(n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (auto& c : s) {
      if (c == 'B') {
        a[i][0]++;
      } else {
        a[i][1]++;
      }
    }
  }
  int low = 0, high = 1e6;
  int retX, retY;
  while (low != high) {
    int mid = (low + high) / 2;
    vector<ii> eventX, eventY, eventXY;
    for (auto& [x, y] : a) {
      eventX.push_back({x - mid, 1});
      eventX.push_back({x + mid + 1, -1});
      eventY.push_back({y - mid, 1});
      eventY.push_back({y + mid + 1, -1});
      eventXY.push_back({x - y - mid, 1});
      eventXY.push_back({x - y + mid + 1, -1});
    }
    sort(eventX.begin(), eventX.end());
    sort(eventY.begin(), eventY.end());
    sort(eventXY.begin(), eventXY.end());
    trace(eventX, eventY, eventXY);

    array<int, 2> x = {1, 0}, y = {1, 0}, xy = {1, 0};
    int sum = 0;
    for (auto& [pos, k] : eventX) {
      sum += k;
      if (sum == n) {
        x[0] = pos;
      } else if (sum - k == n) {
        x[1] = pos - 1;
      }
    }
    sum = 0;
    for (auto& [pos, k] : eventY) {
      sum += k;
      if (sum == n) {
        y[0] = pos;
      } else if (sum - k == n) {
        y[1] = pos - 1;
      }
    }
    for (auto& [pos, k] : eventXY) {
      sum += k;
      if (sum == n) {
        xy[0] = pos;
      } else if (sum - k == n) {
        xy[1] = pos - 1;
      }
    }
    trace(x, y, xy);

    ckmax(x[0], 0);
    ckmax(y[0], 0);
    if (x[0] > x[1] || y[0] > y[1] || xy[0] > xy[1]) {
      low = mid + 1;
      continue;
    }
    bool ok = 0;
    // x & y
    for (int k1 = 0; k1 < 2; ++k1) {
      for (int k2 = 0; k2 < 2; ++k2) {
        int X = x[k1], Y = y[k2];
        if (X >= 0 && Y >= 0 && !(X == 0 && Y == 0) &&
            X >= x[0] && X <= x[1] &&
            Y >= y[0] && Y <= y[1] &&
            X - Y >= xy[0] && X - Y <= xy[1]) {
          retX = X;
          retY = Y;
          ok = 1;
        }
      }
    }
    // x & xy
    for (int k1 = 0; k1 < 2; ++k1) {
      for (int k2 = 0; k2 < 2; ++k2) {
        int X = x[k1], Y = X - xy[k2];
        if (X >= 0 && Y >= 0 && !(X == 0 && Y == 0) &&
            X >= x[0] && X <= x[1] &&
            Y >= y[0] && Y <= y[1] &&
            X - Y >= xy[0] && X - Y <= xy[1]) {
          retX = X;
          retY = Y;
          ok = 1;
        }
      }
    }
    // y & xy
    for (int k1 = 0; k1 < 2; ++k1) {
      for (int k2 = 0; k2 < 2; ++k2) {
        int Y = y[k1], X = xy[k2] + Y;
        if (X >= 0 && Y >= 0 && !(X == 0 && Y == 0) &&
            X >= x[0] && X <= x[1] &&
            Y >= y[0] && Y <= y[1] &&
            X - Y >= xy[0] && X - Y <= xy[1]) {
          retX = X;
          retY = Y;
          ok = 1;
        }
      }
    }

    trace(mid, ok, retX, retY, x, y, xy);

    if (!ok) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  cout << high << '\n';
  cout << string(retX, 'B') << string(retY, 'N') << '\n';
  return 0;
}

