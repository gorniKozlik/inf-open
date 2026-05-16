#include "bits/stdc++.h"

#pragma GCC optimize("03,unroll-loops")

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define len(x) ((int)x.size())

using namespace std;
using ll = long long;
using ld = long double;

#define int ll

const int inf = 1e18;

void solve() {
    int n, m, k, x;
    cin >> n >> m >> k >> x;
    vector<array<int, 2>> a(n);
    for (auto &[h, r] : a) cin >> h >> r;
    vector<array<int, 2>> b(m);
    for (auto &[h, r] : b) cin >> h >> r;
    sort(all(b));
    vector<int> mn(m + 1, inf);
    vector<int> ind(m + 1, -1);
    for (int i = m - 1; i >= 0; --i) {
        if (b[i][1] < mn[i + 1]) {
            ind[i] = b[i][0];
        } else {
            ind[i] = ind[i + 1];
        }
        mn[i] = min(mn[i + 1], b[i][1]);
    }
    auto get = [&](int h) {
        array<int, 2> st = {h, 0};
        auto lw = lower_bound(all(b), st) - b.begin();
        st = {mn[lw], ind[lw]};
        return st;
    };
    vector<int> dp(n + 1, -1);
    dp[0] = x;
    for (int i = 1; i <= n; ++i) {
        int now = dp[i - 1];
        for (auto [pw, cs] : b) {
            if (cs <= now && pw >= a[i - 1][0]) {
                int bl = now - cs;
                for (int j = i; j <= n; ++j) {
                    if (a[j - 1][0] > pw) break;
                    bl += a[j - 1][1];
                    dp[j] = max(dp[j], bl);
                }
            }
        }
    }
    if (dp[n] < 0) {
        cout << "No";
    } else {
        cout << "Yes";
    }
    // vector sp(__lg(n) + 1, vector<array<int, 2>> (n));
    // sp[0] = a;
    // for (int t = 0; t + 1 < len(sp); ++t) {
    //     for (int i = 0; i + (1 << t) < n; ++i) {
    //         sp[t + 1][i][0] = max(sp[t][i][0], sp[t][i + (1 << t)][0]);
    //         sp[t + 1][i][1] = sp[t][i][1] + sp[t][i + (1 << t)][1];
    //     }
    // }
    // // [ ]
    // auto get_mx = [&](int l, int r) {
    //     int sz = __lg(r - l + 1);
    //     auto q1 = sp[sz][l];
    //     auto q2 = sp[sz][r + 1 - (1 << sz)];
    //     q1[0] = max(q1[0], q2[0]);
    //     q1[1] += q2[1];
    //     return q1;
    // };
    // auto get_mn = [&](int j, int i) {
    //     auto [h, r] = get_mx(j, i);
    //     return get(h);
    // };
    // vector<int> dp(n + 1, inf);
    // dp[0] = x;
    // auto min_cost = get(a[0][0]);
    // if (min_cost <= x) {
    //     dp[1] = x - min_cost + a[0][1];
    // }
    // for (int i = 2; i <= n; ++i) {
    //     dp[i] = min(dp[i], get_mn(0, i - 1));
    //     for (int j = 1; j < i; ++j) {
    //         dp[i] = min(dp[i], max(dp[j], get_mn(j, i - 1)));
    //     }
    // }
    // if (dp[n] <= x) {
    //     cout << "Yes";
    // } else {
    //     cout << "No";
    // }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    // cin >> _;
    while (_--) {
        solve();
        cout << '\n';
    }
}
