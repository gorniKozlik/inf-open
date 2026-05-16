#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int q, n;
  cin >> q >> n;

  vector <pair<int, int>> seg(n);
  for (int i = 0; i < n; ++i) {
    cin >> seg[i].first >> seg[i].second;
  }

  for (int qi = 0; qi < q; ++qi) {
    int x;
    cin >> x;

    cout << x / 2 << " ";
  }
  cout << "\n";
  return 0;
}