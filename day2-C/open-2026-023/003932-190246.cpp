#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const int MOD = 1e9 + 7;
const int Inf = 2e9;
const ll INF = 3e18;

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector <pair <int, int>> a(n);
  vector <int> xs;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
    xs.push_back(a[i].first);
    xs.push_back(a[i].second);
  }
  sort(xs.begin(), xs.end());
  map <int, int> mp;
  for (int i = 0; i < 2 * n; i++) {
    mp[xs[i]] = 2 * i + 1;
  }
  vector <int> cntl(4*n), cntr(4*n);
  for (int i = 0; i < n; i++) {
    a[i].first = mp[a[i].first];
    a[i].second = mp[a[i].second];
    cntl[a[i].first]++;
    cntr[a[i].second]++;
  }
  vector <int> pref(4*n), suff(4*n);
  for (int i = 0; i < 4 * n; i++) {
    if (i > 0) pref[i] = pref[i-1];
    pref[i] += cntr[i];
  }
  for (int i = 4 * n - 1; i >= 0; i--) {
    if (i < 2 * n) suff[i] = suff[i+1];
    suff[i] += cntl[i];
  }
  while (q--) {
    int k;
    cin >> k;
    int ans = Inf;
    for (int i = 0; i < 4*n; i += 2) {
      int Ls = (i > 0 ? pref[i - 1] : 0);
      int Rs = (i < 4*n - 1 ? suff[i + 1] : 0);
      if (2 * min(Ls, Rs) + (n - (int)Ls - (int)Rs) >= k) {
        ans = min(ans, (k - (n - (int)Ls - (int)Rs) + 1) / 2);
      }
    }
    cout << max(0, ans) << '\n';
  }
  return 0;
}