#include <bits/stdc++.h>
#define REP(i, a, n) for (long long i = (a); i < (long long)(n); ++i)
#define REPC(i, a, n) for (long long i = (a); i <= (long long)(n); ++i)
#define ALL(t) t.begin(), t.end()
#define RALL(t) t.rbegin(), t.rend()
#define MATINIT(type, row, col, init) \
  vector<vector<type>>(row, vector<type>(col, init));
#define Yes(cond) cout << (cond ? "Yes" : "No") << endl;
#define YES(cond) cout << (cond ? "YES" : "NO") << endl;
using namespace std;
using LL = long long;
using ULL = unsigned long long;
template <class T>
using VEC = std::vector<T>;
template <class T>
using MAT = std::vector<std::vector<T>>;
void DUMP() { cerr << endl; }
template <class Head, class... Tail>
void DUMP(Head &&head, Tail &&... tail) {
  cerr << head << ", ";
  DUMP(std::move(tail)...);
}
template <typename T>
ostream &operator<<(ostream &os, vector<T> &vec) {
  os << "{";
  for (auto v : vec) os << v << ",";
  os << "}";
  return os;
}
template <typename T>
ostream &operator<<(ostream &os, set<T> &s) {
  os << "{";
  for (auto p : s) os << p << ",";
  os << "}";
  return os;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, map<T1, T2> &m) {
  os << "{";
  for (auto p : m) os << p << ",";
  os << "}";
  return os;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, pair<T1, T2> p) {
  os << "[" << p.first << " " << p.second << "]";
  return os;
}
std::map<long long, long long> primeFactorization(
    long long n) { /* prime factorization * nを素因数分解する */
  std::map<long long, long long> pf;
  for (long long i = 2; i * i <= n; ++i) {
    while (n % i == 0) {
      n /= i;
      ++pf[i];
    }
  }
  if (n > 1) {
    ++pf[n];
  }
  return pf;
}

int main() {
  ULL S;
  cin >> S;
  ULL lim = 1e9;
  ULL x2 = (lim-S%lim)%lim;
  ULL x1 = (S+lim-1)/lim;
  printf("%lld %lld %lld %lld %lld %lld\n", 0LL, 0LL, x1, 1LL, x2, (LL)1e9);
  cerr<<x1*lim-x2<<endl;
  return 0;
}
