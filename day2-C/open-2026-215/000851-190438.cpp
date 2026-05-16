#include "bits/stdc++.h"

using namespace std;

template<typename T>
istream &operator>>(istream &is, vector<T> &a) {
      for (T &elem: a) is >> elem;
      return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &a) {
      for (T elem: a) os << elem << ' ';
      return (os << '\n');
}

#define int long long

signed main() {
#ifdef LOCAL
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
#else
      cin.tie(nullptr);
      ios_base::sync_with_stdio(false);
#endif
      int n, q;
      cin >> n >> q;
      vector<pair<int, int>> a(n);
      vector<pair<int, int>> xx;
      for (auto &[l, r]: a) cin >> l >> r, xx.push_back({l, 1}), xx.push_back({r, -1});

      sort(xx.begin(), xx.end());

      vector<int> cntr(xx.size());
      vector<int> cntl(xx.size());
      int bal = 0, cr = 0, cl = 0;
      for (int i = 0; i < xx.size(); ++i) {
            auto [pos, type] = xx[i];

            if (type == -1) {
                  cr++;
            }
            cntl[i] = cr;
      }

      for (int i = xx.size() - 1; i >= 0; --i) {
            auto [pos, type] = xx[i];
            if (type == 1) {
                  cl++;
            }
            cntr[i] = cl;
      }
      struct event {
            int pos, type, maxk;
      };
      vector<event> ev;
      int allmax = 1;
      for (int i = 0; i < xx.size() - 1; ++i) {
            auto [pos, type] = xx[i];

            if (type == 1) bal++;
            else bal--;

            ev.push_back({bal, 1, bal});
            ev.push_back({bal + 2 * min(cntl[i], cntr[i + 1]) + 1, -1, bal});
            allmax = max(bal, allmax);
      }

      sort(ev.begin(), ev.end(), [&](event l, event r) {
            return l.pos < r.pos or l.pos == r.pos and l.type < r.type;
      });

      vector<int> ans(n + 100, 1e9);
      multiset<int, greater<int>> s;
      for (int i = 0; i < ev.size(); ++i) {
            auto [pos, type, maxk] = ev[i];
            if (type == 1) {
                  s.insert(maxk);
            } else {
                  s.extract(maxk);
            }
            if (s.empty()) continue;
            if (pos <= allmax) {
                  ans[pos] = 0;
            } else {
                  int mx = *s.begin();
                  ans[pos] = min(ans[pos], (pos - mx + 1) / 2);
            }

      }

      for (int i = 1; i < n+ 10; ++i) {
            ans[i] = min(ans[i], ans[i - 1] + 1);
      }
      
      for (int i = 0; i < q; ++i) {
            int x;
            cin >> x;
            cout << ans[x] << '\n';
      }


}