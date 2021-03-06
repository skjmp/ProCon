#include <bits/stdc++.h>
#define REP(i, a, n) for (int i = (a); i < (int)(n); ++i)
#define REPC(i, a, n) for (int i = (a); i <= (int)(n); ++i)
#define ALL(t) t.begin(), t.end()
#define RALL(t) t.rbegin(), t.rend()
#define MATINIT(type, row, col, init)                                          \
  vector<vector<type>>(row, vector<type>(col, init));
#define Yes(cond) cout << (cond ? "Yes" : "No") << endl;
#define YES(cond) cout << (cond ? "YES" : "NO") << endl;
using namespace std;
using LL = long long;
using ULL = unsigned long long;
template <class T> using VEC = std::vector<T>;
template <class T> using MAT = std::vector<std::vector<T>>;
void DUMP() { cerr << endl; }
template <class Head, class... Tail> void DUMP(Head &&head, Tail &&... tail) {
  cerr << head << ", ";
  DUMP(std::move(tail)...);
}
template <typename T> ostream &operator<<(ostream &os, vector<T> &vec) {
  os << "{";
  for (auto v : vec)
    os << v << ",";
  os << "}";
  return os;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, pair<T1, T2> p) {
  os << "[" << p.first << " " << p.second << "]";
  return os;
}
int N, K;
VEC<int> A;
std::mt19937 MT(25);

int randInRange(int minimum, int maximum) {
  return minimum + MT() % (maximum - minimum + 1);
}
int minInRange(int s, int e) {
  int mi = INT32_MAX;
  REPC(i, s, e) mi = min(mi, A[i]);
  return mi;
}
int maxInRange(int s, int e) {
  int ma = INT32_MIN;
  REPC(i, s, e) ma = max(ma, A[i]);
  return ma;
}
void update(int i, int j, int k, int l, int v) {
  REPC(a, i, j) A[a] -= v;
  REPC(a, k, l) A[a] += v;
}
LL improvePoint(int i, int j, int k, int l, int v) {
  LL cur = 0;
  LL after = 0;
  REPC(a, i, j) {
    cur += abs(A[a] - a);
    after += abs(A[a] - v - a);
  }
  REPC(a, k, l) {
    cur += abs(A[a] - a);
    after += abs(A[a] + v - a);
  }
  return after - cur;
}
LL score() {
  LL score = 0;
  REPC(i, 1, A.size()) { score += abs(A[i] - i); }
  return score;
}
const int TIMELIMIT = 4500;
int main() {
  auto startTime = chrono::system_clock::now();
  cin >> N >> K;
  VEC<int> inputA(N + 1, -1);
  REPC(i, 1, N) cin >> inputA[i];

  VEC<VEC<int>> currentSol = VEC<VEC<int>>(K, {0, 0, 1, 1, 0});
  LL currentScore = 0;
  VEC<VEC<int>> bestSol = VEC<VEC<int>>(K, {0, 0, 1, 1, 0});
  LL bestScore = 0;

  int64_t msec = 0;

  int cnt = 1;
  while (msec < TIMELIMIT) {
    A = inputA;
    MT.seed(cnt);
    REP(c, 0, K) {
      int i = randInRange(1, N - 1);
      int k = randInRange(i + 1, N);
      int maxlength = min(k - i - 1, N - k);
      int length = randInRange(0, maxlength);
      int j = i + length;
      int l = k + length;
      int left = minInRange(i, j) - 1;
      int right = N - maxInRange(k, l);
      int vmax = min(left, right);
      int v = randInRange(0, vmax);
      LL improvement = improvePoint(i, j, k, l, v);
      if (improvement < 0) {
        c--;
        continue;
      }
      update(i, j, k, l, v);
      currentSol[c] = {i, j, k, l, v};
    }
    currentScore = score();
    if (currentScore > bestScore) {
      bestSol = currentSol;
      bestScore = currentScore;
      DUMP(bestScore);
    }
    msec = chrono::duration_cast<chrono::milliseconds>(
               chrono::system_clock::now() - startTime)
               .count();
    ++cnt;
    // DUMP(msec);
  }
  REP(i, 0, K) {
    REP(j, 0, 5) {
      printf("%d", bestSol[i][j]);
      if (j < 4)
        printf(" ");
    }
    printf("\n");
  }

  return 0;
}
