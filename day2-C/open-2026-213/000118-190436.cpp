#ifndef LOCAL
#pragma GCC Optimize("O3, Ofast")
#pragma GCC Target("avx,avx2,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

#define int ll
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#ifndef LOCAL
#define endl "\n"
#endif

struct F {
    vector<int> t;
    F(int n) {
        t.assign(n, 0);
    }
    int get(int r) {
        int ans = 0;
        for (; r >= 0; r = (r&(r + 1)) - 1) {
            ans += t[r];
        }
        return ans;
    }
    void upd(int i, int x) {
        for (; i < t.size(); i = (i|(i + 1))) {
            t[i] += x;
        }
    }
};

mt19937 rnd(time(0));

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> seg(n);
    for (int i = 0; i < n; ++i) {
        cin >> seg[i].f >> seg[i].s;
    }
    auto calc = [&]() {
        vector<pii> delta;
        for (auto &x : seg) {
            delta.pb(mp(x.f, (ll)1));
            delta.pb(mp(x.s, (ll)-1));
        }
        sort(all(delta));
        int now = 0, ans = 0;
        for (auto &x : delta) {
            now += x.s;
            ans = max(ans, now);
        }
        return ans;
    };
    vector<int> ans(n + 1);
    int now = calc();
    for (int i = now + 1; i <= n; ++i) {
        ans[i] = 1e9;
    }
    int cnt = 0;
    while (true) {
        int L = 0, R = 0;
        for (int i = 0; i < n; ++i) {
            if (seg[i].s < seg[L].s) {
                L = i;
            }
            if (seg[i].f > seg[R].f) {
                R = i;
            }
        }
        if (seg[L].s < seg[R].f) {
            ++cnt;
            int was = seg[L].s;
            seg[L].s = seg[R].f;
            seg[R].f = was;
            int res = calc();
            for (int i = now + 1; i <= res; ++i) {
                ans[i] = cnt;
            }
            now = res;
        } else {
            break;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
    cout << endl;
}

signed main() {
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        ios::sync_with_stdio(false);
        cin.tie(0);
    #endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}