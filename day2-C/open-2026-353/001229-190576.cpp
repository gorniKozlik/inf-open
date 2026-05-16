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
    vector<int> ans(n * 2, 2e9);
    int bal = 0;
    int cl = 0;
    int nop = n;
    for (auto [x, t] : ev) {
        if (t == 1) {
            bal++;
            nop--;
        } else {
            cl++;
            bal--;
        }
        ans[bal] = 0;
        for (int i = 1; i <= min({cl, nop, 10}); i++) {
            ans[bal + i * 2] = min(ans[bal + i * 2], i);
        }
        // if (bal + min(cl, nop) * 2 >= n && (n - bal) % 2 == 0) {
        //     ans[n] = min(ans[n], (n - bal) / 2);
        // }
        if (cl > nop) {
            // if (bal + nop + cl >= n) {
            //     ans[n] = min(ans[n], nop + (cl - nop));
            // }
            for (int i = 1; i <= cl - nop && (bal + nop * 2 + i <= 10); i++) {
                ans[bal + nop * 2 + i] = min(ans[bal + nop * 2 + i], nop + i);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int i = 0; i < q; i++) {
        int cnt; cin >> cnt;
        cout << ans[cnt] << ' ';
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