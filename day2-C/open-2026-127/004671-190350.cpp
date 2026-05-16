#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using namespace std;
mt19937 rnd(239);

const int inf = (int)1e9;

struct event {
    int ty, x;
    event(int ty, int x) : ty(ty), x(x) {};
};


signed main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;
    vector <pair <int, int>> otr(n);
    vector <int> l(n), r(n), x;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        otr[i] = { l[i], r[i] };
        x.push_back(l[i]);
        x.push_back(r[i]);
    }
    sort(x.begin(), x.end());
    for (auto &i : l) i = lower_bound(x.begin(), x.end(), i) - x.begin();
    for (auto &i : r) i = lower_bound(x.begin(), x.end(), i) - x.begin();
    for (auto &i : otr) {
        i.first = lower_bound(x.begin(), x.end(), i.first) - x.begin();
        i.second = lower_bound(x.begin(), x.end(), i.second) - x.begin();
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    vector <int> lef(2 * n), mid(2 * n), rig(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        lef[i] = lower_bound(r.begin(), r.end(), i) - r.begin();
        rig[i] = n - (upper_bound(l.begin(), l.end(), i) - l.begin());
        mid[i] = n - lef[i] - rig[i];
    }
    int c, m, z, mxc = 0;
    vector <int> otv0(n + 2, inf), otv1(n + 1, inf);
    vector <vector <event>> ev(n + 3);
    for (int i = 0; i < 2 * n; i++) {
        mxc = max(mxc, mid[i]);
        ev[mid[i]].push_back(event(1, mid[i] / 2));
        ev[mid[i] + 2 * min(lef[i], rig[i]) + 2].push_back(event(-1, mid[i] / 2));
        ev[mid[i] - 1].push_back(event(1, (mid[i] - 1) / 2));
        ev[mid[i] + 2 * min(lef[i], rig[i]) + 1].push_back(event(-1, (mid[i] - 1) / 2));
    }
    multiset <int> cur;
    for (int k = 0; k <= n; k += 2) {
        for (auto e : ev[k]) {
            if (e.ty == 1) cur.insert(e.x);
            else cur.erase(cur.find(e.x));
        }
        if (!cur.empty()) otv0[k] = min(otv0[k], k / 2 - *cur.rbegin());
    }
    cur.clear();
    for (int k = 1; k <= n; k += 2) {
        for (auto e : ev[k]) {
            if (e.ty == 1) cur.insert(e.x);
            else cur.erase(cur.find(e.x));
        }
        if (!cur.empty()) otv0[k] = min(otv0[k], k / 2 - *cur.rbegin());
    }
    //for (auto i : otv0) cout << i << " ";
    vector <int> st(n + 2, inf);
    for (int i = 0; i < 2 * n; i++) {
        c = mid[i];
        m = min(lef[i], rig[i]);
        st[c + 2 * m] = min(st[c + 2 * m], -c - m);
    }
    int mn = inf;
    for (int k = 1; k <= n; k++) {
        mn = min(mn, st[k]);
        otv1[k] = k + mn;
    }
    while (q--) {
        cin >> z;
        if (z <= mxc) {
            cout << "0 ";
            continue;
        }
        cout << min(otv0[z], otv1[z]) << " ";
    }
    cout << "\n";
    return 0;
}
