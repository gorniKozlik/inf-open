#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <experimental/random>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
using str = string;
using ld = long double;
const ll INF = 1e18, MOD = 998244353;
#define int long long

void solve();

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _ = 1;
    // cin >> _;
    while (_--) {
        solve();
        // cout << "\n";
    }
}

void solve() {
    int q, n;
    cin >> q >> n;
    vector<pair<int,int> > a(n);
    set<int> v;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        v.insert(a[i].first);
        v.insert(a[i].second);
    }
    int o = 0;
    map<int,int> col;
    for (auto k: v) {
        col[k] = o++;
    }
    for (int i = 0; i < n; ++i) {
        a[i].first = col[a[i].first];
        a[i].second = col[a[i].second];
    }
    vector<int> f(2 * n);
    for (int i = 0; i < n; ++i) {
        f[a[i].first] = 1;
        f[a[i].second] = -1;
    }
    int sum = 0;
    int sum1 = 0;
    vector<pair<int,int> > c;
    for (int i = 0; i < 2 * n; ++i) {
        sum += f[i];
        if (f[i] == -1) {
            sum1++;
        } else {
            c.push_back({sum, sum1});
        }
    }
    vector<int> ans(n + 1, INF);
    sort(c.begin(), c.end());
    reverse(c.begin(), c.end());
    int mx = -1;
    for (auto k: c) {
        int e = min(k.second, n - k.first - k.second);
        if (e <= mx) {
            continue;
        }
        mx = e;
        for (int i = 0; i <= k.first; ++i) {
            ans[i] = 0;
        }
        for (int i = k.first; i <= k.first + 2 * e; ++i) {
            ans[i] = min(ans[i], (i - k.first + 1) / 2);
        }
        for (int i = k.first + 1 + 2 * e; i <= n; ++i) {
            ans[i] = min(ans[i], ans[i - 1] + 1);
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << "\n";
    }
}
