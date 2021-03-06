#include <bits/stdc++.h>
#define REP(i, a, n) for (int i = (a); i < (int)(n); ++i)
#define REPC(i, a, n) for (int i = (a); i <= (int)(n); ++i)
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
int N, M;
VEC<int> A;
VEC<int> dp;
const int inf = 1e6;
const VEC<int> num = {0, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main() {
  cin >> N >> M;

  A = VEC<int>(M);
  REP(i, 0, M) cin >> A[i];
  dp = VEC<int>(N + 1, -inf);
  dp[0] = 0;
  REP(i, 0, N + 1) {
    REP(j, 0, M) {
      int rem = i - num[A[j]];
      if (rem >= 0) {
        dp[i] = max(dp[i], dp[rem] + 1);
      }
    }
  }
  DUMP(dp);
  int ansketa = dp[N];
  string ans = "";
  int match = N;
  sort(A.rbegin(), A.rend());
  REP(i, 0, ansketa) {
    REP(j, 0, M) {
      // if A[j] is available, remain will be
      int ketaRemain = ansketa - i - 1;
      int matchRemain = match - num[A[j]];
      if (matchRemain >= 0 && ketaRemain == dp[matchRemain]) {
        ans += A[j] + '0';
        match = matchRemain;
        DUMP(ans, A[j], match);
        break;
      }
    }
  }
  cout << ans << endl;

  return 0;
}
