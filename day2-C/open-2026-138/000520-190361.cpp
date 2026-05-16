#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll

const ll inf = 1e9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> tr;
    tr.reserve(n * 2);
    vector<pair<int, int> > a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        tr.emplace_back(a[i].first);
        tr.emplace_back(a[i].second);
    }
    sort(tr.begin(), tr.end());
    tr.resize(unique(tr.begin(), tr.end()) - tr.begin());
    for (auto &[x,y]: a) {
        x = lower_bound(tr.begin(), tr.end(), x) - tr.begin();
        y = lower_bound(tr.begin(), tr.end(), y) - tr.begin();
    }
    vector<pair<int, int> > ev;
    for (int i = 1; i <= n; i++) {
        ev.emplace_back(a[i].first, 1);
        ev.emplace_back(a[i].second, 2);
    }
    sort(ev.begin(), ev.end());
    int cur = 0;
    int left = 0;
    vector<int> ans(n + 1, inf);
    for (auto [x, t]: ev) {
        if (t == 1) {
            cur++;
            left++;
        } else {
            cur--;
        }
        int dv = min(left - cur, n - left);
        int val = cur;
        int price = 0;
        while (val <= 10 || val == cur) {
            ans[val] = min(ans[val], price);
            price++;
            if (dv > 0) {
                val += 2;
                dv--;
            } else {
                val++;
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int i = 0, k; i < q; i++) {
        cin >> k;
        cout << ans[k] << " ";
    }
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int ts = 1; ts <= t; ts++) {
        solve();
    }
}
