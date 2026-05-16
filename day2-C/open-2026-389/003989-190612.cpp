#ifndef LOCAL
#pragma GCC optimize("Ofast,unroll-loops")
#endif

#include <bits/extc++.h>

using namespace std;

//#define int long long
#define ll long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()

vector<int> t, add;

void push(int v) {
    t[v * 2 + 1] += add[v];
    t[v * 2 + 2] += add[v];
    add[v * 2 + 1] += add[v];
    add[v * 2 + 2] += add[v];
    add[v] = 0;
}

void upd(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        t[v] += x;
        add[v] += x;
        return;
    }
    int m = (r + l) / 2;
    push(v);
    upd(v * 2 + 1, l, m, ql, qr, x);
    upd(v * 2 + 2, m, r, ql, qr, x);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
}

int32_t main() {
#ifndef LOCAL
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
#endif
    int n, q;
    cin >> n >> q;
    t.resize(10 * n);
    add.resize(10 * n);
    vector<pair<int, int> > a(n);
    for (auto &[l,r]: a) cin >> l >> r;
    set<int> s;
    for (auto [l,r]: a) {
        s.insert(l);
        s.insert(r);
    }
    map<int, int> to;
    int pos = 1;
    for (int i: s) to[i] = pos++;
    for (auto &[l,r]: a) {
        l = to[l];
        r = to[r];
    }
    sort(all(a));
    set<pair<int, int> > sl, sr;
    for (auto [l,r]: a) {
        sl.insert({l, r});
        sr.insert({r, l});
        upd(0, 0, 2 * n + 1, l, r + 1, 1);
    }
    vector<int> ans(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        while (t[0] < i) {
            auto [r1,l1] = *sr.begin();
            auto [l2,r2] = *(--sl.end());
            upd(0, 0, 2 * n + 1, l1, r1 + 1, -1);
            upd(0, 0, 2 * n + 1, l2, r2 + 1, -1);
            upd(0, 0, 2 * n + 1, l1, l2 + 1, 1);
            upd(0, 0, 2 * n + 1, r1, r2 + 1, 1);
            sr.erase({r1, l1});
            sr.erase({r2, l2});
            sl.erase({l1, r1});
            sl.erase({l2, r2});
            cnt++;
        }
        ans[i] = cnt;
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
    return 0;
}
