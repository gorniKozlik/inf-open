#pragma GCC optimize("O3,unroll-loops")
#include <string>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

struct Line {
    int l;
    int r;
};

struct SegTree {
    vector<ll>tree;

    void Update (int u, int l, int r, int pos, ll x) {
        if (r - l == 1) {
            tree[u] = x;
            return;
        }
        int m = (l + r) >> 1;
        if (pos < m) {
            Update(2 * u + 1, l, m, pos, x);
        }
        else {
            Update(2 * u + 2, m, r, pos, x);
        }
        tree[u] = max(tree[2 * u + 1], tree[2 * u + 2]);
    }

    ll Get (int u, int l, int r, int left, int right) {
        if (left <= l && r <= right) {
            return tree[u];
        }
        if (right <= l || r <= left) {
            return 0;
        }
        int m = (l + r) >> 1;
        ll max1 = Get(2 * u + 1, l, m, left, right);
        ll max2 = Get(2 * u + 2, m, r, left, right);
        return max(max1, max2);
    }

    SegTree (int n) {
        tree.resize(4 * n);
    }
};

void Solve () {
    int n, q;
    cin >> n >> q;
    vector<Line>a(n);
    for (auto& [l, r] : a) {
        cin >> l >> r;
    }
    vector<pair<int, int>>b;
    for (int i = 0; i < n; ++i) {
        b.push_back({a[i].l, i});
        b.push_back({a[i].r, i});
    }
    sort(b.begin(), b.end());
    SegTree st(2 * n);
    vector<int>maxi(2 * n);
    vector<int>c(n);
    for (int i = 1; i < 2 * n; ++i) {
        c[b[i - 1].second]++;
        if (c[b[i - 1].second] == 2) {
            st.Update(0, 0, 2 * n, i, maxi[i - 1] - 1);
            maxi[i] = maxi[i - 1] - 1;
        }
        else {
            st.Update(0, 0, 2 * n, i, maxi[i - 1] + 1);
            maxi[i] = maxi[i - 1] + 1;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        int ans = st.Get(0, 0, 2 * n, x, 2 * n - x + 1);
        cout << max(0, (x - ans + 1) / 2) << ' ';
    }
}

signed main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        Solve();
    }
}