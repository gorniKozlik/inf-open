#include "bits/stdc++.h"
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

using namespace std;
// using namespace __gnu_pbds;
// template<class T> 
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
using ll = long long;
using ld = long double;

// #define int long long

struct Segtree {
    int n;
    vector<int> tree;
    vector<int> add;
    Segtree(int n) : n(n) {
        tree.assign(4 * n, 0);
        add.assign(4 * n, 0);
    }

    void push(int v) {
        if (add[v] != 0) {
            add[2 * v + 1] += add[v];
            add[2 * v + 2] += add[v];
            tree[2 * v + 1] += add[v];
            tree[2 * v + 2] += add[v];
            add[v] = 0;
        }
    }

    void upd(int v, int l, int r, int ql, int qr, int x) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            tree[v] += x;
            add[v] += x;
            return;
        }
        push(v);
        int m = (l + r) / 2;
        upd(2 * v + 1, l, m, ql, qr, x);
        upd(2 * v + 2, m, r, ql, qr, x);
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }
    void upd(int ql, int qr, int x) {
        upd(0, 0, n, ql, qr, x);
    }

    int get_max() {
        return tree[0]; 
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> vals;
    vector<pair<int, int>> aa;
    set<pair<int, int>> a; // [-l, -r]
    set<pair<int, int>> b; // [r, l]
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        aa.emplace_back(l, r);
        vals.emplace_back(l);
        vals.emplace_back(r);
    }

    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    for (auto& [l, r] : aa) {
        l = lower_bound(all(vals), l) - vals.begin();
        r = lower_bound(all(vals), r) - vals.begin();
        a.emplace(-l, -r);
        b.emplace(r, l);
    }

    Segtree tree(2 * n + 1);
    for (auto& [l, r] : a) {
        tree.upd(-l, -r + 1, 1);
    }

    vector<int> ans(n + 1);
    int can = 0;
    int cnt = 0;
    while (can < n) {
        int ncan = tree.get_max();
        for (int i = can + 1; i <= ncan; ++i) {
            ans[i] = cnt;
        }
        can = ncan;

        cnt++;
        pair<int, int> seg1 = *a.begin();
        pair<int, int> seg2 = *b.begin();
        a.erase(seg1);
        a.erase({-seg2.second, -seg2.first});
        b.erase(seg2);
        b.erase({-seg1.second, -seg1.first});
        swap(seg2.first, seg2.second);
        seg1.first = -seg1.first;
        seg1.second = -seg1.second;
        swap(seg1, seg2);

        tree.upd(seg1.first, seg1.second + 1, -1);
        tree.upd(seg2.first, seg2.second + 1, -1);

        pair<int, int> ns1 = {seg1.first, seg2.first};
        pair<int, int> ns2 = {seg1.second, seg2.second};

        tree.upd(ns1.first, ns1.second + 1, 1);
        tree.upd(ns2.first, ns2.second + 1, 1);

        a.emplace(-ns1.first, -ns1.second);
        a.emplace(-ns2.first, -ns2.second);
        b.emplace(ns1.second, ns1.first);
        b.emplace(ns2.second, ns2.first);
    }
    while (q--) {
        int i;
        cin >> i;
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifdef LOCAL
    freopen("C:\\Users\\User\\Documents\\olymp\\input.txt", "r", stdin);
    freopen("C:\\Users\\User\\Documents\\olymp\\output.txt", "w", stdout);
    #endif

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}