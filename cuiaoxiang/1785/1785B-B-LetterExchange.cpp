// url:https://codeforces.com/contest/1785/problem/B
// time:2023-02-05 15:30:30
// name:B-LetterExchange

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

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n;
    cin >> n;
    const string S = "win";
    auto get = [&](char c) { return S.find(c); };
    auto a = vect<vector<int>>({}, 3, 3);
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      vector<int> cnt(3);
      for (int j = 0; j < 3; ++j) cnt[get(s[j])]++;
      for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
          if (x == y) continue;
          if (cnt[x] > 1 && cnt[y] < 1) {
            a[x][y].push_back(i);
            --cnt[x];
            ++cnt[y];
          }
        }
      }
    }
    vector<array<int, 4>> ret;
    for (int x = 0; x < 3; ++x) {
      for (int y = x + 1; y < 3; ++y) {
        while (SZ(a[x][y]) && SZ(a[y][x])) {
          int i = a[x][y].back(), j = a[y][x].back();
          a[x][y].pop_back();
          a[y][x].pop_back();
          ret.push_back({i, x, j, y});
        }
      }
    }
    while (SZ(a[0][1]) && SZ(a[1][2]) && SZ(a[2][0])) {
      int i = a[0][1].back(), j = a[1][2].back(), k = a[2][0].back();
      a[0][1].pop_back(); a[1][2].pop_back(); a[2][0].pop_back();
      ret.push_back({i, 0, j, 1});
      ret.push_back({j, 0, k, 2});
    }
    while (SZ(a[1][0]) && SZ(a[2][1]) && SZ(a[0][2])) {
      int i = a[1][0].back(), j = a[2][1].back(), k = a[0][2].back();
      a[1][0].pop_back(); a[2][1].pop_back(); a[0][2].pop_back();
      ret.push_back({j, 2, k, 0});
      ret.push_back({i, 1, j, 0});
    }
    cout << SZ(ret) << '\n';
    for (auto [i, x, j, y] : ret) {
      cout << i + 1 << " " << S[x] << " " << j + 1 << " " << S[y] << '\n';
    }
  }

  return 0;
}

