#include <bits/stdc++.h>


using namespace std;
using ll = long long;
using ld = long double;
using sll = __int128;



void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> ev(n * 2);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        ev[i * 2] = {l, 1};
        ev[i * 2 + 1] = {r , -1};
    }
    sort(ev.begin(), ev.end());
    vector<array<int, 2>> ans(n * 2, {(int)2e9, (int)2e9});
    int bal = 0;
    int cl = 0;
    int mx = 0;
    int nop = n;
    for (auto [x, t] : ev) {
        if (t == 1) {
            bal++;
            nop--;
        } else {
            cl++;
            bal--;
        }
        mx = max(mx, bal);
        ans[bal + min(nop, cl) * 2][0] = min(nop, cl);
        if (cl > nop) {
            for (int i = 1; i <= bal; i++) {
                ans[nop + i][1] = min(ans[nop + i][1], nop + i);
            }
        }

    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i][0] = min(ans[i][0], ans[i + 2][0] - 1);
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i][1] = min(ans[i][1], ans[i + 1][1]);
    }
    for (int i = 0; i < q; i++) {
        int cnt; cin >> cnt;
        cout << min(ans[cnt][0], ans[cnt][1]) << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int test = 1;
    // cin >> test;
    while (test--) {
        solve();
    }
}