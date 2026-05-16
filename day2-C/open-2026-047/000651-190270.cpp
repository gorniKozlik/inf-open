// #pragma GCC optimize("O3,fast-math,unroll-loops")
#include <bits/stdc++.h>

#define i64 int64_t
#define vi vector<int>
#define vvi vector<vi>
#define vc vector
#define vb vc<bool>
#define pb push_back
#define pii pair<int, int>
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

using namespace std;

template <typename T>

istream& operator>>(istream& in, vector<T> &a) {
    for (T &el : a) in >> el;
    return in;
}

template <typename T>

ostream& operator<<(ostream& out, vector<T> a) {
    for (T &el : a) out << el << " ";
    return out;
}


void solve() {
    int n, q;
    cin >> n >> q;
    vc<pii> p(n);
    vi a;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].fi >> p[i].se;
        a.pb(p[i].fi);
        a.pb(p[i].se);
    }
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    for (int i = 0; i < n; ++i) {
        p[i].fi = lower_bound(all(a), p[i].fi) - a.begin();
        p[i].se = lower_bound(all(a), p[i].se) - a.begin();
    }
    int mx = 0;
    vi ans(n + 1, 1e9);
    for (int i = 0; i < a.size(); ++i) {
        int x = a[i];
        int cnt = 0;
        int cnt_l = 0;
        int cnt_r = 0;  
        for (pii el : p) {
            if (el.se < x) ++cnt_l;
            if (el.fi > x) ++cnt_r;
        }
        cnt = n - cnt_l - cnt_r;
        int l = cnt;
        int r = cnt + min(cnt_l, cnt_r) * 2;
        bool is = 1;
        for (pii el : p) {
            if (x == el.se) is = 0;
        }
        if (cnt_l > cnt_r && is) ++r;
        else if (cnt_l < cnt_r && !is) ++r;
        for (int i = l; i <= r; ++i) ans[i] = min(ans[i], (i - l + 1) / 2);
        mx = max(mx, l);
    }
    while (q--) {
        int k;
        cin >> k;
        if (k <= mx) cout << 0 << ' ';
        else cout << ans[k] << ' ';
    }
}

int32_t main() {
    // freopen("inputa.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}