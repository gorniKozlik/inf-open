#include <bits/stdc++.h>
// #pragma GCC optimize("O3")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
using ll = long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve();

void solve1() {
    auto start = clock();
    while (true) {
        auto now = clock();
        if ((now - start) / CLOCKS_PER_SEC > 1) {
            cout << 2;
            return;
        }
    }
}

int32_t main() {
#ifdef LOCAL
    freopen("Input.txt", "r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}

constexpr ll INF = 1e18;

struct SegTree {
    vector<pair<ll, ll> > d;
    int n;

    SegTree(int n) : n(n) {
        d.resize(n << 2, {INF, 0});
    }

    int upd(int v, int l, int r, int ql, int qr, ll x, int ost) {
        if (ql >= r || l >= qr) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            d[v] = min(d[v], {x, ost});
            return r - l;
        }
        int m = (l + r) >> 1;
        int len = upd(v << 1, l, m, ql, qr, x, ost);
        len += upd(v << 1 | 1, m, r, ql, qr, x + (len + ost) / 2, (len + ost) % 2);
        return len;
    }

    void upd(int l, int r, ll x) {
        upd(1, 0, n, l, r, x, 1);
    }

    vector<ll> ans;

    void get(int v, int l, int r, pair<ll, ll> a) {
        if (l + 1 == r) {
            ans.emplace_back(min(d[v].first, a.first));
            return;
        }
        int m = (l + r) >> 1;
        get(v << 1, l, m, min(d[v], a));
        get(v << 1 | 1, m, r, {
                min(a, d[v]).first + (m - l + min(a, d[v]).second) / 2,
                (m - l + min(a, d[v]).second) % 2
            });
    }

    vector<ll> get() {
        get(1, 0, n, {INF, 0});
        return ans;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n), cord;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        cord.emplace_back(l[i]);
        cord.emplace_back(r[i]);
    }
    sort(cord.begin(), cord.end());
    cord.resize(unique(cord.begin(), cord.end()) - cord.begin());
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    SegTree a(n + 10);
    int ind = 0;
    for (int c: cord) {
        int LEFT = lower_bound(r.begin(), r.end(), c) - r.begin(); // меньших
        int RIGHT = n - (lower_bound(l.begin(), l.end(), c) - l.begin()); // больших равных
        int tyt = n - LEFT - RIGHT;
        int len = min(LEFT, RIGHT);
        a.upd(tyt, tyt + 2 * len + 1, 0);
        // for (int i = 0; i <= len; ++i, tyt += 2) {
        //     // ans[tyt] = min(ans[tyt], i);
        //     cout << tyt << ' ' << i  << '\n';
        // }
        ind++;
    }
    auto ans = a.get();
    ll nw = 1e18;
    for (int i = n + 9; i >= 0; --i) {
        nw = min<ll>(nw, ans[i]);
        ans[i] = nw;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << '\n';
    }
}
