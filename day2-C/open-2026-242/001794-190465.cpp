#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

using oset = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> ans(n + 1, LLONG_MAX);
    vector<int> vv2(n + 1, LLONG_MAX);
    vector<vector<int>> v1l(n + 1), v1r(n + 1);

    for (int i = 0; i < n; i++) {
        int r = a[i].second;
        int l = a[i].first;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (a[j].second >= r && a[j].first >= a[i].first && a[j].first <= r) {
                l = max(l, a[j].first);
            }
        }
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (a[j].first <= l && a[j].second >= r) cnt++;
        }
        int cl = 0, cr = 0;
        for (int j = 0; j < n; j++) {
            if (a[j].second < l) cl++;
            else if (a[j].first > r) cr++;
        }
        for (int j = 1; j <= cnt; j++) {
            ans[j] = 0;
        }
        int lx = cnt + 1;
        int rx = cnt + min(cl, cr) * 2;
        if (lx <= rx && lx <= n) {
            v1l[lx].push_back(1);
            if (rx + 1 <= n) {
                v1r[rx + 1].push_back(lx);
            }
        }
        /*for (int j = cnt + 1; j <= cnt + min(cl, cr) * 2; j++) {
            ans[j] = min(ans[j], (j - cnt + 1) / 2);
        }*/
        int x = min(cl, cr) + 1;
        int ll = cnt + min(cl, cr) * 2 + 1;
        if (ll <= n) {
            vv2[ll] = min(vv2[ll], x - ll);
        }
    }
    int xx = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        xx = min(xx, vv2[i]);
        if (xx != LLONG_MAX) {
            ans[i] = min(ans[i], i + xx);
        }
    }
    multiset<int> ms;
    for (int i = 1; i <= n; i++) {
        for (auto el : v1r[i]) {
            ms.erase(ms.lower_bound(el));
        }
        for (auto el : v1l[i]) {
            ms.insert(i);
        }
        if (!ms.empty()) {
            int xi = *ms.rbegin();
            ans[i] = min(ans[i], (i - xi + 2) / 2);
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}