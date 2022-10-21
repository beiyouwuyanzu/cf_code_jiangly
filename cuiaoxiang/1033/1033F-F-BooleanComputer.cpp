// url:https://codeforces.com/contest/1033/problem/F
// time:2022-03-13 15:23:07
// name:F-BooleanComputer

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
template<size_t N> int find_first(const bitset<N>& x) {
#ifdef LOCAL
  int k; for (k = 0; k < N && !x[k]; ++k);
  return k;
#else
  return x._Find_first();
#endif
}

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

int cnt[1 << 12];
int three[13];
int weight[1 << 12];
int dp[531441];

int main() {
  int w, n, m;
  scanf("%d%d%d", &w, &n, &m);
  // cin >> w >> n >> m;

  // vector<int> cnt(1 << w);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    // cin >> x;
    cnt[x]++;
  }

  // vector<int> three(w + 1);
  three[0] = 1;
  for (int i = 1; i <= w; ++i) three[i] = three[i - 1] * 3;

  // vector<int> weight(1 << w);
  for (int i = 0; i < (1 << w); ++i) {
    for (int j = 0; j < w; ++j) {
      if ((i >> j) & 1) weight[i] += three[j];
    }
  }
  // vector<int> dp(three[w]);
  for (int i = 0; i < (1 << w); ++i) {
    for (int j = 0; j < (1 << w); ++j) {
      dp[weight[i] + weight[j]] += cnt[i] * cnt[j];
    }
  }

  vector<int> choice;
  char s[100];
  while (m--) {
    // string s;
    // cin >> s;
    scanf("%s", s);
    // reverse(s.begin(), s.end());
    reverse(s, s + w);
    int mask = 0;
    choice.clear();
    for (int i = 0; i < w; ++i) {
      if (s[i] == 'A') choice.push_back(three[i]);
      if (s[i] == 'X') choice.push_back(three[i] * 2);
      if (s[i] == 'a') mask += three[i] * 2;
      if (s[i] == 'o') {
        mask += three[i];
        choice.push_back(three[i]);
      }
      if (s[i] == 'x') mask += three[i];
    }
    function<int(int, int)> dfs =
      [&](int mask, int dep) -> int {
        if (dep == SZ(choice)) return dp[mask];
        return dfs(mask + choice[dep], dep + 1) + dfs(mask, dep + 1);
      };
    int ret = dfs(mask, 0);
    printf("%d\n", ret);
    // cout << dfs(mask, 0) << '\n';
  }

  return 0;
}

