// url:https://codeforces.com/contest/1584/problem/F
// time:2022-01-13 18:44:28
// name:F-StrangeLCS

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
    int n;
    cin >> n;

    auto pos = vect<vector<int>>({}, n, 256);
    auto rpos = vect<int>(0, n, 200);
    auto nxt = vect<int>(-1, n, 200, 256);
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      for (int j = 0; j < SZ(s); ++j) {
        rpos[i][j] = SZ(pos[i][s[j]]);
        pos[i][s[j]].push_back(j);
      }
      vector<int> last(256, -1);
      for (int j = SZ(s) - 1; j >= 0; --j) {
        nxt[i][j] = last;
        last[s[j]] = j;
      }
    }

    vector<char> can;
    for (int i = 0; i < 26; ++i) {
      can.push_back('a' + i);
      can.push_back('A' + i);
    }
    auto dp = vect<int>(-1, 256, 1 << n);
    auto path = vect<pair<char, int>>({}, 256, 1 << n);
    function<int(char, int)> solve =
      [&](char c, int mask) {
        int& ret = dp[c][mask];
        if (ret >= 0) return ret;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
          int k = (mask >> i) & 1;
          if (k >= SZ(pos[i][c])) return ret = 0;
          a[i] = pos[i][c][k];
        }
        ret = 1;
        for (auto& nc : can) {
          int nmask = 0;
          bool ok = 1;
          for (int i = 0; i < n; ++i) {
            int p = nxt[i][a[i]][nc];
            if (p < 0) {
              ok = 0;
              break;
            }
            auto k = rpos[i][p];
            nmask |= k << i;
          }
          // if (c == 'a' && nc == 'c') trace(ok, nmask);
          if (!ok) continue;
          int cur = 1 + solve(nc, nmask);
          if (ret < cur) {
            ret = cur;
            path[c][mask] = {nc, nmask};
          }
        }
        return ret;
      };
    pair<char, int> best;
    int ret = 0;
    for (auto& c : can) {
      for (int mask = 0; mask < (1 << n); ++mask) {
        int cur = solve(c, mask);
        if (ret < cur) {
          ret = cur;
          best = {c, mask};
        }
      }
    }
    cout << ret << '\n';
    string s;
    if (ret > 0) {
      trace(best);
      for (; dp[best.first][best.second] > 1; ) {
        s += best.first;
        best = path[best.first][best.second];
      }
      s += best.first;
    }
    trace(ret, s);
    cout << s << '\n';
  }

  return 0;
}

