#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
mt19937 rnd(67);

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi2,lzcnt,popcnt")

void C() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> ev(2 * n);
    vector<int> ans(n + 1, n);
    for (int i = 0; i < n; ++i) {
        // cin >> v[i].ff >> v[i].ss;
        int x, y; cin >> x >> y;
        ev[2 * i] = {x, 1};
        ev[2 * i + 1] = {y, -1};
    }
    sort(ev.begin(), ev.end());
    // vector<pair<int, int>> o(2 * n);
    int open = 0;
    int close = 0;
    int mx = 0, mx1 = 0;
    vector<int> suf(n + 1);
    // vector<int> suf1(n + 1);
    for (int i = 0; i < 2 * n; ++i) {
        if (ev[i].second == 1) open++;
        else close++;
        // mx = max(mx, open - close);
        ans[open - close] = 0;
        // o[i] = {open, close};
        int K = open - close + 2 * min(close, n - open);
        // cout << open << ' ' << close << ' ' << K << '\n';
        if (min(close, n - open)) {
            // if (K % 2 == 0) mx = max(mx, K);
            // else mx1 = max(mx1, K);
            suf[K - 1]++;
            suf[K - 2 * min(close, n - open)]--;
            ans[K] = min(ans[K], min(close, n - close));
        }
            // ans[K - 2 * ] = min(ans[K], min(close, n - close));
            // ans[K - 1] = min(ans[K], ans[K - 1]);
        // if (i % 2 == 0) {
        //     suf[K]++;
        //     suf[K - 2 * min(close, n - open)]--;
        // } else {
        //     suf1[K]++;
        //     suf[K - 2 * min(close, n - open)]--;
        // }
        // cout << ev[i].first << ' ' << open - close + 2 * min(close, n - open) << ' ' << min(close, open) << '\n';
    }
    // int s = suf[n];
    // for (int i = n - 1; i >= 0; --i) {
    //     ans[i] = min(ans[i], ans[i + 1]);
    //     if (s && i < n - 1) {
    //         ans[i] = min(ans[i], ans[i + 2] - 1);
    //     }
    //     s += suf[i];
    //     // s1 += suf1[i];
    // }

    int s = suf[n];

    // cout << mx << ' ' << mx1 << '\n';
    for (int i = n - 1; i >= 0; --i) {
        // cout << s << '\n';
        if (i < n - 1 && s) ans[i] = min(ans[i + 2] - 1, ans[i]);
        s += suf[i];
    }
    for (int i = 1; i <= n; ++i) {
        ans[i] = min(ans[i - 1] + 1, ans[i]);
    }

    while (q--) {
        int k; cin >> k;
        cout << ans[k] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cout << setprecision(10) << fixed;

    int ttt = 1;
    // cin >> ttt;
    while (ttt--) {
        C();
    }
}