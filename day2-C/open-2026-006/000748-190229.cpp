// Forza Ferrari!
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<array<int, 2>> events;
  for (int i = 0; i < n; i++) {
    int l, r;
    cin >> l >> r;
    events.push_back({l, +1});
    events.push_back({r, -1});
  }
  sort(events.begin(), events.end());
  constexpr int INF = 1e9;
  vector<int> dp(n + 1, INF);
  int open = 0, closed = 0;
  for (int i = 0; i < events.size(); i++) {
    int j = i;
    while (j < events.size() && events[i][0] == events[j][0]) {
      open += events[j][1];
      if (events[j][1] == -1) {
        closed += 2;
      }
      ++j;
    }
    int left = closed, right = 2 * n - 2 * open - closed;
    int pos = open + min(left, right);
    dp[pos] = min(dp[pos], min(left, right) / 2);
    i = j - 1;
  }
  for (int i = n; i > 1; i--) {
    dp[i - 2] = min(dp[i - 2], dp[i] - 1);
  }
  for (int i = n - 1; i >= 0; i--) {
    dp[i] = min(dp[i], dp[i + 1]);
  }
  while (q --> 0) {
    int k;
    cin >> k;
    cout << max(0, dp[k]) << " \n"[q == -1];
  }
}
