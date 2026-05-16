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
        for (int j = cnt + 1; j <= cnt + min(cl, cr) * 2; j++) {
            ans[j] = min(ans[j], (j - cnt + 1) / 2);
        }
        int x = min(cl, cr) + 1;
        for (int j = cnt + min(cl, cr) * 2 + 1; j <= n; j++) {
            ans[j] = min(ans[j], x);
            x++;
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