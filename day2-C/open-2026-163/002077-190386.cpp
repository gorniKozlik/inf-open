#include "bits/stdc++.h"

#pragma GCC optimize("03,unroll-loops")

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define len(x) ((int)x.size())

using namespace std;
using ll = long long;
using ld = long double;

const int inf = 1e9;

void solve() {
    int n, tt;
    cin >> n >> tt;
    vector<array<int, 2>> a(n);
    vector<int> w;
    for (auto &[l, r] : a) {
        cin >> l >> r;
        w.push_back(l);
        w.push_back(r);
    }
    sort(all(w));
    w.resize(unique(all(w)) - w.begin());
    for (auto &[l, r] : a) {
        l = lower_bound(all(w), l) - w.begin();
        r = lower_bound(all(w), r) - w.begin();
    }
    int sz = len(w) + 2;
    w.clear();
    w.resize(sz + 1);
    vector<int> pr(sz + 1);
    vector<int> sf(sz + 1);
    for (auto [l, r] : a) {
        ++w[l];
        --w[r + 1];
        ++pr[r + 1];
        ++sf[l];
    }
    for (int i = 0; i < sz; ++i) {
        pr[i + 1] += pr[i];
    }
    for (int i = sz - 1; i >= 0; --i) {
        sf[i] += sf[i + 1];
    }
    int now = 0;
    for (int i = 0; i < len(w); ++i) {
        now += w[i];
        w[i] = now;
    }
    // unordered_map<int, vector<int>> dp;
    vector<int> q(tt), ans(n + 1, inf);
    for (auto &k : q) {
        cin >> k;
    }

    // vector dp(sz, vector<int> (n + 1, inf));
    // for (int i = 0; i < sz; ++i) dp[i][0] = 0;
    auto get = [&](int i, int cnt) {
        int now = inf;
        int l = pr[i];
        int r = sf[i + 1];
        int mn = min(l, r);
        int d = cnt - w[i];
        if (2 * mn >= d) {
            now = (d + 1) / 2;
        } else {
            d -= 2 * mn;
            now = mn;
            l = pr[i + 1] - pr[i];
            r -= mn;
            mn = min(l, r);
            if (mn >= d) {
                now += d;
            } else {
                l -= mn;
                d -= mn;
                now += mn;
                r = sf[i] - sf[i + 1];
                mn = min(l, r);
                if (mn >= d) {
                    now += mn;
                } else {
                    now = inf;
                }
            }
        }
        return now;
    };
    int mx = *max_element(all(w));
    for (auto cnt : q) {
        if (ans[cnt] == inf) {
            if (mx >= cnt) {
                ans[cnt] = 0;
                continue;
            }
            int l = 0, r = sz + 1;
            while (l + 2 < r) {
                int m1 = (l + r + l) / 3;
                int m2 = (l + r + r) / 3;
                auto q1 = get(m1, cnt);
                auto q2 = get(m2, cnt);
                ans[cnt] = min(ans[cnt], min(q1, q2));
                for (int i = m1 + 1; i < min(sz, m1 + 100); ++i) {
                    ans[cnt] = min(ans[cnt], get(i, cnt));
                }
                for (int i = m2 + 1; i < min(sz, m2 + 100); ++i) {
                    ans[cnt] = min(ans[cnt], get(i, cnt));
                }
                if (q1 < q2) {
                    r = m2;
                } else {
                    l = m1;
                }
            }
            for (; l < r; ++l) {
                ans[cnt] = min(ans[cnt], get(l, cnt));
            }
            // for (int i = 0; i < sz; ++i) {
            //     ans[cnt] = min(ans[cnt], get(i, cnt));
            // }
        }
    }
    for (auto k : q) {
        cout << ans[k] << ' ';
    }

    // cout << endl;
    // for (auto [l, r] : a) {
    //     cout << l << ' ' << r << endl;
    // }
    // cout << endl;
    // for (auto h : w) cout << h << ' ';
    // cout << endl;
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
