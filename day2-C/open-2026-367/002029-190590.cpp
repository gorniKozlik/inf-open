#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
const int inf = 0x3f3f3f3f;
const ll mod = 998'244'353;
const ll INF = 2e16;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(x) 67
#endif


void solve() {
    int n, q; cin >> n >> q;
    vector<pii> a(n);
    vector<int> var;
    for (auto &[l, r] : a) {
        cin >> l >> r;
        var.push_back(l);
        var.push_back(r);
    }
    sort(all(var));
    var.resize(unique(all(var)) - var.begin());
    debug(var);
    for (auto &[l, r] : a) {
        int l0 = l, r0 = r;
        l = lower_bound(all(var), l0) - var.begin();
        r = lower_bound(all(var), r0) - var.begin();
    }
    debug(a);
    vector<int> delta(2 * n + 1);
    vector<int> cnt(2 * n);
    for (auto [l, r] : a) {
        delta[l]++;
        delta[r + 1]--;
    }
    int now = 0;
    for (int i = 0; i < 2 * n; ++i) {
        now += delta[i];
        cnt[i] = now;
    }
    debug(cnt);
    int maxi = 0;
    for (int i = 0; i < 2 * n; ++i) {
        maxi = max(maxi, cnt[i]);
    }
    debug(maxi);
    vector<int> ans(n + 1);
    for (int i = 1; i <= maxi; ++i) {
        ans[maxi] = 0;
    }
    for (int i = maxi; i <= n; i += 2) {
        ans[i] = ans[i + 1] = ans[i - 1] + 1;
    }
    debug(ans);
    while (q--) {
        int k; cin >> k;
        cout << ans[k] << ' ';
    }
}

signed main() {
#ifndef LOCAL
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#endif
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
        if (tt) {
            cout << '\n';
        }
    }
}