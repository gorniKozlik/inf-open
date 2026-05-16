#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define pb push_back
#define rall(x) x.rbegin(), x.rend()
using namespace std;
using ll = long long;
using ld = long double;

struct ST {
    int n;
    vector<int> tree, add;

    ST (int sz) {
        n = sz;
        tree.resize(n * 4, 0);
        add.resize(n * 4, 0);
    }

    void push(int v, int l, int r) {
        if (!add[v]) return;
        int m = (l + r) / 2;
        tree[v * 2] += add[v];
        tree[v * 2 + 1] += add[v];
        add[v * 2] += add[v];
        add[v * 2 + 1] += add[v];
        add[v] = 0;
    }

    void update(int v, int l, int r, int ql, int qr, int x) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            tree[v] += x;
            add[v] += x;
            return;
        }
        int m = (l + r) / 2;
        push(v, l, r);
        update(v * 2, l, m, ql, qr, x);
        update(v * 2 + 1, m, r, ql, qr, x);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }

    void update(int ql, int qr, int x) {
        update(1, 0, n, ql, qr + 1, x);
    }

    int get() {
        return tree[1];
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> s(n);
    vector<int> x;
    for (auto &[l, r] : s) {
        cin >> l >> r;
        x.pb(l);
        x.pb(r);
    }
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    ST t(n * 2);
    for (auto &[l, r] : s) {
        l = lower_bound(all(x), l) - x.begin();
        r = lower_bound(all(x), r) - x.begin();
        t.update(l, r, 1);
    }
    sort(all(s));
    vector<int> k{t.get()};
    for (int i = 0; i < n / 2; i++) {
        auto &[l1, r1] = s[i];
        auto &[l2, r2] = s[n - i - 1];
        t.update(l1, r1, -1);
        t.update(l2, r2, -1);
        t.update(l1, r2, 1);
        t.update(r1, l2, 1);
        k.pb(t.get());
    }
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        cout << lower_bound(all(k), a) - k.begin() << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) solve();
}