#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> t, add;
    int n;
    SegmentTree(const vector<int> &a) {
        n = a.size();
        t.resize(4 * n);
        add.resize(4 * n);
        build(0, 0, n, a);
    }
    void build(int v, int l, int r, const vector<int> &a) {
        if (r - l == 1) {
            t[v] = a[l];
        } else {
            build(v * 2 + 1, l, (l + r) / 2, a);
            build(v * 2 + 2, (l + r) / 2, r, a);
            t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
    void push(int v, int l, int r) {
        if (add[v] == 0 || r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        t[v * 2 + 1] += add[v];
        t[v * 2 + 2] += add[v];
        add[v * 2 + 1] += add[v];
        add[v * 2 + 2] += add[v];
        add[v] = 0;
    }
    int get(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return t[v];
        } else if (l >= qr || ql >= r) {
            return 0;
        } else {
            push(v, l, r);
            return get(v * 2 + 1, l, (l + r) / 2, ql, qr) + get(v * 2 + 2, (l + r) / 2, r, ql, qr);
        }
    }
    void edit(int v, int l, int r, int ql, int qr, int x) {
        if (ql <= l && r <= qr) {
            t[v] += x;
            add[v] += x;
        } else if (l >= qr || ql >= r) {
            return;
        } else {
            push(v, l, r);
            edit(v * 2 + 1, l, (l + r) / 2, ql, qr, x);
            edit(v * 2 + 2, (l + r) / 2, r, ql, qr, x);
            t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> a(n);
    vector<int> sor(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        sor[2 * i] = a[i].first;
        sor[2 * i + 1] = a[i].second;
    }
    sort(sor.begin(), sor.end());
    for (auto &[l, r] : a) {
        l = lower_bound(sor.begin(), sor.end(), l) - sor.begin();
        r = lower_bound(sor.begin(), sor.end(), r) - sor.begin();
    }
    vector<int> ans(n + 1, 1000000000);
    vector<int> cn(2 * n);
    vector<pair<int, int>> evs;
    for (int i = 0; i < n; ++i) {
        evs.emplace_back(a[i].first, -1);
        evs.emplace_back(a[i].second, 1);
        evs.emplace_back(i, 0);
        evs.emplace_back(i + n, 0);
    }
    sort(evs.begin(), evs.end());
    int cur = 0;
    for (auto [tm, tp] : evs) {
        if (tp == 0) {
            cn[tm] = cur;
        } else {
            cur -= tp;
        }
    }
    int alr = *max_element(cn.begin(), cn.end());
    for (int i = 0; i <= alr; ++i) {
        ans[i] = 0;
    }
    int ops = 0;
    set<pair<int, int>> byL, byR;
    auto removeSeg = [&](int i) {
        byL.erase({a[i].first, i});
        byR.erase({a[i].second, i});
    };
    auto insertSeg = [&](int i) {
        byL.emplace(a[i].first, i);
        byR.emplace(a[i].second, i);
    };
    for (int i = 0; i < n; ++i) {
        insertSeg(i);
    }
    SegmentTree sgt(cn);
    while (alr != n) {
        ops++;
        int minR = byR.begin()->first, i1 = byR.begin()->second;
        int maxL = byL.rbegin()->first, i2 = byL.rbegin()->second;
        if (i1 == i2) {
            assert(false);
        }
        assert(minR < maxL);
        sgt.edit(0, 0, sgt.n, minR, maxL + 1, 1);
        sgt.edit(0, 0, sgt.n, minR + 1, maxL, 1);
        byR.erase({a[i1].second, i1});
        byL.erase({a[i2].first, i2});
        a[i1].second = maxL;
        a[i2].first = minR;
        byR.emplace(a[i1].second, i1);
        byL.emplace(a[i2].first, i2);
        int newAlr = sgt.t[0];
        for (int j = alr + 1; j <= newAlr; ++j) {
            ans[j] = ops;
        }
        alr = newAlr;
    }
    for (int t = 0; t < q; ++t) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
    cout << "\n";
}
