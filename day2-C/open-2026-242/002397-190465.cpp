#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

using oset = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long

struct mst {
    int sz = 1;

    vector<vector<int>> t;

    void build(int x, int lx, int rx, vector<int>& a) {
        if (rx - lx == 1) {
            if (lx < (int) a.size()) {
                t[x].push_back(a[lx]);
            }
        }
        else {
            int m = (lx + rx) / 2;
            build(2 * x + 1, lx, m, a);
            build(2 * x + 2, m, rx, a);
            merge(t[2 * x + 1].begin(), t[2 * x + 1].end(), t[2 * x + 2].begin(), t[2 * x + 2].end(),
                back_inserter(t[x]));
        }
    }

    void init(int n, vector<int>& a) {
        while (sz < n) sz *= 2;
        t.assign(2 * sz - 1, vector<int> ());
        build(0, 0, sz, a);
    }

    int get(int x, int lx, int rx, int l, int r, int l1, int r1) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) {
            int it = upper_bound(t[x].begin(), t[x].end(), r1) - lower_bound(t[x].begin(), t[x].end(), l1);
            return it;
        }
        int m = (lx + rx) / 2;
        int x1 = get(2 * x + 1, lx, m, l, r, l1, r1);
        int x2 = get(2 * x + 2, m, rx, l, r, l1, r1);
        return x1 + x2;
    }

    int getmx(int x, int lx, int rx, int l, int r, int l1, int r1) {
        if (lx >= r || rx <= l) return -1;
        if (lx >= l && rx <= r) {
            auto it = upper_bound(t[x].begin(), t[x].end(), r1);
            if (it == t[x].begin()) return -1;
            else {
                it--;
                int xx = *it;
                if (xx >= l1) {
                    assert(xx <= r1);
                    return xx;
                }
                else return -1;
            }
        }
        int m = (lx + rx) / 2;
        int x1 = getmx(2 * x + 1, lx, m, l, r, l1, r1);
        int x2 = getmx(2 * x + 2, m, rx, l, r, l1, r1);
        return max(x1, x2);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> ans(n + 1, LLONG_MAX);
    vector<int> vv2(n + 1, LLONG_MAX);
    vector<vector<int>> v1l(n + 1), v1r(n + 1);
    sort(a.begin(), a.end(), [&](pair<int, int> a, pair<int, int> b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });
    vector<int> tmp;
    for (int i = 0; i < n; i++) {
        tmp.push_back(a[i].second);
    }
    mst sg;
    sg.init(n + 1, tmp);
    for (int i = 0; i < n; i++) {
        int r = a[i].second;
        int l = a[i].first;
        l = sg.getmx(0, 0, sg.sz, i, n, a[i].first, a[i].second);
        int cnt = 0;
        cnt = sg.get(0, 0, sg.sz, i, n, 0, l + 1);
        /*for (int j = 0; j < n; j++) {
            if (a[j].first <= l && a[j].second >= r) cnt++;
        }*/
        int cl = 0, cr = 0;
        for (int j = 0; j < n; j++) {
            if (a[j].second < l) cl++;
            else if (a[j].first > r) cr++;
        }
        for (int j = 1; j <= cnt; j++) {
            ans[j] = 0;
        }
        int lx = cnt + 1;
        int rx = cnt + min(cl, cr) * 2;
        if (lx <= rx && lx <= n) {
            v1l[lx].push_back(1);
            if (rx + 1 <= n) {
                v1r[rx + 1].push_back(lx);
            }
        }
        int x = min(cl, cr) + 1;
        int ll = cnt + min(cl, cr) * 2 + 1;
        if (ll <= n) {
            vv2[ll] = min(vv2[ll], x - ll);
        }
    }
    int xx = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        xx = min(xx, vv2[i]);
        if (xx != LLONG_MAX) {
            ans[i] = min(ans[i], i + xx);
        }
    }
    multiset<int> ms;
    for (int i = 1; i <= n; i++) {
        for (auto el : v1r[i]) {
            ms.erase(ms.lower_bound(el));
        }
        for (auto el : v1l[i]) {
            ms.insert(i);
        }
        if (!ms.empty()) {
            int xi = *ms.rbegin();
            ans[i] = min(ans[i], (i - xi + 2) / 2);
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}