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

    int get(int v, int l, int r, int ind) {
        if (r - l == 1) return tree[v];
        int m = (l + r) / 2;
        push(v, l, r);
        if (ind < m) return get(v * 2, l, m, ind);
        return get(v * 2 + 1, m, r, ind);
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
    vector<pair<int, int>> sr = s;
    for (auto &[l, r] : sr) swap(l, r);
    sort(all(sr));
    vector<int> mx2(n * 2, -1e9), mx1(n * 2, -1e9);
    for (int i = 0; i < x.size(); i++) {
        int cur = t.get(1, 0, n * 2, i);
        int rf = n - (upper_bound(all(s), make_pair(i, n * 2)) - s.begin());
        int lf = (lower_bound(all(sr), make_pair(i, 0)) - sr.begin());
        mx2[min(lf, rf)] = max(mx2[min(lf, rf)], cur + 2 * min(lf, rf));
        mx1[lf + rf - min(lf, rf)] = max(mx1[lf + rf - min(lf, rf)], cur + lf + rf);
    }
    for (int i = 1; i < n * 2; i++) {
        mx2[i] = max(mx2[i], mx2[i - 1] + 1);
    }
    for (int i = n * 2 - 2; i >= 0; i--) {
        mx2[i] = max(mx2[i], mx2[i + 1] - 2);
    }
    vector<int> p1{0}, p2{0};
    for (int i = 0; i < n * 2; i++) {
        p1.pb(max(p1.back(), mx2[i]));
    }
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        cout << lower_bound(all(p1), a) - p1.begin() - 1 << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) solve();
}