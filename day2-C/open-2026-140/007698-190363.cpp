// Created by rost on 05.03.2026.

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

const int INF = 1e9 + 7;

struct Monster {
  int h, r;
};

struct Sword {
  int s, c;
};

void solve() {
  int n, m, k, x;
  cin >> n >> m >> k >> x;
  vector<Monster> monsters(n);
  for (auto &[h, r] : monsters) cin >> h >> r;
  vector<Sword> swords(m);
  for (auto &[s, c] : swords) cin >> s >> c;

  vector<int> d;
  for (auto &[h, r] : monsters) d.emplace_back(h);
  for (auto &[s, c] : swords) d.emplace_back(s);
  sort(d.begin(), d.end());
  d.erase(unique(d.begin(), d.end()), d.end());

  auto compress = [&](int x) {
    return int(lower_bound(d.begin(), d.end(), x) - d.begin());
  };

  for (auto &[h, r] : monsters) h = compress(h);
  for (auto &[s, c] : swords) s = compress(s);

  sort(swords.begin(), swords.end(),
       [](const Sword &s1, const Sword &s2) { return s1.s > s2.s; });

  vector<int> mCost(d.size(), INF);
  for (auto e : swords) mCost[e.s] = min(mCost[e.s], e.c);

  for (int i = int(d.size()) - 2; i >= 0; --i)
    mCost[i] = min(mCost[i], mCost[i + 1]);

  if (k == 1) {
    sort(monsters.begin(), monsters.end(),
         [&](const Monster &m1, const Monster &m2) {
           bool gain1 = m1.r <= mCost[m1.h];
           bool gain2 = m2.r <= mCost[m2.h];

           if (gain1 && gain2) return m1.h < m2.h;
           if (gain1 && !gain2) return true;
           if (!gain1 && gain2) return false;
           return m1.h > m2.h;
         });

    int bal = x;
    for (auto [h, r] : monsters) {
      if (bal < mCost[h]) {
        cout << "No\n";
        return;
      }
      
      bal -= mCost[h];
      bal += r;
    }
    cout << "Yes\n";
  }


}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;
  while (t--) solve();
}