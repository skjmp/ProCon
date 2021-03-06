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

int main() {
  LL M, K;
  cin >> M >> K;
  if (K >= (1 << M)) {
    cout << -1 << endl;
    return 0;
  }
  if (M == 0) {
    cout << "0 0"<< endl;
    return 0;
  }
  if (M == 1) {
    if (K == 0) {
      cout << "0 0 1 1" << endl;
    } else {
      cout << -1 << endl;
    }
    return 0;
  }
  LL lim = (1 << M);
  VEC<LL> A;
  REP(i, 0, lim) {
    if (i != K) {
      A.push_back(i);
    }
  }
  A.push_back(K);
  for (LL i = lim - 1; i >= 0; i--) {
    if (i != K) {
      A.push_back(i);
    }
  }
  A.push_back(K);
  REP(i, 0, A.size()) {
    cout << A[i];
    if (i < A.size() - 1) cout << " ";
  }
  cout << endl;

  return 0;
}
