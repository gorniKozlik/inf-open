#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// gp_hash_table<ll, ll> ht;


struct Node {
    ll res;
    ll push = 0;

    Node(ll res): res(res) {}

    Node(): res(0) {}

    void apply(ll x) {
        res += x;
        push += x;
    }
};

Node merge(const Node& left, const Node& right) {
    return Node(max(left.res, right.res));
}

struct SegmentTree {
    ll n;
    vector<ll> a;
    vector<Node> tree;

    SegmentTree(const vector<ll>& arr): n(arr.size()), a(arr), tree(4 * n) {
        build(0, 0, n);
    }

    void build(ll v, ll l, ll r) {
        if (r - l == 1) {
            tree[v] = {a[l]};
            return;
        }

        ll mid = (r + l) / 2;
        build(2 * v + 1, l, mid);
        build(2 * v + 2, mid, r);

        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void push(ll v) {
        ll x = tree[v].push;
        if (x == 0) {
            return;
        }

        tree[v].push = 0;
        tree[2 * v + 1].apply(x);
        tree[2 * v + 2].apply(x);
    }

    void update(ll ql, ll qr, ll x, ll v, ll l, ll r) {
        if (qr <= l || r <= ql) {
            return;
        }

        if (ql <= l && r <= qr) {
            tree[v].apply(x);
            return;
        }

        push(v);
        ll mid = (r + l) / 2;
        update(ql, qr, x, 2 * v + 1, l, mid);
        update(ql, qr, x, 2 * v + 2, mid, r);

        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void update(ll ql, ll qr, ll x) {
        update(ql, qr, x, 0, 0, n);
    }

    Node get(ll ql, ll qr, ll v, ll l, ll r) {
        if (qr <= l || r <= ql) {
            return {};
        }

        if (ql <= l && r <= qr) {
            return tree[v];
        }

        ll mid = (r + l) / 2;
        push(v);
        return merge(get(ql, qr, 2 * v + 1, l, mid), get(ql, qr, 2 * v + 2, mid, r));
    }

    ll get(ll ql, ll qr) {
        return get(ql, qr, 0, 0, n).res;
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, q;
    cin >> n >> q;

    vector<pair<ll, ll>> a(n);
    vector<pair<ll, ll>> left, right;
    vector<ll> coords;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        left.push_back({a[i].first, i});
        right.push_back({a[i].second, i});
        coords.push_back(a[i].first);
        coords.push_back(a[i].second);
    }

    sort(coords.begin(), coords.end());
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    vector<ll> temp(coords.size());
    SegmentTree st(temp);

    auto get = [&](ll x) {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
    };

    for (auto [c, i] : left) {
        st.update(get(c), temp.size(), 1);
    }

    for (auto [c, i]: right) {
        st.update(get(c), temp.size(), -1);
    }

    vector<ll> vers;

    vers.push_back(st.get(0, temp.size()));
    for (ll i = 0; i < n; ++i) {
        if (left[i].second == right[n - i - 1].second) {
            continue;
        }

        auto [l1, r1] = a[left[i].second];
        auto [l2, r2] = a[right[n - i - 1].second];

        if (r1 > l2) {
            continue;
        }
        // cout << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << '\n';
        st.update(get(r1), temp.size(), 1);
        st.update(get(l2), temp.size(), -1);

        ll l = min(l2, r1);
        ll r = max(l2, r1);
        st.update(get(l), temp.size(), 1);
        st.update(get(r), temp.size(), -1);

        // cout << l << ' ' << r << '\n';

        // for (ll j = 0; j < (ll)temp.size(); ++j) {
        //     cout << st.get(j, j + 1) << ' ';
        // }
        // cout << '\n';

        vers.push_back(st.get(0, temp.size()));
    }

    // for (auto el : vers) {
    //     cout << el << ' ';
    // }
    // cout << '\n';

    while (q--) {
        ll k;
        cin >> k;
        cout << lower_bound(vers.begin(), vers.end(), k) - vers.begin() << ' ';
    }

    return 0;
}
