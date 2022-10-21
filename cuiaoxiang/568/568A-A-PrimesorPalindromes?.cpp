// url:https://codeforces.com/contest/568/problem/A
// time:2021-11-05 12:59:18
// name:A-PrimesorPalindromes?

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

const int N = 1e8;
bool flag[N];
vector<int> prime;

void prime_gen(int n = N) {
  fill(flag, flag + n, false);
  for (int i = 2; i < n; ++i) {
    if (!flag[i]) {
      prime.push_back(i);
      // minp[i] = i;
    }
    for (int j = 0, k; j < SZ(prime) && (k = prime[j] * i) < n; ++j) {
      flag[k] = true;
      if (i % prime[j]) {
        // minp[k] = prime[j];
      } else {
        // minp[k] = minp[i];
        break;
      }
    }
  }
}

int main() {
  prime_gen();

  int64 p, q;
  cin >> p >> q;

  const int K = 8;
  vector<int> p10(K, 1);
  for (int k = 1; k < K; ++k) p10[k] = p10[k - 1] * 10;
  vector<int> palin;
  for (int i = 1; i < 10; ++i) palin.push_back(i);
  auto rev =
    [&](int n) {
      int ret = 0;
      for (int t = n; t; t /= 10) ret = ret * 10 + t % 10;
      return ret;
    };
  for (int k = 2; k < 8; ++k) {
    int L = k / 2;
    if (k % 2) {
      for (int i = p10[L - 1]; i < p10[L]; ++i) {
        for (int j = 0; j < 10; ++j) {
          palin.push_back(i * p10[L + 1] + j * p10[L] + rev(i));
        }
      }
    } else {
      for (int i = p10[L - 1]; i < p10[L]; ++i) {
        palin.push_back(i * p10[L] + rev(i));
      }
    }
  }
  sort(palin.begin(), palin.end());
  auto get_pi =
    [&](int n) {
      return upper_bound(prime.begin(), prime.end(), n) - prime.begin();
    };
  auto get_rub =
    [&](int n) {
      return upper_bound(palin.begin(), palin.end(), n) - palin.begin();
    };
  // int low = 1, high = N;
  // while (low != high) {
  //   int mid = (low + high) / 2;
  //   int64 x = get_pi(mid);
  //   int64 y = get_rub(mid);
  //   if (x * q < p * y) {
  //     low = mid + 1;
  //   } else {
  //     high = mid;
  //   }
  // }
  int ret = 0;
  for (int i = 0; i < SZ(prime); ++i) {
    int x = prime[i] - 1;
    if (i * q <= get_rub(x) * p) ret = x;
  }
  cout << ret << '\n';
  // for (int i = 1; i <= 10000; ++i) {
  //   double cur = get_pi(i) * 1.0 / get_rub(i);
  //   trace(i, cur);
  // }
  // cout << high << '\n';
  return 0;
}

