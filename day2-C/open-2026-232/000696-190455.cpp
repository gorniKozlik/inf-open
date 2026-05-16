#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()


void solve() {
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        ev.push_back({l, -1});
        ev.push_back({r, 1});
    }
    sort(all(ev));
    int cnt = 0;
    int cur = 0;
    int closed = 0;
    vector <vector <int>> l(n + 1), r(n + 1);
    vector <pair <int, int>> seg;
    int mx = 0;
    for (int i = 0; i < 2 * n; i++) {
        cnt -= ev[i].second;
        if (ev[i].second == 1) {
            closed++;
        }
        while (i + 1 < 2 * n && ev[i + 1].first == ev[i].first && ev[i + 1].second == -1) {
            cnt -= ev[++i].second;
        }
        mx = max(mx, cnt);
        int pot = 2 * min(closed, n - closed - cnt);
        l[cnt].push_back(seg.size());
        r[cnt + pot].push_back(seg.size());
        seg.push_back({cnt, cnt + pot});
    }
    vector <int> ans(n + 1, 1e9);
    set <pair <int, int>> st;
    for (int i = 0; i <= n; i++) {
        for (auto k : l[i]) {
            st.insert({seg[k].first, k});
        }
        auto it = st.upper_bound({i, 1e9});
        if (it != st.begin()) {
            it--;
            ans[i] = (i - it->first + 1) / 2;
        }
        for (auto k : r[i]) {
            st.erase({seg[k].first, k});
        }
    }
    while (q--) {
        int x;
        cin >> x;
        if (x <= mx) {
            cout << "0 ";
        } else {
            cout << ans[x] << ' ';
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}

// Halal code
