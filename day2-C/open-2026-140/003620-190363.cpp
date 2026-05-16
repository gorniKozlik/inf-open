// Created by rost on 05.03.2026.

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

struct Seg {
  int l, r;
  int i;
};

void solve() {
  int n, q;
  cin >> n >> q;
  vector<Seg> segs(n);
  vector<int> cords;
  for (auto &[l, r, i] : segs) {
    cin >> l >> r;

    cords.emplace_back(l);
    cords.emplace_back(r);
  }

  sort(cords.begin(), cords.end());
  // cords.erase(unique(cords.begin(), cords.end()), cords.end());
  auto compress = [&](int x) -> int {
    return int(lower_bound(cords.begin(), cords.end(), x) - cords.begin());
  };

  for (auto &[l, r, i] : segs) {
    l = compress(l);
    r = compress(r);
  }

  vector<int> d(2 * n);
  for (auto [l, r, i] : segs) {
    d[l]++;
    d[r]--;
  }

  // sort(segs.begin(), segs.end(),
  //      [](const Seg &lhs, const Seg &rhs) { return lhs.r < rhs.r; });

  vector<int> res(n + 1, 2 * n);

  int bal = 0, lCnt = 0, rCnt = n;
  vector<Seg> resSegs(2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    // cerr << i << ": " << lCnt << ' ' << rCnt << '\n';
    // for (int k = 0; k <= min(lCnt, rCnt); ++k)
    // res[bal + 2 * k] = min(res[bal + 2 * k], k);

    resSegs[i] = {bal, bal + 2 * min(lCnt, rCnt), i};

    bal += d[i];
    if (d[i] == 1) {
      rCnt--;
    } else {
      lCnt++;
    }
  }

  auto sortSegs = resSegs;
  sort(sortSegs.begin(), sortSegs.end(),
       [](const Seg &lhs, const Seg &rhs) { return lhs.l < rhs.l; });

  int j = 0;
  vector<int> st;
  for (int i = 1; i <= n; ++i) {
    while (j != 2 * n && sortSegs[j].l <= i)
      st.push_back(j++);
    while (resSegs[st.back()].r < i) st.pop_back();

    res[i] = (i - resSegs[st.back()].l + 1) / 2;
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