//#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define int long long


struct segtree {
    vector<int> t, lazy;

    segtree(int n) {
        t.resize(4 * n);
        lazy.resize(4 * n);
    }

    void push(int v, int tl, int tr) {
        if (tr - tl > 1) {
            lazy[2 * v + 1] += lazy[v];
            lazy[2 * v + 2] += lazy[v];
        }
        t[v] += lazy[v];
        lazy[v] = 0;
    }

    int get(int v, int tl, int tr, int ql, int qr) {
        push(v, tl, tr);
        if (tl >= qr || tr <= ql)
            return 0;
        if (tl >= ql && tr <= qr)
            return t[v];
        int tm = (tl + tr) / 2;
        return max(get(2 * v + 1, tl, tm, ql, qr), get(2 * v + 2, tm, tr, ql, qr));
    }

    void update(int v, int tl, int tr, int ql, int qr, int x) {
        push(v, tl, tr);
        if (tl >= qr || tr <= ql)
            return;
        if (tl >= ql && tr <= qr) {
            lazy[v] = x;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        update(2 * v + 1, tl, tm, ql, qr, x);
        update(2 * v + 2, tm, tr, ql, qr, x);
        t[v] = max(t[2 * v + 1], t[2 * v + 2]);
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> s(n);
    vector<int> p(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> s[i].first >> s[i].second;
        p[2 * i] = s[i].first;
        p[2 * i + 1] = s[i].second;
    }
    sort(p.begin(), p.end());
    for (int i = 0; i < n; i++) {
        s[i].first = distance(p.begin(), lower_bound(p.begin(), p.end(), s[i].first));
        s[i].second = distance(p.begin(), lower_bound(p.begin(), p.end(), s[i].second));
    }

    set<pair<int, int>> sl, sr;
    for (int i = 0; i < n; i++) {
        sl.insert({s[i].second, s[i].first});
        sr.insert(s[i]);
    }

    segtree st(2 * n);
    for (int i = 0; i < n; i++)
        st.update(0, 0, 2 * n, s[i].first, s[i].second + 1, 1);
    
    vector<int> ans(n + 1, 1e9);
    int t = 0, best = 0, res = st.get(0, 0, 2 * n, 0, 2 * n);
    while (true) {
        for (int i = best + 1; i <= res; i++)
            ans[i] = t;
        const pair<int, int> l = *sl.begin();
        const pair<int, int> r = *sr.rbegin();
        if (l.first >= r.first)
            break;
        st.update(0, 0, 2 * n, l.first, r.first + 1, 1);
        st.update(0, 0, 2 * n, l.first + 1, r.first, 1);
        best = res;
        res = st.get(0, 0, 2 * n, 0, 2 * n);
    
        sr.erase(r);
        sl.erase(l);
        sr.erase({l.second, l.first});
        sl.erase({r.second, r.first});

        sr.insert({l.second, r.first});
        sl.insert({r.first, l.second});
        sr.insert({l.first, r.second});
        sl.insert({r.second, l.first});

        t++;
    }

    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
