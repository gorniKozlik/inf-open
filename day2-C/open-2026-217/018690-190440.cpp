#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int inf = 2e9;
// const ll inf = 2e18;

struct segTree {
    vector<int> t, lazy;

    void apply(int v, int val) {
        t[v] += val;
        lazy[v] += val;
    }

    void push(int v, int tl, int tr) {
        if (tl == tr) {
            lazy[v] = 0;
            return;
        }

        apply(v * 2, lazy[v]);
        apply(v * 2 + 1, lazy[v]);
        lazy[v] = 0;
    }

    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            apply(v, val);
        } else {
            int tm = (tl + tr) / 2;

            upd(v * 2, tl, tm, l, min(r, tm), val);
            upd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);

            t[v] = max(t[v * 2], t[v * 2 + 1]);
        }
    }

    int q() {
        return t[1];
    }

    segTree(int n) {
        t.resize(n * 4 + 1, 0);
        lazy.resize(n * 4 + 1, 0);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> p(2 * n);
    vector<pair<int, int>> l(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[2 * i] >> p[2 * i + 1];
        l[i].first = p[2 * i];
        l[i].second = p[2 * i + 1];
    }

    sort(p.begin(), p.end());
    unordered_map<int, int> mp;
    for (int i = 0; i < 2 * n; ++i) {
        if (mp.find(p[i]) == mp.end()) {
            mp[p[i]] = mp.size();
        }
        // if (mp.find(p[i] + 1) == mp.end()) {
        //     mp[p[i] + 1] = mp.size();
        // }
    }

    for (int i = 0; i < n; ++i) {
        l[i].first = mp[l[i].first];
        l[i].second = mp[l[i].second];
    }
    sort(l.begin(), l.end());

    vector<pair<int, int>> u(q);
    for (int i =0; i < q; ++i) {
        cin >> u[i].first;
        u[i].second = i;
    }

    sort(u.begin(), u.end());

    vector<vector<int>> p
}

signed main() {
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(0);
    cout.sync_with_stdio(0);

    int d = 1;
    // cin >> d;

    while(d--) {
        solve();
        cout << "\n";
    }
}
