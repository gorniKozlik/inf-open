// Created by rost on 05.03.2026.

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

struct Seg {
  int l, r;
};

void solve() {
  int n, q;
  cin >> n >> q;
  vector<Seg> segs(n);
  vector<int> cords;
  for (auto &[l, r] : segs) {
    cin >> l >> r;

    cords.emplace_back(l);
    cords.emplace_back(r);
  }

  sort(cords.begin(), cords.end());
  // cords.erase(unique(cords.begin(), cords.end()), cords.end());
  auto compress = [&](int x) -> int {
    return int(lower_bound(cords.begin(), cords.end(), x) - cords.begin());
  };

  for (auto &[l, r] : segs) {
    l = compress(l);
    r = compress(r);
  }

  vector<int> d(2 * n);
  for (auto [l, r] : segs) {
    d[l]++;
    d[r]--;
  }

  // sort(segs.begin(), segs.end(),
  //      [](const Seg &lhs, const Seg &rhs) { return lhs.r < rhs.r; });

  vector<int> res(n + 1, 2 * n);

  int j = 0;
  int bal = 0, lCnt = 0, rCnt = n;
  for (int i = 0; i < 2 * n; ++i) {
    // cerr << i << ": " << lCnt << ' ' << rCnt << '\n';
    for (int k = 0; k <= min(lCnt, rCnt); ++k) res[bal + 2 * k] = k;

    bal += d[i];
    if (d[i] == 1) {
      rCnt--;
    } else {
      lCnt++;
    }
  }

  for (int i = n - 1; i >= 0; --i) res[i] = min(res[i], res[i + 1]);

  for (int i = 0; i < q; ++i) {
    int x;
    cin >> x;
    cout << res[x] << ' ';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;
  while (t--) solve();
}