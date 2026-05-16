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
    vector<int> open(2 * n + 1);
    vector<int> close(2 * n + 1);
    vector<int> cnt(2 * n);
    for (auto [l, r] : a) {
        open[l]++;
        close[r + 1]++;
    }
    int now = 0;
    for (int i = 0; i < 2 * n; ++i) {
        now += open[i] - close[i];
        cnt[i] = now;
    }
    debug(cnt);
    vector<int> ans(n + 1, inf);
    vector<int> mem(n + 1, inf);
    auto upd = [&](int maxi, int l, int r) {
        mem.assign(n + 1, inf);
        for (int i = 1; i <= maxi; ++i) {
            mem[i] = 0;
        }
        int i = maxi + 1;
        while (l > 0 && r > 0) {
            mem[i] = mem[i - 1] + 1;
            mem[i + 1] = mem[i - 1] + 1;
            l--;
            r--;
            i += 2;
        }
        while (l > 0 || r > 0) {
            mem[i] = mem[i - 1] + 1;
            i++;
            l--;
            r--;
        }
        for (int i = 1; i <= n; ++i) {
            ans[i] = min(ans[i], mem[i]);
        }
    };
    int left = 0, right = n;
    now = 0;
    for (int i = 0; i <= 2 * n; ++i) {
        left += close[i];
        right -= open[i];
        now += open[i] - close[i];
        upd(now, left, right);
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