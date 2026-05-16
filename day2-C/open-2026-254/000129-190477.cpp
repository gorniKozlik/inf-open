#include <bits/stdc++.h>
using namespace std;
#define int int64_t
void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> s;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        s[l]++;
        s[r]--;
    }
    int lf = 0, rf = n, cur = 0;
    vector<pair<int, int>> all(0);
    for (auto to : s) {
        if (to.second == 1) {
            rf--;
            cur++;
        }
        else {
            lf++;
            cur--;
        }
        all.push_back({cur, min(lf, rf)});
    }
    vector<int> ans(n + 1, n + 1);
    for (auto to : all) {
        ans[to.first] = 0;
        for (int i = 1; i <= to.second; i++) {
            ans[to.first + 2 * i] = min(ans[to.first + 2 * i], i);
            ans[to.first + 2 * i - 1] = min(ans[to.first + 2 * i - 1], i);
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int qq = 0; qq < q; qq++) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}