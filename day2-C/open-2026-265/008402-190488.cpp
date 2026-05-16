#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define debout(x) std::cout << #x << " : " << x << '\n';
#define debvout(x) std::cout << #x << " : "; for (auto i: x) std::cout << i << ' '; std::cout << '\n';
#define enter std::cout << '\n';
using ll = long long;

void s1nm() {
  ll n, q;
  std::cin >> n >> q;
  std::vector<std::pair<ll, ll>> a(n);
  std::vector<ll> b;
  b.push_back(0);
  for (auto &[l, r]: a) {
    std::cin >> l >> r;
    b.push_back(l), b.push_back(r);
    b.push_back(r + 1);
  }
  std::sort(all(b));
  ll m = b.size() + 2;
  std::vector<std::vector<std::pair<ll, std::pair<ll, ll>>>> s(m); // 1 - add   0 - del
  for (auto &[l, r]: a) {
    l = std::lower_bound(all(b), l) - b.begin();
    r = std::lower_bound(all(b), r) - b.begin();
    // std::cout << l << ' ' << r << '\n';
    s[l].push_back({1, {l, r}});
    s[r + 1].push_back({0, {l, r}});
  }
  ll cntl = 0, cntr = n, cnt = 0;
  std::vector<ll> mink(n + 1, 1e18);
  std::vector<ll> add(n + 3, -1), add1(n + 3, -1);
  for (ll i = 0; i < m; i++) {
    ll temp = 0;
    for (ll j = 0; j < s[i].size(); j++) if (s[i][j].first == 0) temp++;
    if (cntr > cntl) {
      // debout(temp)
      // debout(cnt + cntl + 1)
      add1[cnt + cntl + 1] = std::max(add1[cnt + cntl + 1], cnt + cntl * 2 + std::min(temp, cntr - cntl));
      // debout(add1[cnt + cntl + 1])
    }
    // enter;
    temp = 0;
    for (ll j = 0; j < s[i].size(); j++) {
      if (s[i][j].first == 1) cnt++, cntr--;
      if (s[i][j].first == 0) cntl++, cnt--;
    }
    mink[cnt] = 0;
    // debout(i)debout(cntl) debout(cntr) debout(cnt)
    add[cnt + 1] = std::max(add[cnt + 1], cnt + std::min(cntr, cntl) * 2);
    // debout(add[cnt + 1])
    // if (cntl > cntr) {
    //   debout(cnt + cntl * 2 + 1)
    //   add1[cnt + cntl * 2 + 1] = std::max(add1[cnt + cntl * 2 + 1], cnt + cntl * 2 + std::min(cnt, cntl - 2));
    //   debout(add1[cnt + cntl * 2 + 1])
    // }
    for (ll j = 0; j < s[i].size(); j++) if (s[i][j].first == 1) temp++;
    if (cntl > cntr) {
      // debout(temp)
      // debout(cnt + cntr + 1)
      add1[cnt + cntr + 1] = std::max(add1[cnt + cntr + 1], cnt + cntr * 2 + std::min(temp, cntl - cntr));
      // debout(add1[cnt + cntr + 1])
    }
  }
  // debvout(mink) debvout(add) debvout(add1)
  std::deque<std::pair<ll, ll>> e, e1;
  for (ll i = 1; i <= n; i++) {
    if (add[i] != -1e18) {
      while (!e.empty() && e.back().second < add[i]) e.pop_back();
      e.emplace_back(i, add[i]);
    }
    if (add1[i] != -1e18) {
      while (!e1.empty() && e.back().second < add[i]) e1.pop_back();
      e1.emplace_back(i, add1[i]);
    }
    while (!e.empty() && e.back().second < i) e.pop_back();
    while (!e1.empty() && e1.back().second < i) e1.pop_back();
    if (!e.empty()) {
      mink[i] = std::min({mink[i], (i - e.back().first - 1) / 2 + 1});
    }
    if (!e1.empty()) {
      mink[i] = std::min(mink[i], (i - e1.back().first + 1));
    }
    // debout(mink[i])
  }
  for (ll i = n - 1; i >= 0; i--) mink[i] = std::min(mink[i], mink[i + 1]);
  while (q--) {
    ll k;
    std::cin >> k;
    std::cout << mink[k] << ' ';
  }
}

signed main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  ll TTT = 1;
  // std::cin >> TTT;
  while (TTT--) {
    s1nm();
    std::cout << '\n';
  }
}