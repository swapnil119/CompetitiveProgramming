#include <bits/stdc++.h>

using namespace std;

int dp[128][128];

int calc(int r, int c) {
  if(dp[r][c] != -1) return dp[r][c];
  set<int> s;
  for(int i=1; i<r; ++i) {
    if(i == c) continue;
    s.insert(calc(i, c));
  }
  for(int i=1; i<c; ++i) {
    if(r == i) continue;
    s.insert(calc(r, i));
  }
  int temp = min(r, c);
  for(int i=1; i<temp; ++i) {
    s.insert(calc(r-i, c-i));
  }
  int y = 0;
  while(1) {
    if(s.find(y) == s.end()) return dp[r][c] = y;
    ++y;
  }
}

int main() {
  int n;
  cin >> n;
  memset(dp, -1, sizeof(dp));
  dp[1][2] = 0;
  dp[2][1] = 0;
  int ans = 0;
  for(int i=1; i<=n; ++i) {
    int l, r;
    cin >> l >> r;
    if(l == r or l == 0 or r == 0) {
      cout << 'Y' << endl;
      return 0;
    }
    else {
      ans ^= calc(l, r);
    }
  }
  if(ans) {
    cout << "Y\n";
  }
  else {
    cout << "N\n";
  }
}
