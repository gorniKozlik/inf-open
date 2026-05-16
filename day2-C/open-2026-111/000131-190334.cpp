#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll=long long;
#define int ll

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define fi first
#define sc second

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(2 * n);
    vector<int> tmp;
    vector<pair<int, int>> vv;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        tmp.push_back(l);
        tmp.push_back(r);
        vv.push_back({l, r});
    }
    sort(all(tmp));
    for (auto &i : vv) {
        i.first = lower_bound(all(tmp), i.first) - tmp.begin();
        i.second = lower_bound(all(tmp), i.second) - tmp.begin();
        v[i.first]++;
        v[i.second]--;
    }
    vector<int> ans(n);
    int bal = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        bal += v[i];
        ans[min(i + 1, 2 * n - i - 1)] = max(ans[min(i + 1, 2 * n - i - 1)], bal);
    }
    for (int i = n - 2; i >= 0; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << max(0ll, (k - ans[k - 1] + 1) / 2) << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
